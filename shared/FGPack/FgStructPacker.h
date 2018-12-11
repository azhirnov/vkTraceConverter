// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "framegraph/Public/SamplerDesc.h"
#include "framegraph/Public/MemoryDesc.h"
#include "framegraph/Public/BufferDesc.h"
#include "framegraph/Public/ImageDesc.h"
#include "framegraph/Public/RenderPassDesc.h"

namespace VTC
{

/*
=================================================
	FGPack_Rectangle
=================================================
*/
	template <typename T>
	inline void FGPack_Rectangle (const FG::Rectangle<T> &rect, TracePacker &packer)
	{
		packer << rect.left;	packer << rect.top;
		packer << rect.right;	packer << rect.bottom;
	}
	
/*
=================================================
	FGPack_Vec
=================================================
*/
	template <typename T, uint I>
	inline void FGPack_Vec (const FG::Vec<T,I> &vec, TracePacker &packer)
	{
		for (size_t i = 0; i < vec.size(); ++i) {
			packer << vec[i];
		}
	}
	
/*
=================================================
	FGPack_RGBAColor
=================================================
*/
	template <typename T>
	inline void FGPack_RGBAColor (const FG::RGBAColor<T> &col, TracePacker &packer)
	{
		packer << col.r;
		packer << col.g;
		packer << col.b;
		packer << col.a;
	}
	
/*
=================================================
	FGPack_DepthStencil
=================================================
*/
	inline void FGPack_DepthStencil (const FG::DepthStencil &ds, TracePacker &packer)
	{
		packer << ds.depth;
		packer << ds.stencil;
	}

/*
=================================================
	FGPack_SamplerDesc
=================================================
*/
	inline void FGPack_SamplerDesc (const FG::SamplerDesc &desc, TracePacker &packer)
	{
		packer << desc.magFilter;
		packer << desc.minFilter;
		packer << desc.mipmapMode;
		FGPack_Vec( desc.addressMode, packer );
		packer << desc.mipLodBias;

		packer << desc.maxAnisotropy.has_value();
		packer << desc.compareOp.has_value();

		if ( desc.maxAnisotropy.has_value() )
			packer << desc.maxAnisotropy.value();

		if ( desc.compareOp.has_value() )
			packer << desc.compareOp.value();

		packer << desc.minLod;
		packer << desc.maxLod;
		packer << desc.borderColor;
		packer << desc.unnormalizedCoordinates;
	}
	
/*
=================================================
	FGPack_MemoryDesc
=================================================
*/
	inline void FGPack_MemoryDesc (const FG::MemoryDesc &desc, TracePacker &packer)
	{
		packer << desc.type;
		packer << desc.poolId;
	}
	
/*
=================================================
	FGPack_ImageDesc
=================================================
*/
	inline void FGPack_ImageDesc (const FG::ImageDesc &desc, TracePacker &packer)
	{
		ASSERT( desc.format != EPixelFormat::Unknown );
		ASSERT( desc.usage != EImageUsage::Unknown );
		ASSERT(All( desc.dimension > uint3(0) ));
		ASSERT( desc.maxLevel.Get() > 0 );
		ASSERT( desc.arrayLayers.Get() > 0 );

		packer << desc.imageType;
		FGPack_Vec( desc.dimension, packer );
		packer << desc.format;
		packer << desc.usage;
		packer << desc.arrayLayers.Get();
		packer << desc.maxLevel.Get();
		packer << desc.samples.Get();
	}
	
/*
=================================================
	FGPack_ImageViewDesc
=================================================
*/
	inline void FGPack_ImageViewDesc (const FG::ImageViewDesc &desc, TracePacker &packer)
	{
		ASSERT( desc.format != EPixelFormat::Unknown );
		ASSERT( desc.levelCount > 0 );
		ASSERT( desc.layerCount > 0 );

		packer << desc.viewType;
		packer << desc.format;
		packer << desc.baseLevel.Get();
		packer << desc.levelCount;
		packer << desc.baseLayer.Get();
		packer << desc.layerCount;
		packer << BitCast<uint>( desc.swizzle );
	}

/*
=================================================
	FGPack_BufferDesc
=================================================
*/
	inline void FGPack_BufferDesc (const FG::BufferDesc &desc, TracePacker &packer)
	{
		ASSERT( desc.size > 0 );
		ASSERT( desc.usage != EBufferUsage::Unknown );

		packer << uint64_t(desc.size);
		packer << desc.usage;
	}
	
/*
=================================================
	FGPack_ImageSubresourceRange
=================================================
*/
	inline void FGPack_ImageSubresourceRange (const VkImageSubresourceLayers &src, TracePacker &packer)
	{
		ASSERT( src.layerCount > 0 );

		// pack as 'FG::ImageSubresourceRange'
		packer << FGEnumCast( VkImageAspectFlagBits(src.aspectMask) );
		packer << src.mipLevel;
		packer << src.baseArrayLayer;
		packer << src.layerCount;
	}
	
/*
=================================================
	FGPack_Offset3D
=================================================
*/
	inline void FGPack_Offset3D (const VkOffset3D &src, TracePacker &packer)
	{
		// pack as 'FG::int3'
		packer << src.x;
		packer << src.y;
		packer << src.z;
	}
	
/*
=================================================
	FGPack_Extent3D
=================================================
*/
	inline void FGPack_Extent3D (const VkExtent3D &src, TracePacker &packer)
	{
		ASSERT( src.width > 0 and src.height > 0 and src.depth > 0 );

		// pack as 'FG::uint3'
		packer << src.width;
		packer << src.height;
		packer << src.depth;
	}
	
/*
=================================================
	FGPack_BufferImageCopy_Region
=================================================
*/
	inline void FGPack_BufferImageCopy_Region (const VkBufferImageCopy &src, TracePacker &packer)
	{
		// pack 'CopyBufferToImage::Region'
		packer << src.bufferOffset;
		packer << src.bufferRowLength;
		packer << src.bufferImageHeight;
		FGPack_ImageSubresourceRange( src.imageSubresource, INOUT packer );
		FGPack_Offset3D( src.imageOffset, INOUT packer );
		FGPack_Extent3D( src.imageExtent, INOUT packer );
	}
	
/*
=================================================
	FGPack_VertexInputState
=================================================
*/
	inline void FGPack_VertexInputState (const FG::VertexInputState &state, TracePacker &packer)
	{
		packer << uint(state.BufferBindings().size());
		packer << uint(state.Vertices().size());

		for (auto& buf : state.BufferBindings())
		{
			ASSERT( buf.first.IsDefined() );
			ASSERT( buf.second.stride > 0 );

			packer << buf.first;
			packer << uint(buf.second.stride);
			packer << buf.second.index;
			packer << buf.second.rate;
		}

		for (auto& vert : state.Vertices())
		{
			ASSERT( vert.first.IsDefined() );

			packer << vert.first;
			packer << vert.second.type;
			packer << vert.second.index;
			packer << uint(vert.second.offset);
			packer << vert.second.bindingIndex;
		}
	}
	
/*
=================================================
	FGPack_ColorBuffersState
=================================================
*/
	inline void FGPack_ColorBuffer (const FG::RenderState::ColorBuffer &cb, TracePacker &packer)
	{
		packer << cb.srcBlendFactor.color;		packer << cb.srcBlendFactor.alpha;
		packer << cb.dstBlendFactor.color;		packer << cb.dstBlendFactor.alpha;
		packer << cb.blendOp.color;				packer << cb.blendOp.alpha;
		FGPack_Vec( cb.colorMask, packer );		packer << cb.blend;
	}
	
/*
=================================================
	FGPack_ColorBuffersState
=================================================
*/
	inline void FGPack_ColorBuffersState (const FG::RenderState::ColorBuffersState &state, TracePacker &packer)
	{
		packer << uint(state.buffers.size());
		for (auto& cb : state.buffers) {
			packer << cb.first;
			FGPack_ColorBuffer( cb.second, packer );
		}
		packer << state.logicOp;
		FGPack_RGBAColor( state.blendColor, packer );
	}
	
/*
=================================================
	FGPack_DepthBufferState
=================================================
*/
	inline void FGPack_DepthBufferState (const FG::RenderState::DepthBufferState &state, TracePacker &packer)
	{
		packer << state.compareOp;
		FGPack_Vec( state.bounds, packer );
		packer << state.boundsEnabled;
		packer << state.write;
		packer << state.test;
	}
	
/*
=================================================
	FGPack_StencilBufferState
=================================================
*/
	inline void FGPack_StencilBufferState (const FG::RenderState::StencilBufferState &state, TracePacker &packer)
	{
		packer << state.front.failOp;
		packer << state.front.depthFailOp;
		packer << state.front.passOp;
		packer << state.front.compareOp;
		packer << state.front.reference;
		packer << state.front.writeMask;
		packer << state.front.compareMask;
		
		packer << state.back.failOp;
		packer << state.back.depthFailOp;
		packer << state.back.passOp;
		packer << state.back.compareOp;
		packer << state.back.reference;
		packer << state.back.writeMask;
		packer << state.back.compareMask;

		packer << state.enabled;
	}
	
/*
=================================================
	FGPack_RasterizationState
=================================================
*/
	inline void FGPack_RasterizationState (const FG::RenderState::RasterizationState &state, TracePacker &packer)
	{
		packer << state.polygonMode;
		packer << state.lineWidth;
		packer << state.depthBiasConstFactor;
		packer << state.depthBiasClamp;
		packer << state.depthBiasSlopeFactor;
		packer << state.depthBias;
		packer << state.depthClamp;
		packer << state.rasterizerDiscard;
		packer << state.frontFaceCCW;
		packer << state.cullMode;
	}
	
/*
=================================================
	FGPack_MultisampleState
=================================================
*/
	inline void FGPack_MultisampleState (const FG::RenderState::MultisampleState &state, TracePacker &packer)
	{
		for (auto& mask : state.sampleMask) {
			packer << mask;
		}
		packer << state.samples.Get();
		packer << state.minSampleShading;
		packer << state.sampleShading;
		packer << state.alphaToCoverage;
		packer << state.alphaToOne;
	}
	
/*
=================================================
	FGPack_RenderPassTraget
----
	see unpacker in 'FGPlayer_v100::_CreateRenderPass'
=================================================
*/
	inline void FGPack_RenderPassTraget (const FG::RenderPassDesc::RT &rt, TracePacker &packer)
	{
		ASSERT( rt.desc.has_value() );

		packer << rt.image.Index();
		FGPack_ImageViewDesc( *rt.desc, packer );
		packer << uint(rt.clearValue.index());
		Visit( rt.clearValue,
			   [&packer] (const RGBA32f &col)		{ FGPack_RGBAColor( col, packer ); },
			   [&packer] (const RGBA32u &col)		{ FGPack_RGBAColor( col, packer ); },
			   [&packer] (const RGBA32i &col)		{ FGPack_RGBAColor( col, packer ); },
			   [&packer] (const DepthStencil &ds)	{ FGPack_DepthStencil( ds, packer ); },
			   [&packer] (const std::monostate &)	{}
			  );
		packer << rt.loadOp;
		packer << rt.storeOp;
	}
	
/*
=================================================
	FGPack_ClearColor
=================================================
*/
	inline void FGPack_ClearColor (const VkClearColorValue &cv, VkFormat format, TracePacker &packer)
	{
		using EType = PixelFormatInfo::EType;

		const auto	type = EPixelFormat_GetInfo( FGEnumCast( format )).valueType;
		ASSERT( EnumAny( type, EType::DepthStencil ));

		switch ( type & EType::_ValueMask )
		{
			case EType::SFloat :
			case EType::UFloat :
			case EType::UNorm :
			case EType::SNorm :
				packer << uint(FG::TypeList< ClearColorImage::ClearColor_t >::Index<RGBA32f>);
				FGPack_RGBAColor( RGBA32f{ cv.float32[0], cv.float32[0], cv.float32[0], cv.float32[0] }, INOUT packer );
				break;

			case EType::Int :
				packer << uint(FG::TypeList< ClearColorImage::ClearColor_t >::Index<RGBA32i>);
				FGPack_RGBAColor( RGBA32i{ cv.int32[0], cv.int32[0], cv.int32[0], cv.int32[0] }, INOUT packer );
				break;

			case EType::UInt :
				packer << uint(FG::TypeList< ClearColorImage::ClearColor_t >::Index<RGBA32u>);
				FGPack_RGBAColor( RGBA32u{ cv.uint32[0], cv.uint32[0], cv.uint32[0], cv.uint32[0] }, INOUT packer );
				break;

			default :
				RETURN_ERR( "unsupported color format", void());
		}
	}

/*
=================================================
	FGPack_RenderPassViewport
=================================================
*/
	inline void FGPack_RenderPassViewport (const FG::RenderPassDesc::Viewport &vp, TracePacker &packer)
	{
		FGPack_Rectangle( vp.rect, packer );
		packer << vp.minDepth;
		packer << vp.maxDepth;
	}
	
/*
=================================================
	FGPack_PushConstantData
=================================================
*/
	inline void FGPack_PushConstantData (const _fg_hidden_::PushConstantData &pc, TracePacker &packer)
	{
		packer << pc.id;
		packer << uint(pc.size);
		packer.AddArray( pc.data, size_t(pc.size) );
	}
	
/*
=================================================
	FGPack_ClearColorImage_Range
=================================================
*/
	inline void FGPack_ClearColorImage_Range (const VkImageSubresourceRange &range, TracePacker &packer)
	{
		packer << FGEnumCast( range.aspectMask );
		packer << range.baseMipLevel;
		packer << range.levelCount;
		packer << range.baseArrayLayer;
		packer << range.layerCount;
	}
	
/*
=================================================
	FGPack_CopyImage_Region
=================================================
*/
	inline void FGPack_CopyImage_Region (const VkImageCopy &src, TracePacker &packer)
	{
		FGPack_ImageSubresourceRange( src.srcSubresource, INOUT packer );
		FGPack_Offset3D( src.srcOffset, INOUT packer );
		FGPack_ImageSubresourceRange( src.dstSubresource, INOUT packer );
		FGPack_Offset3D( src.dstOffset, INOUT packer );
		FGPack_Extent3D( src.extent, INOUT packer );
	}
	
/*
=================================================
	FGPack_ResolveImage_Region
=================================================
*/
	inline void FGPack_ResolveImage_Region (const VkImageResolve &src, TracePacker &packer)
	{
		FGPack_ImageSubresourceRange( src.srcSubresource, INOUT packer );
		FGPack_Offset3D( src.srcOffset, INOUT packer );
		FGPack_ImageSubresourceRange( src.dstSubresource, INOUT packer );
		FGPack_Offset3D( src.dstOffset, INOUT packer );
		FGPack_Extent3D( src.extent, INOUT packer );
	}
	
/*
=================================================
	FGPacket_BlitImage_Region
=================================================
*/
	inline void FGPacket_BlitImage_Region (const VkImageBlit &src, TracePacker &packer)
	{
		FGPack_ImageSubresourceRange( src.srcSubresource, INOUT packer );
		FGPack_Offset3D( src.srcOffsets[0], INOUT packer );
		FGPack_Offset3D( src.srcOffsets[1], INOUT packer );
		FGPack_ImageSubresourceRange( src.dstSubresource, INOUT packer );
		FGPack_Offset3D( src.dstOffsets[0], INOUT packer );
		FGPack_Offset3D( src.dstOffsets[1], INOUT packer );
	}


}	// VTC
