// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/FrameGraphConverter.h"
#include "Converters/Utils/TracePacker.h"
#include "Converters/FrameGraph/DrawCallConverter.h"
#include "Converters/FrameGraph/PipelineConverter.h"
#include "Converters/FrameGraph/SamplerConverter.h"
#include "Converters/FrameGraph/ImageConverter.h"
#include "Converters/FrameGraph/BufferConverter.h"
#include "framegraph/Public/FGEnums.h"

namespace VTC
{
#	include "Types/TraceFileHeader.h"

/*
=================================================
	RunConverter_FrameGraph
=================================================
*/
	bool RunConverter_FrameGraph (const AppTrace &trace, const ConverterConfig &config)
	{
		FG_TIMEPROFILER();
		FG_LOGI( "run FrameGraph converter" );

		FrameGraphConverter	conv{ config };

		return conv.Run( trace );
	}
	
/*
=================================================
	constructor
=================================================
*/
	FrameGraphConverter::FrameGraphConverter (const ConverterConfig &cfg) :
		_config{ cfg.conveters.frameGraphTrace },
		_directory{ fs::path{cfg.outputDirectory}.append("fg-trace") },
		_dataDir{ fs::path{cfg.outputDirectory}.append("data") },			// TODO
		_inputFile{ cfg.inputTraceFile },
		_fileName{ fs::path{cfg.outputDirectory}.filename().string() << "-fg" }
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
	bool FrameGraphConverter::Run (const AppTrace &appTrace)
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
			_renderPassAnalyzer		= appTrace.GetAnalyzer< RenderPassAnalyzer >();

			CHECK_ERR( _swapchainAnalyzer and _resourcesBookmarks and _deviceAnalyzer and _queueAnalyzer );
			CHECK_ERR( _memTransferAnalyzer and _extensionAnalyzer and _fpsAnalyzer );
			CHECK_ERR( _memoryObjAnalyzer and _imageAnalyzer and _bufferAnalyzer );
			
			_tracePacker.reset( new TracePacker{} );
			_tempPacker.reset( new TracePacker{} );

			_imageConv.reset( new ImageConverter{ *this });
			_bufferConv.reset( new BufferConverter{ *this });
			_samplerConv.reset( new SamplerConverter{ *this });
			_pipelineConv.reset( new PipelineConverter{ *this });
			_drawCallConv.reset( new DrawCallConverter{ *this });
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
		_tempPacker.reset();
		_drawCallConv.reset();
		_pipelineConv.reset();
		_samplerConv.reset();
		_imageConv.reset();
		_bufferConv.reset();
		return true;
	}
	
/*
=================================================
	_AfterConverting
=================================================
*/
	bool FrameGraphConverter::_AfterConverting ()
	{
		const auto		fname	= fs::path{_directory}.append( _fileName + ".bin" );
		FileWStream		file	{ fname };
		CHECK_ERR( file.IsOpen() );

		// header
		{
			TraceFileHeader		header		= {};
			header.magic					= TraceFileHeader::MagicNumber;
			header.instructionSet			= uint(EPacketID::_FrameGraphApi | EPacketID::_V100);
			header.pointerSize				= sizeof(void*);
			header.archiveType				= TraceFileHeader::EArchiveType::None;	// TODO
			header.instructionBlockOffset	= sizeof(header);
			header.dataBlockOffset			= UMax;

			CHECK_ERR( file.Write( header ));
		}

		// pack part 1
		{
			TracePacker		packer{ _resourcesBookmarks, true };

			CHECK_ERR( _PackData( INOUT packer ));
			
			_InitializeResources( INOUT packer );
			_PackVulkanCreateInfo( VulkanCreateInfo::EImplFlags::None, INOUT packer );
			_PackCreateThreads( INOUT packer );

			CHECK_ERR( _pipelineConv->Convert( INOUT packer ));
			CHECK_ERR( _samplerConv->Convert( INOUT packer ));

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
	_InitializeResources
=================================================
*/
	void FrameGraphConverter::_InitializeResources (INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgSetThreadCount );
		packer << uint(1);	// TODO
		packer.End( EPacketID::FgSetThreadCount );

		packer.Begin( EPacketID::FgSetShaderModuleCount );
		packer << _pipelineConv->GetShaderModuleCount();
		packer.End( EPacketID::FgSetShaderModuleCount );

		packer.Begin( EPacketID::FgSetGraphicsPipelineCount );
		packer << _pipelineConv->GetGraphicsPipelineCount();
		packer.End( EPacketID::FgSetGraphicsPipelineCount );
		
		packer.Begin( EPacketID::FgSetComputePipelineCount );
		packer << _pipelineConv->GetComputePipelineCount();
		packer.End( EPacketID::FgSetComputePipelineCount );

		packer.Begin( EPacketID::FgSetSamplerCount );
		packer << _samplerConv->GetSamplerCacheSize();
		packer.End( EPacketID::FgSetSamplerCount );
		
		packer.Begin( EPacketID::FgSetImageCount );
		packer << _imageConv->GetImageCount();
		packer.End( EPacketID::FgSetImageCount );

		packer.Begin( EPacketID::FgSetBufferCount );
		packer << _bufferConv->GetBufferCount();
		packer.End( EPacketID::FgSetBufferCount );
		
		packer.Begin( EPacketID::FgSetBufferCount );
		packer << _bufferConv->GetBufferCount();
		packer.End( EPacketID::FgSetBufferCount );

		packer.Begin( EPacketID::FgSetLogicalPassCount );
		packer << _drawCallConv->GetMaxLogicalPasses();
		packer.End( EPacketID::FgSetLogicalPassCount );
	}
	
/*
=================================================
	_PackCreateThreads
----
	see unpacker in 'FGPlayer_v100::_CreateFrameGraphThread'
=================================================
*/
	void FrameGraphConverter::_PackCreateThreads (INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateThread );
		packer << uint(0);		// TODO: thread id
		packer << (EThreadUsage::Present | EThreadUsage::Graphics | EThreadUsage::Transfer);
		packer.End( EPacketID::FgCreateThread );
	}

/*
=================================================
	_OnBeginFrame
----
	see unpacker in 'FGPlayer_v100::_BeginFrame'
=================================================
*/
	bool FrameGraphConverter::_OnBeginFrame (TraceRange::Bookmark pos, FrameID frameId, INOUT TracePacker &packer) const
	{
		CommandBatchID		batch_id {"main"};

		packer.Begin( EPacketID::FgBeginFrame );
		packer << uint(1);	// batch count
		packer << batch_id;
		packer << uint(1);
		packer.End( EPacketID::FgBeginFrame );

		packer.Begin( EPacketID::FgBeginThread );
		packer << uint(0);		// thread id
		packer << batch_id;
		packer << uint(0);
		packer << (EThreadUsage::Graphics);
		packer.End( EPacketID::FgBeginThread );

		CHECK_ERR( _bufferConv->OnBeginFrame( pos, frameId, packer ));
		CHECK_ERR( _imageConv->OnBeginFrame( pos, frameId, packer ));
		return true;
	}
	
/*
=================================================
	_OnEndFrame
----
	see unpacker in 'FGPlayer_v100::_EndFrame'
=================================================
*/
	bool FrameGraphConverter::_OnEndFrame (uint64_t dt, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _bufferConv->OnEndFrame( packer ));
		CHECK_ERR( _imageConv->OnEndFrame( packer ));
		
		packer.Begin( EPacketID::FgEndThread );
		packer << uint(0);	// thread id
		packer.End( EPacketID::FgEndThread );

		packer.Begin( EPacketID::FgEndFrame );
		packer << dt;
		packer.End( EPacketID::FgEndFrame );
		return true;
	}

/*
=================================================
	_ConvertFunction
=================================================
*/
	bool FrameGraphConverter::_ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId)
	{
		ENABLE_ENUM_CHECKS();
		switch ( iter->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateSampler :						CHECK( _samplerConv->CreateSampler( iter ));		break;
			case VKTRACE_TPI_VK_vkDestroySampler :						_samplerConv->DestroySampler( iter );				break;
			case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion :
			case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR :		CHECK( _samplerConv->CreateSamplerYcbcr( iter ));	break;
			case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion :
			case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR :	_samplerConv->DestroySamplerYcbcr( iter );			break;

			case VKTRACE_TPI_VK_vkAllocateMemory :
			case VKTRACE_TPI_VK_vkFreeMemory :
			case VKTRACE_TPI_VK_vkMapMemory :
			case VKTRACE_TPI_VK_vkUnmapMemory :
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :
			case VKTRACE_TPI_VK_vkCreateFence :
			case VKTRACE_TPI_VK_vkDestroyFence :
			case VKTRACE_TPI_VK_vkResetFences :
			case VKTRACE_TPI_VK_vkCreateSemaphore :
			case VKTRACE_TPI_VK_vkDestroySemaphore :
			case VKTRACE_TPI_VK_vkCreateEvent :
			case VKTRACE_TPI_VK_vkDestroyEvent :
			case VKTRACE_TPI_VK_vkSetEvent :
			case VKTRACE_TPI_VK_vkResetEvent :
			case VKTRACE_TPI_VK_vkCreateQueryPool :
			case VKTRACE_TPI_VK_vkDestroyQueryPool :
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
			case VKTRACE_TPI_VK_vkDestroyFramebuffer :
			case VKTRACE_TPI_VK_vkCreateRenderPass :
			case VKTRACE_TPI_VK_vkDestroyRenderPass :
				break;
			
			case VKTRACE_TPI_VK_vkWaitForFences :
			case VKTRACE_TPI_VK_vkQueueWaitIdle :
			case VKTRACE_TPI_VK_vkDeviceWaitIdle :				break;	// TODO

			case VKTRACE_TPI_VK_vkCreateBuffer :				CHECK( _bufferConv->CreateBuffer( iter ));					break;
			case VKTRACE_TPI_VK_vkDestroyBuffer :				CHECK( _bufferConv->DestroyBuffer( iter ));					break;
			case VKTRACE_TPI_VK_vkCreateBufferView :			ASSERT(false);  break;
			case VKTRACE_TPI_VK_vkDestroyBufferView :			ASSERT(false);  break;
			case VKTRACE_TPI_VK_vkBindBufferMemory :			CHECK( _bufferConv->BindMemory( iter ));					break;
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :		CHECK( _bufferConv->BindMemory2( iter ));					break;
				
			case VKTRACE_TPI_VK_vkCreateImage :					CHECK( _imageConv->CreateImage( iter ));					break;
			case VKTRACE_TPI_VK_vkDestroyImage :				CHECK( _imageConv->DestroyImage( iter ));					break;
			case VKTRACE_TPI_VK_vkBindImageMemory :				CHECK( _imageConv->BindMemory( iter ));						break;
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :			CHECK( _imageConv->BindMemory2( iter ));					break;
			case VKTRACE_TPI_VK_vkCreateImageView :				break;	// ignore
			case VKTRACE_TPI_VK_vkDestroyImageView :			break;	// ignore
			case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR :		CHECK( _imageConv->GetSwapchainImages( iter ));				break;

			case VKTRACE_TPI_VK_vkCreateShaderModule :			CHECK( _pipelineConv->CreateShaderModule( iter ));			break;
			case VKTRACE_TPI_VK_vkDestroyShaderModule :			CHECK( _pipelineConv->DestroyShaderModule( iter ));			break;
			case VKTRACE_TPI_VK_vkCreateDescriptorSetLayout :	CHECK( _pipelineConv->CreateDescriptorSetLayout( iter ));	break;
			case VKTRACE_TPI_VK_vkDestroyDescriptorSetLayout :	CHECK( _pipelineConv->DestroyDescriptorSetLayout( iter ));	break;
			case VKTRACE_TPI_VK_vkCreatePipelineLayout :		CHECK( _pipelineConv->CreatePipelineLayout( iter ));		break;
			case VKTRACE_TPI_VK_vkDestroyPipelineLayout :		CHECK( _pipelineConv->DestroyPipelineLayout( iter ));		break;
			case VKTRACE_TPI_VK_vkCreateGraphicsPipelines :		CHECK( _pipelineConv->CreateGraphicsPipelines( iter ));		break;
			case VKTRACE_TPI_VK_vkCreateComputePipelines :		CHECK( _pipelineConv->CreateComputePipelines( iter ));		break;
			case VKTRACE_TPI_VK_vkDestroyPipeline :				CHECK( _pipelineConv->DestroyPipeline( iter ));				break;
				
			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :
				//CHECK( _pipelineConv->UpdateDescriptorSets( iter ));
				CHECK( _drawCallConv->UpdateDescriptorSets( iter ));
				break;

			case VKTRACE_TPI_VK_vkCreateDescriptorPool :		CHECK( _drawCallConv->CreateDescriptorPool( iter ));		break;
			case VKTRACE_TPI_VK_vkDestroyDescriptorPool :		CHECK( _drawCallConv->DestroyDescriptorPool( iter ));		break;
			case VKTRACE_TPI_VK_vkResetDescriptorPool :			CHECK( _drawCallConv->ResetDescriptorPool( iter ));			break;
			case VKTRACE_TPI_VK_vkAllocateDescriptorSets :		CHECK( _drawCallConv->AllocateDescriptorSets( iter ));		break;
			case VKTRACE_TPI_VK_vkFreeDescriptorSets :			CHECK( _drawCallConv->FreeDescriptorSets( iter ));			break;
			case VKTRACE_TPI_VK_vkCreateCommandPool :			CHECK( _drawCallConv->CreateCommandPool( iter ));			break;
			case VKTRACE_TPI_VK_vkDestroyCommandPool :			CHECK( _drawCallConv->DestroyCommandPool( iter ));			break;
			case VKTRACE_TPI_VK_vkResetCommandPool :			CHECK( _drawCallConv->ResetCommandPool( iter ));			break;
			case VKTRACE_TPI_VK_vkAllocateCommandBuffers :		CHECK( _drawCallConv->AllocateCommandBuffers( iter ));		break;
			case VKTRACE_TPI_VK_vkFreeCommandBuffers :			CHECK( _drawCallConv->FreeCommandBuffers( iter ));			break;
			case VKTRACE_TPI_VK_vkBeginCommandBuffer :			CHECK( _drawCallConv->BeginCommandBuffer( iter ));			break;
			case VKTRACE_TPI_VK_vkEndCommandBuffer :			CHECK( _drawCallConv->EndCommandBuffer( iter ));			break;
			case VKTRACE_TPI_VK_vkResetCommandBuffer :			CHECK( _drawCallConv->ResetCommandBuffer( iter ));			break;
			case VKTRACE_TPI_VK_vkTrimCommandPool :				break;
			case VKTRACE_TPI_VK_vkTrimCommandPoolKHR :			break;
			case VKTRACE_TPI_VK_vkCmdBindPipeline :				CHECK( _drawCallConv->CmdBindPipeline( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetViewport :				CHECK( _drawCallConv->CmdSetViewport( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetScissor :				CHECK( _drawCallConv->CmdSetScissor( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetLineWidth :				CHECK( _drawCallConv->CmdSetLineWidth( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetDepthBias :				CHECK( _drawCallConv->CmdSetDepthBias( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetBlendConstants :		CHECK( _drawCallConv->CmdSetBlendConstants( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdSetDepthBounds :			CHECK( _drawCallConv->CmdSetDepthBounds( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdSetStencilCompareMask :	CHECK( _drawCallConv->CmdSetStencilCompareMask( iter ));	break;
			case VKTRACE_TPI_VK_vkCmdSetStencilWriteMask :		CHECK( _drawCallConv->CmdSetStencilWriteMask( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdSetStencilReference :		CHECK( _drawCallConv->CmdSetStencilReference( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdBindDescriptorSets :		CHECK( _drawCallConv->CmdBindDescriptorSets( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdBindIndexBuffer :			CHECK( _drawCallConv->CmdBindIndexBuffer( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdBindVertexBuffers :		CHECK( _drawCallConv->CmdBindVertexBuffers( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdDraw :						CHECK( _drawCallConv->CmdDraw( iter ));						break;
			case VKTRACE_TPI_VK_vkCmdDrawIndexed :				CHECK( _drawCallConv->CmdDrawIndexed( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdDrawIndirect :				CHECK( _drawCallConv->CmdDrawIndirect( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect :		CHECK( _drawCallConv->CmdDrawIndexedIndirect( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdDispatch :					CHECK( _drawCallConv->CmdDispatch( iter ));					break;
			case VKTRACE_TPI_VK_vkCmdDispatchIndirect :			CHECK( _drawCallConv->CmdDispatchIndirect( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdCopyBuffer :				CHECK( _drawCallConv->CmdCopyBuffer( iter, frameId ));		break;
			case VKTRACE_TPI_VK_vkCmdCopyImage :				CHECK( _drawCallConv->CmdCopyImage( iter, frameId ));		break;
			case VKTRACE_TPI_VK_vkCmdBlitImage :				CHECK( _drawCallConv->CmdBlitImage( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :		CHECK( _drawCallConv->CmdCopyBufferToImage( iter, frameId ));break;
			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :		CHECK( _drawCallConv->CmdCopyImageToBuffer( iter, frameId ));break;
			case VKTRACE_TPI_VK_vkCmdUpdateBuffer :				CHECK( _drawCallConv->CmdUpdateBuffer( iter, frameId ));	break;
			case VKTRACE_TPI_VK_vkCmdFillBuffer :				CHECK( _drawCallConv->CmdFillBuffer( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdClearColorImage :			CHECK( _drawCallConv->CmdClearColorImage( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage :	CHECK( _drawCallConv->CmdClearDepthStencilImage( iter ));	break;
			case VKTRACE_TPI_VK_vkCmdClearAttachments :			CHECK( _drawCallConv->CmdClearAttachments( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdResolveImage :				CHECK( _drawCallConv->CmdResolveImage( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetEvent :					ASSERT(false);	break;
			case VKTRACE_TPI_VK_vkCmdResetEvent :				break;
			case VKTRACE_TPI_VK_vkCmdWaitEvents :				ASSERT(false);	break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :			break;
			case VKTRACE_TPI_VK_vkCmdBeginQuery :				break;
			case VKTRACE_TPI_VK_vkCmdEndQuery :					break;
			case VKTRACE_TPI_VK_vkCmdResetQueryPool :			break;
			case VKTRACE_TPI_VK_vkCmdWriteTimestamp :			break;
			case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults :		break;
			case VKTRACE_TPI_VK_vkCmdPushConstants :			CHECK( _drawCallConv->CmdPushConstants( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :			CHECK( _drawCallConv->CmdBeginRenderPass( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdNextSubpass :				CHECK( _drawCallConv->CmdNextSubpass( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :			CHECK( _drawCallConv->CmdEndRenderPass( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdExecuteCommands :			CHECK( _drawCallConv->CmdExecuteCommands( iter ));			break;
			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :		ASSERT(false);		break;
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :	ASSERT(false);	break;
			case VKTRACE_TPI_VK_vkCmdSetDeviceMask :			ASSERT(false);		break;
			case VKTRACE_TPI_VK_vkCmdDispatchBase :				CHECK( _drawCallConv->CmdDispatchBase( iter ));				break;
			case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT :	ASSERT(false);		break;
			case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV :	ASSERT(false);		break;
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR :		CHECK( _drawCallConv->CmdPushDescriptorSet( iter ));		break;
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR :	CHECK( _drawCallConv->CmdPushDescriptorSetWithTemplate( iter ));break;
			case VKTRACE_TPI_VK_vkQueueBindSparse :				ASSERT(false);		break;
			case VKTRACE_TPI_VK_vkQueueSubmit :					CHECK( _drawCallConv->QueueSubmit( iter, frameId, *_tempPacker ));	break;

			case VKTRACE_TPI_VK_vkQueuePresentKHR :
			{
				const uint64_t	dt = iter->vktrace_begin_time - _lastUpdateTime;
				_lastUpdateTime = iter->vktrace_begin_time;

				CHECK( _OnBeginFrame( iter.GetBookmark(), frameId, *_tracePacker ));
				CHECK( _drawCallConv->QueuePresent( iter, frameId, *_tempPacker ));
				_tracePacker->Append( *_tempPacker );
				_tempPacker->Clear();
				CHECK( _OnEndFrame( dt, *_tracePacker ));
				break;
			}

			case VKTRACE_TPI_VK_vkDestroySurfaceKHR :
			case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate :
			case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :
			case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR :
			case VKTRACE_TPI_VK_vkCreateDisplayModeKHR :
			case VKTRACE_TPI_VK_vkCreateWaylandSurfaceKHR :
			case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplateKHR :
			case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR :
			case VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR :
			case VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR :
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :
			case VKTRACE_TPI_VK_vkDestroySwapchainKHR :
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :
			case VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR :
				break;


			case VKTRACE_TPI_MESSAGE :
			case VKTRACE_TPI_MARKER_CHECKPOINT :
			case VKTRACE_TPI_MARKER_API_BOUNDARY :
			case VKTRACE_TPI_MARKER_API_GROUP_BEGIN :
			case VKTRACE_TPI_MARKER_API_GROUP_END :
			case VKTRACE_TPI_MARKER_TERMINATE_PROCESS :
			case VKTRACE_TPI_PORTABILITY_TABLE :
			case VKTRACE_TPI_VK_vkApiVersion :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalImageFormatPropertiesNV :
			case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT :
			case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT :
			case VKTRACE_TPI_VK_vkDebugReportMessageEXT :
			case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT :
			case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT :
			case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT :
			case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT :
			case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT :
			case VKTRACE_TPI_VK_vkEnumeratePhysicalDevices :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties :
			case VKTRACE_TPI_VK_vkGetInstanceProcAddr :
			case VKTRACE_TPI_VK_vkGetDeviceProcAddr :
			case VKTRACE_TPI_VK_vkEnumerateInstanceExtensionProperties :
			case VKTRACE_TPI_VK_vkEnumerateDeviceExtensionProperties :
			case VKTRACE_TPI_VK_vkEnumerateInstanceLayerProperties :
			case VKTRACE_TPI_VK_vkEnumerateDeviceLayerProperties :
			case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment :
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements :
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties :
			case VKTRACE_TPI_VK_vkGetImageSubresourceLayout :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR :
			case VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR :
			case VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceWaylandPresentationSupportKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2KHR :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR :
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR :
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormats2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPropertiesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlanePropertiesKHR :
			case VKTRACE_TPI_VK_vkGetDisplayModePropertiesKHR :
			case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR :
			case VKTRACE_TPI_VK_vkGetMemoryFdKHR :
			case VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR :
			case VKTRACE_TPI_VK_vkImportSemaphoreFdKHR :
			case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR :
			case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR :
			case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX :
			case VKTRACE_TPI_VK_vkCmdSetDeviceMaskKHX :
			case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHX :
			case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHX :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHX :
			case VKTRACE_TPI_VK_vkCmdDispatchBaseKHX :
			case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHX :
			case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroupsKHX :
			case VKTRACE_TPI_VK_vkCmdProcessCommandsNVX :
			case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX :
			case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX :
			case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX :
			case VKTRACE_TPI_VK_vkCreateObjectTableNVX :
			case VKTRACE_TPI_VK_vkDestroyObjectTableNVX :
			case VKTRACE_TPI_VK_vkRegisterObjectsNVX :
			case VKTRACE_TPI_VK_vkUnregisterObjectsNVX :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX :
			case VKTRACE_TPI_VK_vkReleaseDisplayEXT :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT :
			case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE :
			case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE :
			case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT :
			case VKTRACE_TPI_VK_vkSetHdrMetadataEXT :
			case VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT :
			case VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT :
			case VKTRACE_TPI_VK_vkDisplayPowerControlEXT :
			case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT :
			case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT :
			case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT :
			case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR :
			case VKTRACE_TPI_VK_vkImportFenceFdKHR :
			case VKTRACE_TPI_VK_vkGetFenceFdKHR :
			case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR :
			case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT :
			case VKTRACE_TPI_VK_vkCreateValidationCacheEXT :
			case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT :
			case VKTRACE_TPI_VK_vkMergeValidationCachesEXT :
			case VKTRACE_TPI_VK_vkGetValidationCacheDataEXT :
			case VKTRACE_TPI_VK_vkGetShaderInfoAMD :
			case VKTRACE_TPI_VK_vkGetDeviceQueue2 :
			case VKTRACE_TPI_VK_vkEnumerateInstanceVersion :
			case VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport :
			case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR :
			case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR :
			case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures :
			case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroups :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFenceProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphoreProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlaneProperties2KHR :
			case VKTRACE_TPI_VK_vkGetDisplayModeProperties2KHR :
			case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilities2KHR :
			case VKTRACE_TPI_VK_vkGetRenderAreaGranularity :
			case VKTRACE_TPI_VK_vkMergePipelineCaches :
			case VKTRACE_TPI_VK_vkCreateInstance :
			case VKTRACE_TPI_VK_vkDestroyInstance :
			case VKTRACE_TPI_VK_vkCreateDevice :
			case VKTRACE_TPI_VK_vkDestroyDevice :
			case VKTRACE_TPI_VK_vkGetDeviceQueue :
			case VKTRACE_TPI_VK_vkCreatePipelineCache :
			case VKTRACE_TPI_VK_vkDestroyPipelineCache :
			case VKTRACE_TPI_VK_vkGetPipelineCacheData :
			case VKTRACE_TPI_VK_vkGetEventStatus :
			case VKTRACE_TPI_VK_vkGetQueryPoolResults :
			case VKTRACE_TPI_VK_vkGetFenceStatus :
				break;	// ignore
		}
		DISABLE_ENUM_CHECKS();

		return true;
	}


}	// VTC
