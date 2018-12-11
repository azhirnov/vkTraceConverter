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
			VkImage				handle		= VK_NULL_HANDLE;
			uint				id			= ~0u;
			FG::ImageDesc		desc;
			FG::MemoryDesc		mem;
			bool				memBinded	= false;
		};

		using PendingImages_t	= Array< PendingImage >;
		using IndexArray_t		= Array< uint >;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		PendingImages_t			_pendingImages;
		IndexArray_t			_readyToDelete;
		IndexArray_t			_freeIndices;

		Array<RawImageID>		_remapping;

		uint					_imageCounter	= 0;


	// methods
	public:
		explicit ImageConverter (FrameGraphConverter &fgConv) : _fgConv{fgConv} {}
		
		bool OnBeginFrame (TracePacker &packer);
		bool OnEndFrame (TracePacker &packer);

		bool CreateImage (const TraceRange::Iterator &);
		bool DestroyImage (const TraceRange::Iterator &);
		bool BindMemory (const TraceRange::Iterator &);
		bool BindMemory2 (const TraceRange::Iterator &);
		bool GetSwapchainImages (const TraceRange::Iterator &);

		ND_ uint		GetImageCount ()		const	{ return _imageCounter; }

		ND_ RawImageID	Remap (ResourceID id, TraceRange::Bookmark)		const;
		ND_ RawImageID	Remap (VkImage id, TraceRange::Bookmark pos)	const	{ return Remap( ResourceID(id), pos ); }
	};


}	// VTC
