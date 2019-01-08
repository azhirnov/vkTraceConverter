// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

namespace VTPlayer
{

/*
=================================================
	FGUnpack_Rectangle
=================================================
*/
	template <typename T>
	inline void FGUnpack_Rectangle (OUT FG::Rectangle<T> &rect, FGUnpacker &unpacker)
	{
		rect.left << unpacker;		rect.top << unpacker;
		rect.right << unpacker;		rect.bottom << unpacker;
	}
	
/*
=================================================
	FGUnpack_Vec
=================================================
*/
	template <typename T, uint I>
	inline void FGUnpack_Vec (OUT FG::Vec<T,I> &vec, FGUnpacker &unpacker)
	{
		for (size_t i = 0; i < vec.size(); ++i) {
			vec[i] << unpacker;
		}
	}
	
/*
=================================================
	FGUnpack_RGBAColor
=================================================
*/
	template <typename T>
	inline void FGUnpack_RGBAColor (OUT FG::RGBAColor<T> &col, FGUnpacker &unpacker)
	{
		col.r << unpacker;
		col.g << unpacker;
		col.b << unpacker;
		col.a << unpacker;
	}
	
/*
=================================================
	FGUnpack_DepthStencil
=================================================
*/
	inline void FGUnpack_DepthStencil (OUT FG::DepthStencil &ds, FGUnpacker &unpacker)
	{
		ds.depth << unpacker;
		ds.stencil << unpacker;
	}

/*
=================================================
	FGUnpack_SamplerDesc
=================================================
*/
	void FGUnpack_SamplerDesc (OUT FG::SamplerDesc &desc, FGUnpacker &unpacker)
	{
		desc.magFilter << unpacker;
		desc.minFilter << unpacker;
		desc.mipmapMode << unpacker;
		desc.addressMode.x << unpacker;
		desc.addressMode.y << unpacker;
		desc.addressMode.z << unpacker;
		desc.mipLodBias << unpacker;

		const bool	has_anisotropy	= unpacker.Get<bool>();
		const bool	has_compare_op	= unpacker.Get<bool>();

		if ( has_anisotropy )
			desc.maxAnisotropy = unpacker.Get<float>();

		if ( has_compare_op )
			desc.compareOp = unpacker.Get<ECompareOp>();

		desc.minLod << unpacker;
		desc.maxLod << unpacker;
		desc.borderColor << unpacker;
		desc.unnormalizedCoordinates << unpacker;
	}
	
/*
=================================================
	FGUnpack_MemoryDesc
=================================================
*/
	void FGUnpack_MemoryDesc (OUT FG::MemoryDesc &desc, FGUnpacker &unpacker)
	{
		desc.type << unpacker;
		desc.poolId << unpacker;
	}
	
/*
=================================================
	FGUnpack_ImageDesc
=================================================
*/
	void FGUnpack_ImageDesc (OUT FG::ImageDesc &desc, FGUnpacker &unpacker)
	{
		desc.imageType << unpacker;
		desc.dimension.x << unpacker;
		desc.dimension.y << unpacker;
		desc.dimension.z << unpacker;
		desc.format << unpacker;
		desc.usage << unpacker;
		desc.arrayLayers = ImageLayer{ unpacker.Get<uint>() };
		desc.maxLevel = MipmapLevel{ unpacker.Get<uint>() };
		desc.samples = MultiSamples{ unpacker.Get<uint>() };

		ASSERT( desc.format != Default );
		ASSERT( desc.usage != Default );
		ASSERT(All( desc.dimension > uint3(0) ));
		ASSERT( desc.arrayLayers.Get() > 0 );
		ASSERT( desc.maxLevel.Get() > 0 );
	}
	
/*
=================================================
	FGUnpack_ImageViewDesc
=================================================
*/
	inline void FGUnpack_ImageViewDesc (OUT FG::ImageViewDesc &desc, FGUnpacker &unpacker)
	{
		desc.viewType << unpacker;
		desc.format << unpacker;
		desc.baseLevel = MipmapLevel{ unpacker.Get<uint>() };
		desc.levelCount << unpacker;
		desc.baseLayer = ImageLayer{ unpacker.Get<uint>() };
		desc.layerCount << unpacker;
		desc.swizzle = BitCast<ImageSwizzle>( unpacker.Get<uint>() );
		desc.aspectMask << unpacker;
		
		ASSERT( desc.format != Default );
		ASSERT( desc.levelCount > 0 );
		ASSERT( desc.layerCount > 0 );
		ASSERT( desc.aspectMask != Default );
	}

/*
=================================================
	FGUnpack_BufferDesc
=================================================
*/
	void FGUnpack_BufferDesc (OUT FG::BufferDesc &desc, FGUnpacker &unpacker)
	{
		desc.size = BytesU{ unpacker.Get<uint64_t>() };
		desc.usage << unpacker;

		ASSERT( desc.size > 0 );
		ASSERT( desc.usage != EBufferUsage::Unknown );
	}
	
/*
=================================================
	FGUnpack_ImageSubresourceRange
=================================================
*/
	void FGUnpack_ImageSubresourceRange (OUT FG::ImageSubresourceRange &result, FGUnpacker &unpacker)
	{
		result.aspectMask << unpacker;
		result.mipLevel = MipmapLevel{ unpacker.Get<uint>() };
		result.baseLayer = ImageLayer{ unpacker.Get<uint>() };
		result.layerCount << unpacker;

		ASSERT( result.layerCount > 0 );
	}
	
/*
=================================================
	FGUnpack_BufferImageCopy_Region
=================================================
*/
	inline void FGUnpack_BufferImageCopy_Region (OUT FG::CopyBufferToImage::Region &result, FGUnpacker &unpacker)
	{
		result.bufferOffset = BytesU{ unpacker.Get<uint64_t>() };
		result.bufferRowLength = unpacker.Get<uint>();
		result.bufferImageHeight = unpacker.Get<uint>();
		FGUnpack_ImageSubresourceRange( OUT result.imageLayers, unpacker );
		FGUnpack_Vec( OUT result.imageOffset, unpacker );
		FGUnpack_Vec( OUT result.imageSize, unpacker );

		ASSERT(All( result.imageSize > uint3(0) ));
	}
	
/*
=================================================
	FGUnpack_CopyImage_Region
=================================================
*/
	inline void FGUnpack_CopyImage_Region (OUT FG::CopyImage::Region &result, FGUnpacker &unpacker)
	{
		FGUnpack_ImageSubresourceRange( OUT result.srcSubresource, unpacker );
		FGUnpack_Vec( OUT result.srcOffset, unpacker );
		FGUnpack_ImageSubresourceRange( OUT result.dstSubresource, unpacker );
		FGUnpack_Vec( OUT result.dstOffset, unpacker );
		FGUnpack_Vec( OUT result.size, unpacker );
	}

/*
=================================================
	FGUnpack_VertexInputState
=================================================
*/
	inline void FGUnpack_VertexInputState (OUT FG::VertexInputState &result, FGUnpacker &unpacker)
	{
		const uint	buf_count	= unpacker.Get<uint>();
		const uint	vert_count	= unpacker.Get<uint>();
		ASSERT( buf_count <= FG_MaxVertexBuffers );
		ASSERT( vert_count <= FG_MaxAttribs );

		for (uint i = 0; i < buf_count; ++i)
		{
			VertexBufferID	id;		id << unpacker;
			const auto		stride	= Bytes<uint>{ unpacker.Get<uint>() };
			const auto		index	= unpacker.Get<uint>();
			const auto		rate	= unpacker.Get<EVertexInputRate>();

			result.Bind( id, stride, index, rate );
		}
		
		for (uint i = 0; i < vert_count; ++i)
		{
			VertexID		id;		id << unpacker;
			const auto		type	= unpacker.Get<EVertexType>();
			const auto		index	= unpacker.Get<uint>();
			const auto		offset	= BytesU{ unpacker.Get<uint>() };
			const auto		bind_idx= unpacker.Get<uint>();
			VertexBufferID	buf_id	{ "vb"s + FG::ToString(bind_idx) };

			//CHECK( index == i );	// TODO
			result.Add( id, type, offset, buf_id );
		}
	}
	
/*
=================================================
	FGUnpack_ColorBuffersState
=================================================
*/
	inline void FGUnpack_ColorBuffer (OUT FG::RenderState::ColorBuffer &result, FGUnpacker &unpacker)
	{
		result.srcBlendFactor.color << unpacker;		result.srcBlendFactor.alpha << unpacker;
		result.dstBlendFactor.color << unpacker;		result.dstBlendFactor.alpha << unpacker;
		result.blendOp.color << unpacker;				result.blendOp.alpha << unpacker;
		FGUnpack_Vec( OUT result.colorMask, unpacker );	result.blend << unpacker;
	}
	
/*
=================================================
	FGUnpack_ColorBuffersState
=================================================
*/
	inline void FGUnpack_ColorBuffersState (OUT FG::RenderState::ColorBuffersState &result, FGUnpacker &unpacker)
	{
		const auto	count = unpacker.Get<uint>();

		for (uint i = 0; i < count; ++i)
		{
			RenderTargetID				id;	id << unpacker;
			RenderState::ColorBuffer	cb;
			FGUnpack_ColorBuffer( OUT cb, unpacker );

			result.buffers.insert({ id, cb });
		}

		result.logicOp << unpacker;
		FGUnpack_RGBAColor( OUT result.blendColor, unpacker );
	}
	
/*
=================================================
	FGUnpack_DepthBufferState
=================================================
*/
	inline void FGUnpack_DepthBufferState (OUT FG::RenderState::DepthBufferState &result, FGUnpacker &unpacker)
	{
		result.compareOp << unpacker;
		FGUnpack_Vec( OUT result.bounds, unpacker );
		result.boundsEnabled << unpacker;
		result.write << unpacker;
		result.test << unpacker;
	}
	
/*
=================================================
	FGUnpack_StencilBufferState
=================================================
*/
	inline void FGUnpack_StencilBufferState (OUT FG::RenderState::StencilBufferState &result, FGUnpacker &unpacker)
	{
		result.front.failOp << unpacker;
		result.front.depthFailOp << unpacker;
		result.front.passOp << unpacker;
		result.front.compareOp << unpacker;
		result.front.reference << unpacker;
		result.front.writeMask << unpacker;
		result.front.compareMask << unpacker;
		
		result.back.failOp << unpacker;
		result.back.depthFailOp << unpacker;
		result.back.passOp << unpacker;
		result.back.compareOp << unpacker;
		result.back.reference << unpacker;
		result.back.writeMask << unpacker;
		result.back.compareMask << unpacker;

		result.enabled << unpacker;
	}
	
/*
=================================================
	FGUnpack_RasterizationState
=================================================
*/
	inline void FGUnpack_RasterizationState (OUT FG::RenderState::RasterizationState &result, FGUnpacker &unpacker)
	{
		result.polygonMode << unpacker;
		result.lineWidth << unpacker;
		result.depthBiasConstFactor << unpacker;
		result.depthBiasClamp << unpacker;
		result.depthBiasSlopeFactor << unpacker;
		result.depthBias << unpacker;
		result.depthClamp << unpacker;
		result.rasterizerDiscard << unpacker;
		result.frontFaceCCW << unpacker;
		result.cullMode << unpacker;
	}
	
/*
=================================================
	FGUnpack_MultisampleState
=================================================
*/
	inline void FGUnpack_MultisampleState (OUT FG::RenderState::MultisampleState &result, FGUnpacker &unpacker)
	{
		for (auto& mask : result.sampleMask) {
			mask << unpacker;
		}
		result.samples = MultiSamples{ unpacker.Get<uint>() };
		result.minSampleShading << unpacker;
		result.sampleShading << unpacker;
		result.alphaToCoverage << unpacker;
		result.alphaToOne << unpacker;
	}
	
/*
=================================================
	FGUnpack_RenderPassViewport
=================================================
*/
	inline void FGUnpack_RenderPassViewport (OUT FG::RenderPassDesc::Viewport &result, FGUnpacker &unpacker)
	{
		FGUnpack_Rectangle( OUT result.rect, unpacker );
		result.minDepth << unpacker;
		result.maxDepth << unpacker;
	}
	
/*
=================================================
	FGUnpack_BlitImage_Region
=================================================
*/
	inline void FGUnpack_BlitImage_Region (OUT FG::BlitImage::Region &result, FGUnpacker &unpacker)
	{
		FGUnpack_ImageSubresourceRange( OUT result.srcSubresource, unpacker );
		FGUnpack_Vec( OUT result.srcOffset0, unpacker );
		FGUnpack_Vec( OUT result.srcOffset1, unpacker );
		FGUnpack_ImageSubresourceRange( OUT result.dstSubresource, unpacker );
		FGUnpack_Vec( OUT result.dstOffset0, unpacker );
		FGUnpack_Vec( OUT result.dstOffset1, unpacker );
	}
	
/*
=================================================
	FGUnpack_ResolveImage_Region
=================================================
*/
	inline void FGUnpack_ResolveImage_Region (OUT FG::ResolveImage::Region &result, FGUnpacker &unpacker)
	{
		FGUnpack_ImageSubresourceRange( OUT result.srcSubresource, unpacker );
		FGUnpack_Vec( OUT result.srcOffset, unpacker );
		FGUnpack_ImageSubresourceRange( OUT result.dstSubresource, unpacker );
		FGUnpack_Vec( OUT result.dstOffset, unpacker );
		FGUnpack_Vec( OUT result.extent, unpacker );
	}

/*
=================================================
	FGUnpack_ClearColorImage_Range
=================================================
*/
	inline void FGUnpack_ClearColorImage_Range (OUT FG::ClearColorImage::Range &result, FGUnpacker &unpacker)
	{
		result.aspectMask	<< unpacker;
		result.baseMipLevel	= MipmapLevel{ unpacker.Get<uint>() };
		result.levelCount	<< unpacker;
		result.baseLayer	= ImageLayer{ unpacker.Get<uint>() };
		result.layerCount	<< unpacker;
	}
	
/*
=================================================
	FGUnpack_ClearColor
=================================================
*/
	inline void FGUnpack_ClearColor (OUT FG::ClearColorImage::ClearColor_t &result, FGUnpacker &unpacker)
	{
		using ColorTypes = TypeList< ClearColorImage::ClearColor_t >;

		const auto	index = unpacker.Get<uint>();

		switch ( index )
		{
			case ColorTypes::Index<RGBA32f> :
			{
				RGBA32f		col;
				col.r << unpacker;	col.g << unpacker;	col.b << unpacker;	col.a << unpacker;
				result = col;
				break;
			}
			case ColorTypes::Index<RGBA32u> :
			{
				RGBA32u		col;
				col.r << unpacker;	col.g << unpacker;	col.b << unpacker;	col.a << unpacker;
				result = col;
				break;
			}
			case ColorTypes::Index<RGBA32i> :
			{
				RGBA32i		col;
				col.r << unpacker;	col.g << unpacker;	col.b << unpacker;	col.a << unpacker;
				result = col;
				break;
			}
			default :
				RETURN_ERR( "unsupported color type", void());
		}
	}
	
/*
=================================================
	FGUnpack_DrawTaskDynamicStates
=================================================
*/
	inline void FGUnpack_DrawTaskDynamicStates (OUT _fg_hidden_::DynamicStates &result, FGUnpacker &unpacker)
	{
		result = *unpacker.GetArray< _fg_hidden_::DynamicStates >( 1 );
	}

/*
=================================================
	FGUnpack_Optional
=================================================
*/
	template <typename T>
	inline void FGUnpack_Optional (OUT Optional<T> &result, FGUnpacker &unpacker)
	{
		if ( unpacker.Get<bool>() )
		{
			result = unpacker.Get<T>();
		}
	}

	
}	// VTC
