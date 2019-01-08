// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Vulkan/VulkanTraceConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"
#include "Converters/Utils/TracePacker.h"
#include "Converters/Utils/BasicTypesConverter.h"

namespace VTC
{
	using VPacker = TracePacker;
	
#	include "Generated/VulkanTraceStructPacker.h"
#	include "Generated/VulkanTraceStructPackerImpl.h"
#	include "Types/TraceFileHeader.h"

/*
=================================================
	RunConverter_VulkanPlayer
=================================================
*/
	bool RunConverter_VulkanPlayer (const AppTrace &trace, const ConverterConfig &config)
	{
		FG_TIMEPROFILER();
		FG_LOGI( "run VulkanPlayer converter" );

		VulkanTraceConverter	conv{ config };

		return conv.Run( trace );
	}
	
/*
=================================================
	constructor
=================================================
*/
	VulkanTraceConverter::VulkanTraceConverter (const ConverterConfig &cfg) :
		_config{ cfg.conveters.vulkanTrace },
		_directory{ fs::path{cfg.outputDirectory}.append("vk-trace") },
		_dataDir{ fs::path{cfg.outputDirectory}.append("data") },			// TODO
		_inputFile{ cfg.inputTraceFile },
		_fileName{ fs::path{cfg.outputDirectory}.filename().string() << "-vk" }
	{
		if ( not fs::exists( _directory ) ) {
			CHECK( fs::create_directories( _directory ));
		}
	}
	
/*
=================================================
	Run
=================================================
*/
	bool VulkanTraceConverter::Run (const AppTrace &appTrace)
	{
		// initialization
		{
			_appTrace		= &appTrace;
			_dataCounter	= 0;
			_lastUpdateTime	= 0;
			_dataAccess.clear();

			// request analyzers
			_swapchainAnalyzer		= appTrace.GetAnalyzer< SwapchainAnalyzer >();
			_resourcesBookmarks		= appTrace.GetAnalyzer< AllResourcesBookmarks >();
			_deviceAnalyzer			= appTrace.GetAnalyzer< DeviceAnalyzer >();
			_memTransferAnalyzer	= appTrace.GetAnalyzer< MemoryTransferAnalyzer >();
			_memoryObjAnalyzer		= appTrace.GetAnalyzer< MemoryObjAnalyzer >();
			_imageAnalyzer			= appTrace.GetAnalyzer< ImageAnalyzer >();
			_bufferAnalyzer			= appTrace.GetAnalyzer< BufferAnalyzer >();
			_extensionAnalyzer		= appTrace.GetAnalyzer< ExtensionAnalyzer >();
			_queueAnalyzer			= appTrace.GetAnalyzer< QueueAnalyzer >();
			_fpsAnalyzer			= appTrace.GetAnalyzer< FPSAnalyzer >();

			CHECK_ERR( _swapchainAnalyzer and _resourcesBookmarks and _deviceAnalyzer and _queueAnalyzer );
			CHECK_ERR( _memTransferAnalyzer and _extensionAnalyzer and _fpsAnalyzer );
			CHECK_ERR( _memoryObjAnalyzer and _imageAnalyzer and _bufferAnalyzer );

			_tracePacker.reset( new TracePacker{ _resourcesBookmarks, _config.useUniqueResourceIndices });
		}


		// convert packets
		const FrameID	last_frame	= Min( _config.lastFrame, appTrace.GetFrameCount() );
		FrameID			curr_frame	= 0;
		const auto&		present_bm	= appTrace.PresentBookmark();
		uint			progress	= 0;
		
		for (auto iter = appTrace.FullTrace().begin(); iter < appTrace.FullTrace().LastBookmark(); ++iter)
		{
			for (; not (iter < present_bm[curr_frame]) and curr_frame < present_bm.size(); ++curr_frame) {}

			if ( curr_frame >= last_frame )
				break;

			if ( not appTrace.CheckPacketErrors( iter ) )
				continue;
			
			CHECK_ERR( _ConvertFunction( iter, curr_frame ));

			const BytesU	diff		= appTrace.FullTrace().LastBookmark().Value() - iter.GetBookmark().Value();
			const uint		curr_progr	= 8 - uint((diff * 8) / appTrace.FullTrace().LastBookmark().Value());

			if ( curr_progr > progress )
			{
				progress = curr_progr;
				FG_LOGI( "progress: "s << ToString( (100 * progress + 7) / 8 ) << " %" );
			}
		}

		CHECK_ERR( _AfterConverting() );

		_appTrace = null;
		_tracePacker.reset();
		return true;
	}
	
/*
=================================================
	_InitializeResources
=================================================
*/
	void VulkanTraceConverter::_InitializeResources (INOUT TracePacker &packer) const
	{
		for (size_t i = 0; i < VkResourceTypes::Count; ++i)
		{
			uint64_t	count = _resourcesBookmarks->GetResourceCountByType( GetVkResourceType(i) );

			if ( not count )
				continue;

			packer.Begin( EPacketID::VInitializeResource );
			packer << uint(i);
			packer << count;
			packer.End( EPacketID::VInitializeResource );
		}
	}

/*
=================================================
	_AfterConverting
=================================================
*/
	bool VulkanTraceConverter::_AfterConverting ()
	{
		const auto		fname	= fs::path{_directory}.append( _fileName + ".bin" );
		FileWStream		file	{ fname };
		CHECK_ERR( file.IsOpen() );

		// header
		{
			TraceFileHeader		header		= {};
			header.magic					= TraceFileHeader::MagicNumber;
			header.instructionSet			= uint(EPacketID::_VulkanApi | EPacketID::_V100);
			header.pointerSize				= sizeof(void*);
			header.archiveType				= TraceFileHeader::EArchiveType::None;	// TODO
			header.instructionBlockOffset	= sizeof(header);
			header.dataBlockOffset			= UMax;

			CHECK_ERR( file.Write( header ));
		}

		// pack part 1
		{
			TracePacker		packer{ _resourcesBookmarks, _config.useUniqueResourceIndices };

			CHECK_ERR( _PackData( INOUT packer ));
			
			_InitializeResources( INOUT packer );
			
			using EImplFlags = VulkanCreateInfo::EImplFlags;

			EImplFlags		impl_flags = EImplFlags::None;
			if ( _config.remapMemory )				impl_flags |= EImplFlags::OverrideMemoryAllocation;
			if ( _config.remapQueueFamily )			impl_flags |= EImplFlags::RemapQueueFamilies;
			if ( _config.indirectSwapchain )		impl_flags |= EImplFlags::IndirectSwapchain;
			if ( _config.useUniqueResourceIndices )	impl_flags |= EImplFlags::UniqueResourceIndices;

			_PackVulkanCreateInfo( impl_flags, INOUT packer );

			CHECK_ERR( file.Write( packer.GetData() ));
		}

		// pack part 2
		_EndOfTrace( INOUT *_tracePacker );
		CHECK_ERR( file.Write( _tracePacker->GetData() ));

		CHECK_ERR( _GenMain( _fileName, _inputFile, fname, fs::path{_directory}.append("main.cpp") ));
		CHECK_ERR( _GenCMake( _fileName, fs::path{_directory}.append("CMakeLists.txt") ));

		return true;
	}

/*
=================================================
	_ConvertFunction
=================================================
*/
	bool VulkanTraceConverter::_ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId)
	{
		_tracePacker->SetCurrentPos( iter.GetBookmark() );

		switch ( iter->packet_id )
		{
			// skip some packets
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :		_lastUpdateTime = iter->vktrace_begin_time;	break;

			// remap queue family index
			//case VKTRACE_TPI_VK_vkCreateCommandPool :				CHECK_ERR( _OnCreateCommandPool( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkCreateBuffer :					CHECK_ERR( _OnCreateBuffer( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCreateImage :						CHECK_ERR( _OnCreateImage( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT :		break;	// skip origin names
			
			// load data from file and call function
			case VKTRACE_TPI_VK_vkCreateShaderModule :				CHECK_ERR( _OnCreateShaderModule( iter, frameId, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkCreatePipelineCache :				CHECK_ERR( _OnCreatePipelineCache( iter, frameId, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkCmdUpdateBuffer :					CHECK_ERR( _OnCmdUpdateBuffer( iter, frameId, INOUT *_tracePacker ));						break;
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR :	CHECK_ERR( _OnCmdPushDescriptorSetWithTemplate( iter, frameId, INOUT *_tracePacker ));	break;
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate :	CHECK_ERR( _OnUpdateDescriptorSetWithTemplate( iter, frameId, INOUT *_tracePacker ));		break;

			// remap swapchain images
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :				CHECK_ERR( _OnAcquireNextImage( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :			ASSERT(false);															break;	// TODO
			case VKTRACE_TPI_VK_vkQueuePresentKHR :					CHECK_ERR( _OnQueuePresent( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCreateRenderPass :				CHECK_ERR( _OnCreateRenderPass( iter, INOUT *_tracePacker ));			break;
				
			// remap swapchain images adn queue family index
			case VKTRACE_TPI_VK_vkCmdWaitEvents :					CHECK_ERR( _OnCmdWaitEvents( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :				CHECK_ERR( _OnCmdPipelineBarrier( iter, INOUT *_tracePacker ));			break;

			/*
			//case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment :		CHECK_ERR( _OnGetDeviceMemoryCommitment( iter, INOUT *_tracePacker ));	break;
			*/
			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :			CHECK_ERR( _OnUpdateDescriptorSets( iter, INOUT *_tracePacker ));		break;

			// remap memory
			case VKTRACE_TPI_VK_vkAllocateMemory :					CHECK_ERR( _OnAllocateMemory( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkFreeMemory :						CHECK_ERR( _OnFreeMemory( iter, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkMapMemory :						CHECK_ERR( _OnMapMemory( iter, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkUnmapMemory :						CHECK_ERR( _OnUnmapMemory( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK_ERR( _OnFlushMappedMemoryRanges( iter, frameId, INOUT *_tracePacker ));	break;
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	break;
			case VKTRACE_TPI_VK_vkBindBufferMemory :				CHECK_ERR( _OnBindBufferMemory( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkBindImageMemory :					CHECK_ERR( _OnBindImageMemory( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :			CHECK_ERR( _OnBindBufferMemory2( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :				CHECK_ERR( _OnBindImageMemory2( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkDestroyBuffer :					CHECK_ERR( _OnDestroyBuffer( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkDestroyImage :					CHECK_ERR( _OnDestroyImage( iter, INOUT *_tracePacker ));				break;

			// use default packer
			default :												CHECK_ERR( _ConvertVkFunction( iter, INOUT *_tracePacker ));			break;
		}
		return true;
	}

/*
=================================================
	_ConvertVkFunction
=================================================
*/
	bool VulkanTraceConverter::_ConvertVkFunction (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
#		ifdef _MSC_VER
#			pragma warning (push)
#			pragma warning (disable: 4505)
#			pragma warning (disable: 4189)
#		endif

#		include "Generated/VulkanTraceFuncPacker.h"

#		ifdef _MSC_VER
#			pragma warning (pop)
#		endif

		return true;
	}
	
/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool VulkanTraceConverter::_OnAcquireNextImage (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkAcquireNextImageKHR >();
		VK_CHECK( packet.result );
		
		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.swapchain), pos.GetBookmark() );
		CHECK_ERR( swapchain );
		CHECK_ERR( *packet.pImageIndex < swapchain->images.size() );

		packer.Begin( EPacketID::VAcquireNextImageKHR );
		{
			packer << packet.device;
			packer << packet.swapchain;
			packer << packet.timeout;
			packer << packet.semaphore;
			packer << packet.fence;
			packer << VkImage(swapchain->images[ *packet.pImageIndex ].id);
		}
		packer.End( EPacketID::VAcquireNextImageKHR );

		return true;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool VulkanTraceConverter::_OnQueuePresent (const TraceRange::Iterator &pos, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkQueuePresentKHR >();
		VK_CHECK( packet.result );
		CHECK_ERR( packet.pPresentInfo );
		CHECK_ERR( packet.pPresentInfo->pNext == null );
		CHECK_ERR( packet.pPresentInfo->swapchainCount == 1 );
		
		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.pPresentInfo->pSwapchains[0]), pos.GetBookmark() );
		CHECK_ERR( swapchain );
		
		const uint64_t	dt = pos->vktrace_begin_time - _lastUpdateTime;
		_lastUpdateTime = pos->vktrace_begin_time;

		packer.Begin( EPacketID::VQueuePresentKHR );
		{
			packer << dt;
			packer << packet.queue;
			packer << VkImage(swapchain->images[ *packet.pPresentInfo->pImageIndices ].id);
			packer << packet.pPresentInfo->waitSemaphoreCount;

			packer.Push( packet.pPresentInfo->pWaitSemaphores );
			 for (uint i = 0; i < packet.pPresentInfo->waitSemaphoreCount; ++i) {
				packer << packet.pPresentInfo->pWaitSemaphores[i];
			 }
			packer.PopAndStore( packet.pPresentInfo->pWaitSemaphores );
		}
		packer.End( EPacketID::VQueuePresentKHR );

		return true;
	}
	
/*
=================================================
	IsPresentLayout
=================================================
*/
	ND_ inline bool  IsPresentLayout (VkImageLayout layout)
	{
		if ( layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR or
			 layout == VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR )
		{
			return true;
		}
		return false;
	}

/*
=================================================
	_OnCreateRenderPass
=================================================
*/
	bool VulkanTraceConverter::_OnCreateRenderPass (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		// replace image layouts with *present* by *transfer*
		if ( _config.indirectSwapchain )
		{
			auto&	packet = pos.Cast< packet_vkCreateRenderPass >();

			for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i)
			{
				auto&	attachment = const_cast<VkAttachmentDescription *>( packet.pCreateInfo->pAttachments )[i];

				if ( IsPresentLayout( attachment.initialLayout ) )
					attachment.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// from blit command

				if ( IsPresentLayout( attachment.finalLayout ) )
					attachment.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;		// to blit command
			}
		}
			
		return _ConvertVkFunction( pos, packer );
	}
	
/*
=================================================
	_OnWaitEvents2
=================================================
*/
	bool VulkanTraceConverter::_OnWaitEvents2 (const TraceRange::Iterator &pos) const
	{
		// replace image layouts with *present* by *transfer*
		if ( _config.indirectSwapchain )
		{
			auto&	packet = pos.Cast< packet_vkCmdWaitEvents >();

			for (uint i = 0; i < packet.imageMemoryBarrierCount; ++i)
			{
				auto&	barrier = const_cast<VkImageMemoryBarrier *>( packet.pImageMemoryBarriers )[i];

				if ( IsPresentLayout( barrier.oldLayout ) )
					barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// from blit command

				if ( IsPresentLayout( barrier.newLayout ) )
					barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// to blit command
			}
		}
		return true;
	}
	
/*
=================================================
	_OnPipelineBarrier2
=================================================
*/
	bool VulkanTraceConverter::_OnPipelineBarrier2 (const TraceRange::Iterator &pos) const
	{
		// replace image layouts with *present* by *transfer*
		if ( _config.indirectSwapchain )
		{
			auto&	packet = pos.Cast< packet_vkCmdPipelineBarrier >();

			for (uint i = 0; i < packet.imageMemoryBarrierCount; ++i)
			{
				auto&	barrier = const_cast<VkImageMemoryBarrier *>( packet.pImageMemoryBarriers )[i];

				if ( IsPresentLayout( barrier.oldLayout ) )
					barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// from blit command

				if ( IsPresentLayout( barrier.newLayout ) )
					barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// to blit command
			}
		}
		return true;
	}

/*
=================================================
	_OnCmdWaitEvents
=================================================
*/
	bool VulkanTraceConverter::_OnCmdWaitEvents (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _OnWaitEvents2( pos ));
		//CHECK_ERR( _OnWaitEvents3( pos ));
		return _ConvertVkFunction( pos, packer );
	}
	
/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*/
	bool VulkanTraceConverter::_OnCmdPipelineBarrier (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _OnPipelineBarrier2( pos ));
		//CHECK_ERR( _OnPipelineBarrier3( pos ));
		return _ConvertVkFunction( pos, packer );
	}

/*
=================================================
	_OnCreateShaderModule
=================================================
*/
	bool VulkanTraceConverter::_OnCreateShaderModule (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkCreateShaderModule >();
		CHECK_ERR( packet.pCreateInfo );
		VK_CHECK( packet.result );
		
		DataID		data_id = _RequestData( pos, packet.header, packet.pCreateInfo->pCode, packet.pCreateInfo->codeSize, frameId );
		CHECK_ERR( data_id != UMax );
		
		const_cast<VkShaderModuleCreateInfo *>(packet.pCreateInfo)->pCode = null;
		const_cast<VkShaderModuleCreateInfo *>(packet.pCreateInfo)->codeSize = 0;

		packer.Begin( EPacketID::VCreateShaderModule );
		{
			packer.Push( packet.pCreateInfo );
			 VPack_VkShaderModuleCreateInfo( packet.pCreateInfo, packer );
			packer.PopAndStore( packet.pCreateInfo );

			packer << data_id;
			packer << packet.device;
			packer.Push( packet.pShaderModule );
			 packer << (*packet.pShaderModule);
			packer.PopAndStore( packet.pShaderModule );
		}
		packer.End( EPacketID::VCreateShaderModule );

		return true;
	}
	
/*
=================================================
	_OnCreatePipelineCache
=================================================
*/
	bool VulkanTraceConverter::_OnCreatePipelineCache (const TraceRange::Iterator &pos, FrameID, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkCreatePipelineCache >();
		CHECK_ERR( packet.pCreateInfo );
		VK_CHECK( packet.result );

		const_cast<VkPipelineCacheCreateInfo *>(packet.pCreateInfo)->pInitialData	 = null;
		const_cast<VkPipelineCacheCreateInfo *>(packet.pCreateInfo)->initialDataSize = 0;

		packer.Begin( EPacketID::VCreatePipelineCache );
		{
			packer.Push( packet.pCreateInfo );
			 VPack_VkPipelineCacheCreateInfo( packet.pCreateInfo, packer );
			packer.PopAndStore( packet.pCreateInfo );
			
			packer << packet.device;
			packer.Push( packet.pPipelineCache );
			 packer << (*packet.pPipelineCache);
			packer.PopAndStore( packet.pPipelineCache );
		}
		packer.End( EPacketID::VCreatePipelineCache );

		return true;
	}
	
/*
=================================================
	_OnCmdUpdateBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnCmdUpdateBuffer (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkCmdUpdateBuffer >();

		DataID		data_id = _RequestData( pos, packet.header, packet.pData, packet.dataSize, frameId );
		CHECK_ERR( data_id != UMax );

		packer.Begin( EPacketID::VCmdUpdateBuffer );
		{
			packer << packet.commandBuffer;
			packer << packet.dstBuffer;
			packer << packet.dstOffset;
			packer << packet.dataSize;
			packer << data_id;
		}
		packer.End( EPacketID::VCmdUpdateBuffer );

		return true;
	}
	
/*
=================================================
	_OnUpdateDescriptorSets
=================================================
*/
	bool VulkanTraceConverter::_OnUpdateDescriptorSets (const TraceRange::Iterator &pos, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkUpdateDescriptorSets >();

		for (uint i = 0; i < packet.descriptorWriteCount; ++i)
		{
			auto&	write		= packet.pDescriptorWrites[i];
			auto&	image_info	= const_cast<VkDescriptorImageInfo *&>(write.pImageInfo);
			auto&	buffer_info	= const_cast<VkDescriptorBufferInfo *&>(write.pBufferInfo);
			auto&	buffer_view	= const_cast<VkBufferView *&>(write.pTexelBufferView);

			ENABLE_ENUM_CHECKS();
			switch ( write.descriptorType )
			{
				case VK_DESCRIPTOR_TYPE_SAMPLER :
				case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER :
				case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE :
				case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE :
				case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT :
					buffer_info = null;
					buffer_view = null;
					break;

				case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER :
				case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER :
					image_info = null;
					buffer_info = null;
					break;

				case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
				case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER :
				case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC :
				case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC :
					image_info = null;
					buffer_view = null;
					break;

				case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT :
				case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV :
				case VK_DESCRIPTOR_TYPE_RANGE_SIZE :
				case VK_DESCRIPTOR_TYPE_MAX_ENUM :
					ASSERT(false);
					image_info = null;
					buffer_info = null;
					buffer_view = null;
					break;
			}
			DISABLE_ENUM_CHECKS();

			
			switch ( write.descriptorType )
			{
				case VK_DESCRIPTOR_TYPE_SAMPLER :
					for (uint a = 0; image_info and a < write.descriptorCount; ++a) {
						image_info[a].imageLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
						image_info[a].imageView		= VK_NULL_HANDLE;
					}
					break;

				case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE :
				case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE :
				case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT :
					for (uint a = 0; image_info and a < write.descriptorCount; ++a) {
						image_info[a].sampler = VK_NULL_HANDLE;
					}
					break;
			}
		}

		return _ConvertVkFunction( pos, packer );
	}

/*
=================================================
	_OnCmdPushDescriptorSetWithTemplate
=================================================
*/
	bool VulkanTraceConverter::_OnCmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &)
	{
		// TODO
		return false;
	}
	
/*
=================================================
	_OnUpdateDescriptorSetWithTemplate
=================================================
*/
	bool VulkanTraceConverter::_OnUpdateDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &)
	{
		// TODO
		return false;
	}
	
/*
=================================================
	_OnCreateBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnCreateBuffer (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _ConvertVkFunction( pos, INOUT *_tracePacker ));
		
		auto&	packet	= pos.Cast< packet_vkCreateBuffer >();
		auto*	res		= _resourcesBookmarks->GetResource( VK_OBJECT_TYPE_BUFFER, ResourceID(*packet.pBuffer), pos.GetBookmark() );
		CHECK_ERR( res );

		String	name	= "buffer-"s + ToString<16>( res->uniqueIndex );

		VkDebugMarkerObjectNameInfoEXT	info = {};
		info.sType		= VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
		info.objectType	= VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT;
		info.object		= uint64_t(*packet.pBuffer);
		info.pObjectName= name.data();
		
		packer.RemapVkResource( BitCast<VkBuffer *>(&info.object) );

		packer.Begin( EPacketID::VDebugMarkerSetObjectNameEXT );
		packer << packet.device;
		packer.Push( &info );
		 VPackStruct( BitCast<VkBaseInStructure const*>(&info), packer );
		packer.PopAndStore( &info );
		packer.End( EPacketID::VDebugMarkerSetObjectNameEXT );

		return true;
	}
	
	
/*
=================================================
	_OnCreateImage
=================================================
*/
	bool VulkanTraceConverter::_OnCreateImage (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _ConvertVkFunction( pos, INOUT *_tracePacker ));

		auto&	packet	= pos.Cast< packet_vkCreateImage >();
		auto*	res		= _resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, ResourceID(*packet.pImage), pos.GetBookmark() );
		CHECK_ERR( res );

		String	name	= "image-"s + ToString<16>( res->uniqueIndex );

		VkDebugMarkerObjectNameInfoEXT	info = {};
		info.sType		= VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
		info.objectType	= VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;
		info.object		= uint64_t(*packet.pImage);
		info.pObjectName= name.data();

		packer.RemapVkResource( BitCast<VkImage *>(&info.object) );

		packer.Begin( EPacketID::VDebugMarkerSetObjectNameEXT );
		packer << packet.device;
		packer.Push( &info );
		 VPackStruct( BitCast<VkBaseInStructure const*>(&info), packer );
		packer.PopAndStore( &info );
		packer.End( EPacketID::VDebugMarkerSetObjectNameEXT );

		return true;
	}

}	// VTC
