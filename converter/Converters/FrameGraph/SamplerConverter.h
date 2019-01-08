// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/FrameGraph/FrameGraphConverter.h"
#include "framegraph/Public/SamplerDesc.h"

namespace std
{
	template <>
	struct hash< FG::SamplerDesc >
	{
		ND_ size_t  operator () (const FG::SamplerDesc &x) const noexcept
		{
			return size_t(FG::HashOf( &x, sizeof(x) ));
		}
	};

}	// std

namespace FG
{
	ND_ bool operator == (const SamplerDesc &lhs, const SamplerDesc &rhs);
}	// FG

namespace VTC
{

	//
	// Sampler Converter
	//

	class FrameGraphConverter::SamplerConverter
	{
	// types
	private:
		using FGSamplers_t		= HashMap< SamplerDesc, RawSamplerID >;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		Array<RawSamplerID>		_remapping;
		FGSamplers_t			_fgSamplers;
		uint					_fgSamplerCounter	= 0;


	// methods
	public:
		explicit SamplerConverter (FrameGraphConverter &fg) : _fgConv{fg} {}

		bool Convert (TracePacker &packer) const;

		bool CreateSampler (const TraceRange::Iterator &);
		void DestroySampler (const TraceRange::Iterator &);
		bool CreateSamplerYcbcr (const TraceRange::Iterator &);
		void DestroySamplerYcbcr (const TraceRange::Iterator &);

		ND_ RawSamplerID  Remap (VkSampler id, TraceRange::Bookmark pos)	const	{ return Remap( ResourceID(id), pos ); }
		ND_ RawSamplerID  Remap (ResourceID id, TraceRange::Bookmark pos)	const;

		ND_ uint  GetSamplerCacheSize ()	const	{ return _fgSamplerCounter; }
	};


}	// VTC
