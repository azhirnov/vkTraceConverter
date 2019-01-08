// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/ImageConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "FGPack/FgStructPacker.h"

namespace VTC
{

/*
=================================================
	OnBeginFrame
----
	see unpacker in 'FGPlayer_v100::_CreateImage'
=================================================
*/
	bool FrameGraphConverter::ImageConverter::OnBeginFrame (TraceRange::Bookmark submitPos, FrameID frameId, TracePacker &packer)
	{
		if ( not _dummyColorImage2D )
			CHECK( _CreateDummyImages( packer ));

		for (auto iter = _pendingImages.begin(); iter != _pendingImages.end();)
		{
			if ( not iter->memBinded ) {
				++iter;
				continue;
			}

			packer.Begin( EPacketID::FgCreateImage );
			packer << uint(0);	// TODO: thread id
			packer << iter->id;
			packer << iter->uid;
			FGPack_ImageDesc( iter->desc, packer );
			FGPack_MemoryDesc( iter->mem, packer );
			packer.End( EPacketID::FgCreateImage );

			iter = _pendingImages.erase( iter );
		}

		for (auto& img : _hostImages)
		{
			CHECK_ERR( _UpdateImage( img, submitPos, frameId, packer ));
		}
		return true;
	}
	
/*
=================================================
	OnEndFrame
----
	see unpacker in 'FGPlayer_v100::_DestroyImage'
=================================================
*/
	bool FrameGraphConverter::ImageConverter::OnEndFrame (TracePacker &packer)
	{
		for (auto item : _readyToDelete)
		{
			packer.Begin( EPacketID::FgDestroyImage );
			packer << uint(0);	// TODO: thread id
			packer << item;
			packer.End( EPacketID::FgDestroyImage );

			_freeIndices.push_back( item );
		}

		_readyToDelete.clear();
		return true;
	}
	
/*
=================================================
	CreateImage
=================================================
*/
	bool FrameGraphConverter::ImageConverter::CreateImage (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCreateImage>();
		
		auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, ResourceID(*packet.pImage), pos.GetBookmark() );
		auto*	image	 = _fgConv._imageAnalyzer->GetImage( ResourceID(*packet.pImage), pos.GetBookmark() );
		CHECK_ERR( image and resource );
		
		uint			index	= 0;
		FG::ImageDesc	img_desc;
		
		if ( not _freeIndices.empty() ) {
			index = _freeIndices.back();
			_freeIndices.pop_back();
		}else
			index = _imageCounter++;
		
		img_desc.imageType	= FGEnumCast( image->createInfo.imageType, image->createInfo.flags, image->createInfo.arrayLayers, image->createInfo.samples );
		img_desc.dimension	= { image->createInfo.extent.width, image->createInfo.extent.height, image->createInfo.extent.depth };
		img_desc.format		= FGEnumCast( image->createInfo.format );
		img_desc.usage		= FGEnumCast( VkImageUsageFlagBits(image->createInfo.usage) );
		img_desc.arrayLayers= ImageLayer{ image->createInfo.arrayLayers };
		img_desc.maxLevel	= MipmapLevel{ image->createInfo.mipLevels };
		img_desc.samples	= FGEnumCast( image->createInfo.samples );
		
		CHECK( img_desc.format != EPixelFormat::Unknown );
		CHECK( img_desc.usage != EImageUsage::Unknown );
		CHECK(All( img_desc.dimension > uint3(0) ));
		CHECK( img_desc.maxLevel.Get() > 0 );
		CHECK( img_desc.arrayLayers.Get() > 0 );

		_pendingImages.push_back({ resource->uniqueIndex, index, img_desc, FG::MemoryDesc{}, false });
		return true;
	}
	
/*
=================================================
	DestroyImage
=================================================
*/
	bool FrameGraphConverter::ImageConverter::DestroyImage (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkDestroyImage>();
		
		auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, ResourceID(packet.image), pos.GetBookmark() );
		CHECK_ERR( resource );

		auto	result = _remapping[resource->localIndex];
		if ( not result )
			return true;

		_readyToDelete.push_back( result.Index() );

		for (auto iter = _hostImages.begin(); iter != _hostImages.end();)
		{
			if ( iter->image->id == ResourceID(packet.image) )
				iter = _hostImages.erase( iter );
			else
				++iter;
		}
		return true;
	}
	
/*
=================================================
	BindMemory
=================================================
*/
	bool FrameGraphConverter::ImageConverter::BindMemory (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkBindImageMemory>();

		for (auto& item : _pendingImages)
		{
			auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, ResourceID(packet.image), pos.GetBookmark() );

			if ( not resource or item.uid != resource->uniqueIndex or item.memBinded )
				continue;

			auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), pos.GetBookmark() );
			CHECK_ERR( mem );
			
			if ( mem->usage == EMemoryUsage::HostRead )
				continue;
			
			item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated :
							  EnumEq( mem->usage, EMemoryUsage::HostWrite ) ? EMemoryType::HostWrite : EMemoryType::Default;
			item.mem.poolId = MemPoolID{ ToString<16>( mem->id )};
			item.memBinded	= true;
			
			_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
			_remapping[resource->localIndex] = RawImageID{ item.id, 0 };

			_AddHostImage( packet.image, mem, pos.GetBookmark() );
			break;
		}
		return true;
	}
	
/*
=================================================
	BindMemory2
=================================================
*/
	bool FrameGraphConverter::ImageConverter::BindMemory2 (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkBindImageMemory2>();

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			for (auto& item : _pendingImages)
			{
				auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, ResourceID(packet.pBindInfos[i].image), pos.GetBookmark() );

				if ( not resource or item.uid != resource->uniqueIndex or item.memBinded )
					continue;

				auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.pBindInfos[i].memory), pos.GetBookmark() );
				CHECK_ERR( mem );
				
				if ( mem->usage == EMemoryUsage::HostRead )
					continue;
				
				item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated :
								  EnumEq( mem->usage, EMemoryUsage::HostWrite ) ? EMemoryType::HostWrite : EMemoryType::Default;
				item.mem.poolId = MemPoolID{ ToString<16>( mem->id )};
				item.memBinded	= true;
				
				_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
				_remapping[resource->localIndex] = RawImageID{ item.id, 0 };

				_AddHostImage( packet.pBindInfos[i].image, mem, pos.GetBookmark() );
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	GetSwapchainImages
=================================================
*/
	bool FrameGraphConverter::ImageConverter::GetSwapchainImages (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkGetSwapchainImagesKHR>();

		if ( packet.pSwapchainImages == null )
			return true;	// images is not created yet

		auto*	swapchain	= _fgConv._swapchainAnalyzer->GetSwapchain( ResourceID(packet.swapchain), pos.GetBookmark() );
		CHECK_ERR( swapchain );

		uint	index	= 0;
		if ( not _freeIndices.empty() ) {
			index = _freeIndices.back();
			_freeIndices.pop_back();
		}else
			index = _imageCounter++;

		FG::ImageDesc	img_desc;
		img_desc.imageType	= EImage::Tex2D;
		img_desc.dimension	= { swapchain->createInfo.imageExtent.width, swapchain->createInfo.imageExtent.height, 1 };
		img_desc.format		= FGEnumCast( swapchain->createInfo.imageFormat );
		img_desc.usage		= FGEnumCast( VkImageUsageFlagBits(swapchain->createInfo.imageUsage) ) | EImageUsage::TransferSrc;	// for blit source
		img_desc.arrayLayers= ImageLayer{1};
		img_desc.maxLevel	= MipmapLevel{1};
		img_desc.samples	= MultiSamples{1};

		_pendingImages.push_back({ 0, index, img_desc, MemoryDesc{}, true });

		for (auto& sw_image : swapchain->images)
		{
			auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, sw_image.id, pos.GetBookmark() );
			auto*	image	 = _fgConv._imageAnalyzer->GetImage( sw_image.id, pos.GetBookmark() );
			CHECK_ERR( image and resource );
		
			_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
			_remapping[resource->localIndex] = RawImageID{ index, 0 };
		}
		return true;
	}

/*
=================================================
	Remap
=================================================
*/
	RawImageID  FrameGraphConverter::ImageConverter::Remap (ResourceID id, TraceRange::Bookmark pos) const
	{
		auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_IMAGE, id, pos );
		CHECK_ERR( resource );

		auto	result = _remapping[resource->localIndex];
		CHECK_ERR( result );

		return result;
	}
	
/*
=================================================
	_AddHostImage
=================================================
*/
	bool FrameGraphConverter::ImageConverter::_AddHostImage (VkImage imageId, MemoryObjAnalyzer::MemoryObjInfo_t const* mem, TraceRange::Bookmark pos)
	{
		using EMemoryUsage = MemoryObjAnalyzer::EMemoryUsage;

		auto*	img = _fgConv._imageAnalyzer->GetImage( ResourceID(imageId), pos );
		CHECK_ERR( img and mem );
		
		if ( not EnumAny( mem->usage, EMemoryUsage::HostRead | EMemoryUsage::HostWrite ))
			return false;

		if ( not EnumAny( img->createInfo.usage, ~(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT) ))
			return false;

		_hostImages.push_back({ img, mem, mem->FirstBookmark().pos });
		return true;
	}
	
/*
=================================================
	_UpdateImage
=================================================
*/
	bool FrameGraphConverter::ImageConverter::_UpdateImage (const HostAccessibleImage &imageInfo, TraceRange::Bookmark submitPos, FrameID frameId, INOUT TracePacker &packer)
	{
		return false;
	}


}	// VTC
