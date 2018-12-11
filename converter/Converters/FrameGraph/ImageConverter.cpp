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
	bool FrameGraphConverter::ImageConverter::OnBeginFrame (TracePacker &packer)
	{
		for (auto& item : _pendingImages)
		{
			CHECK( item.memBinded );

			packer.Begin( EPacketID::FgCreateImage );
			packer << uint(0);	// TODO: thread id
			packer << item.id;
			FGPack_ImageDesc( item.desc, packer );
			FGPack_MemoryDesc( item.mem, packer );
			packer.End( EPacketID::FgCreateImage );
		}

		_pendingImages.clear();
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
		
		img_desc.imageType	= FGEnumCast( image->createInfo.imageType, image->createInfo.arrayLayers, image->createInfo.samples );
		img_desc.dimension	= { image->createInfo.extent.width, image->createInfo.extent.height, image->createInfo.extent.depth };
		img_desc.format		= FGEnumCast( image->createInfo.format );
		img_desc.usage		= FGEnumCast( VkImageUsageFlagBits(image->createInfo.usage) );
		img_desc.arrayLayers= ImageLayer{ image->createInfo.arrayLayers };
		img_desc.maxLevel	= MipmapLevel{ image->createInfo.mipLevels };
		img_desc.samples	= FGEnumCast( image->createInfo.samples );
		
		ASSERT( img_desc.format != EPixelFormat::Unknown );
		ASSERT( img_desc.usage != EImageUsage::Unknown );
		ASSERT(All( img_desc.dimension > uint3(0) ));
		ASSERT( img_desc.maxLevel.Get() > 0 );
		ASSERT( img_desc.arrayLayers.Get() > 0 );

		_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
		_remapping[resource->localIndex] = RawImageID{ index, 0 };

		_pendingImages.push_back({ *packet.pImage, index, img_desc, FG::MemoryDesc{}, false });
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

		_readyToDelete.push_back( Remap( packet.image, pos.GetBookmark() ).Index() );
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
			if ( packet.image != item.handle )
				continue;

			auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), pos.GetBookmark() );
			CHECK_ERR( mem );
			CHECK_ERR( not item.memBinded );

			item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated : EMemoryType::Default;
			item.mem.poolId = MemPoolID{ ToString( mem->id )};
			item.memBinded	= true;
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
				if ( item.handle != packet.pBindInfos[i].image )
					continue;

				auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.pBindInfos[i].memory), pos.GetBookmark() );
				CHECK_ERR( mem );
				CHECK_ERR( not item.memBinded );

				item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated : EMemoryType::Default;
				item.mem.poolId = MemPoolID{ ToString( mem->id )};
				item.memBinded	= true;
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
		img_desc.usage		= FGEnumCast( VkImageUsageFlagBits(swapchain->createInfo.imageUsage) );
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


}	// VTC
