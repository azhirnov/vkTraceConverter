// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/SamplerConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "FGPack/FgStructPacker.h"

namespace FG
{

/*
=================================================
	operator == (SamplerDesc)
=================================================
*/
	bool operator == (const SamplerDesc &lhs, const SamplerDesc &rhs)
	{
		return	lhs.magFilter				== rhs.magFilter		and
				lhs.minFilter				== rhs.minFilter		and
				lhs.mipmapMode				== rhs.mipmapMode		and
				All( lhs.addressMode		== rhs.addressMode )	and
				lhs.mipLodBias				== rhs.mipLodBias		and
				lhs.maxAnisotropy.has_value() == rhs.maxAnisotropy.has_value()			and
				(lhs.maxAnisotropy.has_value() ? *lhs.maxAnisotropy == *rhs.maxAnisotropy : true)	and
				lhs.compareOp.has_value()	== rhs.compareOp.has_value()				and
				(lhs.compareOp.has_value() ? *lhs.compareOp == rhs.compareOp : true)	and
				lhs.minLod					== rhs.minLod			and
				lhs.maxLod					== rhs.maxLod			and
				lhs.borderColor				== rhs.borderColor		and
				lhs.unnormalizedCoordinates	== rhs.unnormalizedCoordinates;
	}

}	// FG


namespace VTC
{

/*
=================================================
	Convert
=================================================
*/
	bool FrameGraphConverter::SamplerConverter::Convert (TracePacker &packer) const
	{
		for (auto& samp : _fgSamplers)
		{
			packer.Begin( EPacketID::FgCreateSampler );
			packer << uint(0);	// TODO: thread id
			packer << samp.second.Index();
			FGPack_SamplerDesc( samp.first, packer );
			packer.End( EPacketID::FgCreateSampler );
		}
		return true;
	}

/*
=================================================
	CreateSampler
=================================================
*/
	bool FrameGraphConverter::SamplerConverter::CreateSampler (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCreateSampler>();
		auto&	ci		= *packet.pCreateInfo;
		
		auto*	sampler = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_SAMPLER, ResourceID(*packet.pSampler), pos.GetBookmark() );
		CHECK_ERR( sampler );

		ASSERT( ci.flags == 0 );
		ASSERT( ci.pNext == null );

		SamplerDesc		desc;
		desc.magFilter		= FGEnumCast( ci.magFilter );
		desc.minFilter		= FGEnumCast( ci.minFilter );
		desc.mipmapMode		= FGEnumCast( ci.mipmapMode );
		desc.addressMode.x	= FGEnumCast( ci.addressModeU );
		desc.addressMode.y	= FGEnumCast( ci.addressModeV );
		desc.addressMode.z	= FGEnumCast( ci.addressModeW );
		desc.mipLodBias		= ci.mipLodBias;
		desc.minLod			= ci.minLod;
		desc.maxLod			= ci.maxLod;
		desc.borderColor	= FGEnumCast( ci.borderColor );
		desc.unnormalizedCoordinates	= ci.unnormalizedCoordinates;

		if ( ci.anisotropyEnable )
			desc.maxAnisotropy = ci.maxAnisotropy;

		if ( ci.compareEnable )
			desc.compareOp = FGEnumCast( ci.compareOp );

		auto	iter = _fgSamplers.find( desc );
		
		if ( iter == _fgSamplers.end() )
		{
			iter = _fgSamplers.insert_or_assign( desc, RawSamplerID{_fgSamplerCounter++, 0} ).first;
		}

		_remapping.resize(Max( sampler->localIndex+1, _remapping.size() ));
		_remapping[sampler->localIndex] = iter->second;

		return true;
	}
	
/*
=================================================
	DestroySampler
=================================================
*/
	void FrameGraphConverter::SamplerConverter::DestroySampler (const TraceRange::Iterator &)
	{
	}
	
/*
=================================================
	CreateSamplerYcbcr
=================================================
*/
	bool FrameGraphConverter::SamplerConverter::CreateSamplerYcbcr (const TraceRange::Iterator &)
	{
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	DestroySamplerYcbcr
=================================================
*/
	void FrameGraphConverter::SamplerConverter::DestroySamplerYcbcr (const TraceRange::Iterator &)
	{
	}
	
/*
=================================================
	Remap
=================================================
*/
	RawSamplerID  FrameGraphConverter::SamplerConverter::Remap (ResourceID id, TraceRange::Bookmark pos) const
	{
		auto*	sampler = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_SAMPLER, id, pos );
		CHECK_ERR( sampler );

		RawSamplerID	result = _remapping[sampler->localIndex];
		CHECK_ERR( result );

		return result;
	}
	

}	// VTC
