// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/FrameGraph/FrameGraphConverter.h"
#include "framegraph/Public/MemoryDesc.h"
#include "framegraph/Public/ImageDesc.h"

namespace VTC
{

	//
	// Image Converter
	//

	class FrameGraphConverter::ImageConverter
	{
	// types
	private:
		struct PendingImage
		{
			uint64_t			uid			= UMax;
			uint				id			= UMax;
			FG::ImageDesc		desc;
			FG::MemoryDesc		mem;
			bool				memBinded	= false;
		};

		struct HostAccessibleImage
		{
			ImageAnalyzer::ImageInfo_t const*			image		= null;
			MemoryObjAnalyzer::MemoryObjInfo_t const*	memory		= null;
			TraceRange::Bookmark						lastPos;
		};

		using PendingImages_t	= Array< PendingImage >;
		using IndexArray_t		= Array< uint >;
		using HosteImages_t		= Array< HostAccessibleImage >;
		using EMemoryUsage		= MemoryObjAnalyzer::EMemoryUsage;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		PendingImages_t			_pendingImages;
		IndexArray_t			_readyToDelete;
		IndexArray_t			_freeIndices;

		Array<RawImageID>		_remapping;
		
		HosteImages_t			_hostImages;

		uint					_imageCounter	= 0;

		RawImageID				_dummyColorImage2D;
		ImageDesc				_dummyColorImage2DDesc;


	// methods
	public:
		explicit ImageConverter (FrameGraphConverter &fgConv) : _fgConv{fgConv} {}
		
		bool OnBeginFrame (TraceRange::Bookmark, FrameID, TracePacker &packer);
		bool OnEndFrame (TracePacker &packer);

		bool CreateImage (const TraceRange::Iterator &);
		bool DestroyImage (const TraceRange::Iterator &);
		bool BindMemory (const TraceRange::Iterator &);
		bool BindMemory2 (const TraceRange::Iterator &);
		bool GetSwapchainImages (const TraceRange::Iterator &);

		ND_ uint		GetImageCount ()		const	{ return _imageCounter; }

		ND_ RawImageID	Remap (ResourceID id, TraceRange::Bookmark)		const;
		ND_ RawImageID	Remap (VkImage id, TraceRange::Bookmark pos)	const	{ return Remap( ResourceID(id), pos ); }

		ND_ RawImageID			GetDummyColorImage2D ()					const	{ return _dummyColorImage2D; }
		ND_ ImageDesc const&	GetDummyColorImage2DDesc ()				const	{ return _dummyColorImage2DDesc; }


	private:
		bool _AddHostImage (VkImage img, MemoryObjAnalyzer::MemoryObjInfo_t const* mem, TraceRange::Bookmark pos);
		bool _UpdateImage (const HostAccessibleImage &, TraceRange::Bookmark, FrameID, INOUT TracePacker &);
		bool _CreateDummyImages (TracePacker &packer);
	};


}	// VTC
