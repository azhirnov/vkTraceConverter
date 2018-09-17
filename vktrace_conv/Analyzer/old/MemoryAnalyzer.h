// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Memory Analyzer
	//

	class MemoryAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct MemBinding
		{
			ResourceID				id		= 0;
			VkDeviceSize			offset	= 0;
			VkDeviceSize			size	= 0;
			TraceRange::Bookmark	pos;
		};


		struct MemInfo
		{
			ResourceID				id					= 0;
			uint					memoryTypeIndex		= ~0u;
			VkMemoryPropertyFlags	propertyFlags		= 0;
			VkDeviceSize			size				= 0;
			ResourceID				dedicatedResource	= 0;	// image or buffer
			bool					isExported			= false;
			bool					isImported			= false;
			Array<MemBinding>		imageBindings;
			Array<MemBinding>		bufferBindings;
		};


		struct BlockInfo
		{
			uint64_t	offset	= 0;	// position in file
			uint64_t	size	= 0;	// data size
		};

		struct MemTransferInfo
		{
			Array<BlockInfo>	blocks;
		};


		struct VkImageSubresourceHash {
			ND_ size_t  operator () (const VkImageSubresource &value) const {
				return size_t(HashOf( value.aspectMask ) + HashOf( value.mipLevel ) + HashOf( value.arrayLayer ));
			}
		};

		using SubresLayouts_t	= HashMap< VkImageSubresource, VkSubresourceLayout, VkImageSubresourceHash >;

		struct ImageInfo
		{
			TraceRange::Bookmark	createdIn;
			VkFormat				initialFormat;
			HashSet<VkFormat>		viewFormats;
			SubresLayouts_t			subresLayouts;
			bool					hasCompressedFormats	= false;
			bool					hasOptimalTiling		= false;	// optimal tiling requires device local memory
		};


		struct BufferInfo
		{
			bool					hasCompressedFormats	= false;
		};


		using MemoryObjectsMap_t	= ResourceTracker< MemInfo >;
		using MemoryInfo_t			= MemoryObjectsMap_t::Item_t;

		using MemTransferMap_t		= HashMap< Pair<ResourceID, TraceRange::Bookmark>, MemTransferInfo >;

		using ImagesMap_t			= ResourceTracker< ImageInfo >;
		using ImageInfo_t			= ImagesMap_t::Item_t;

		using BuffersMap_t			= ResourceTracker< BufferInfo >;
		using BufferInfo_t			= BuffersMap_t::Item_t;


	// variables
	private:
		MemoryObjectsMap_t		_memObjects;
		//MemTransferMap_t		_memTransfer;

		ImagesMap_t				_images;
		BuffersMap_t			_buffers;

		TraceRange const*		_fullTrace;
		uint16_t				_traceFileVersion;


	// methods
	public:
		MemoryAnalyzer ();
		


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;

		void Process (const TraceRange::Iterator &) override;
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;

		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessMemoryUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessImageUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessBufferUsage (const TraceRange::Iterator &, ResourceID);

		bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &);
		bool _OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &);
		
		bool _OnQueueBindSparse (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnAllocateMemory (const TraceRange::Iterator &, ResourceID);
		bool _OnMapMemory (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindBufferMemory (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindImageMemory (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindImageMemory2 (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _BindBufferMemory (MemoryInfo_t &mem, VkBuffer buffer, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos);
		bool _BindImageMemory (MemoryInfo_t &mem, VkImage image, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos);

		bool _OnCreateImage ();
		bool _OnGetImageSubresourceLayout ();
		bool _OnGetImageMemoryRequirements ();
		bool _OnGetImageMemoryRequirements2 ();

		bool _OnCreateBuffer ();
		bool _OnGetBufferMemoryRequirements ();
		bool _OnGetBufferMemoryRequirements2 ();
	};


}	// VTC
