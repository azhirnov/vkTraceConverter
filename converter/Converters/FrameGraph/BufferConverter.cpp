// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/BufferConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "FGPack/FgStructPacker.h"

namespace VTC
{

/*
=================================================
	OnBeginFrame
----
	see unpacker in 'FGPlayer_v100::_CreateBuffer'
=================================================
*/
	bool FrameGraphConverter::BufferConverter::OnBeginFrame (TraceRange::Bookmark submitPos, FrameID frameId, INOUT TracePacker &packer)
	{
		for (auto& item : _pendingBuffers)
		{
			CHECK( item.memBinded );

			packer.Begin( EPacketID::FgCreateBuffer );
			packer << uint(0);	// TODO: thread id
			packer << item.id;
			FGPack_BufferDesc( item.desc, packer );
			FGPack_MemoryDesc( item.mem, packer );
			packer.End( EPacketID::FgCreateBuffer );
			
			CHECK_ERR( _UpdateBuffer( ResourceID(item.handle), item.startPos, submitPos, frameId, INOUT packer ));
		}

		_pendingBuffers.clear();
		return true;
	}
	
/*
=================================================
	OnEndFrame
----
	see unpacker in 'FGPlayer_v100::_DestroyBuffer'
=================================================
*/
	bool FrameGraphConverter::BufferConverter::OnEndFrame (TracePacker &packer)
	{
		for (auto item : _readyToDelete)
		{
			packer.Begin( EPacketID::FgDestroyBuffer );
			packer << uint(0);	// TODO: thread id
			packer << item;
			packer.End( EPacketID::FgDestroyBuffer );

			_freeIndices.push_back( item );
		}

		_readyToDelete.clear();
		return true;
	}
	
/*
=================================================
	CreateBuffer
=================================================
*/
	bool FrameGraphConverter::BufferConverter::CreateBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCreateBuffer>();

		auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_BUFFER, ResourceID(*packet.pBuffer), pos.GetBookmark() );
		auto*	buffer	 = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(*packet.pBuffer), pos.GetBookmark() );
		CHECK_ERR( buffer and resource );

		uint			index	= 0;
		FG::BufferDesc	buf_desc;

		if ( not _freeIndices.empty() ) {
			index = _freeIndices.back();
			_freeIndices.pop_back();
		}else
			index = _bufferCounter++;

		buf_desc.size	= BytesU{ buffer->createInfo.size };
		buf_desc.usage	= FGEnumCast( VkBufferUsageFlagBits(buffer->createInfo.usage) ) | EBufferUsage::TransferDst;

		_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
		_remapping[resource->localIndex] = RawBufferID{ index, 0 };

		_pendingBuffers.push_back({ *packet.pBuffer, index, buf_desc, FG::MemoryDesc{}, pos.GetBookmark(), false });
		return true;
	}
	
/*
=================================================
	DestroyBuffer
=================================================
*/
	bool FrameGraphConverter::BufferConverter::DestroyBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkDestroyBuffer>();

		_readyToDelete.push_back( Remap( packet.buffer, pos.GetBookmark() ).Index() );
		return true;
	}
	
/*
=================================================
	BindMemory
=================================================
*/
	bool FrameGraphConverter::BufferConverter::BindMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast<packet_vkBindBufferMemory>();

		for (auto& item : _pendingBuffers)
		{
			if ( item.handle != packet.buffer )
				continue;

			auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), pos.GetBookmark() );
			CHECK_ERR( mem );
			CHECK_ERR( not item.memBinded );

			item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated : EMemoryType::Default;
			item.mem.poolId = MemPoolID{ ToString( mem->id )};
			item.memBinded	= true;
			item.startPos	= pos.GetBookmark();
			break;
		}
		return true;
	}
	
/*
=================================================
	BindMemory2
=================================================
*/
	bool FrameGraphConverter::BufferConverter::BindMemory2 (const TraceRange::Iterator &pos, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast<packet_vkBindBufferMemory2>();

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			for (auto& item : _pendingBuffers)
			{
				if ( item.handle != packet.pBindInfos[i].buffer )
					continue;

				auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.pBindInfos[i].memory), pos.GetBookmark() );
				CHECK_ERR( mem );
				CHECK_ERR( not item.memBinded );

				item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated : EMemoryType::Default;
				item.mem.poolId = MemPoolID{ ToString( mem->id )};
				item.memBinded	= true;
				item.startPos	= pos.GetBookmark();
				break;
			}
		}
		return true;
	}

/*
=================================================
	Remap
=================================================
*/
	RawBufferID  FrameGraphConverter::BufferConverter::Remap (ResourceID id, TraceRange::Bookmark pos) const
	{
		auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_BUFFER, id, pos );
		CHECK_ERR( resource );

		auto	result = _remapping[resource->localIndex];
		CHECK_ERR( result );

		return result;
	}
	
/*
=================================================
	_UpdateBuffer
=================================================
*/
	bool FrameGraphConverter::BufferConverter::_UpdateBuffer (ResourceID bufferId, TraceRange::Bookmark pos, TraceRange::Bookmark submitPos,
															  FrameID frameId, INOUT TracePacker &packer)
	{
		using EMemoryUsage = MemoryObjAnalyzer::EMemoryUsage;

		auto*	buf = _fgConv._bufferAnalyzer->GetBuffer( bufferId, pos );
		CHECK_ERR( buf );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( buf->memId, pos );
		CHECK_ERR( mem );
		
		if ( not EnumAny( mem->usage, EMemoryUsage::HostRead | EMemoryUsage::HostWrite ))
			return true;

		if ( not EnumAny( buf->createInfo.usage, ~(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT) ))
			return true;

		size_t	mem_last_bm = 0;

		for (size_t i = 0; i < mem->bookmarks.size(); ++i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.pos >= submitPos )
				break;

			mem_last_bm = i;
		}
		
		Array<Pair<uint64_t, uint64_t>>		regions;
		regions.push_back({ 0, buf->createInfo.size });

		// find memory transfer to buffer
		for (size_t i = mem_last_bm; i < mem->bookmarks.size() and regions.size(); --i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.packetId != VKTRACE_TPI_VK_vkFlushMappedMemoryRanges )
				continue;
			
			auto*	info = _fgConv._memTransferAnalyzer->GetTransfer( mem->id, bm.pos );
			CHECK_ERR( info );
			
			for (auto& block : info->blocks)
			{
				for (auto iter = regions.begin(); iter != regions.end();)
				{
					auto&	reg = *iter;
					
					const uint64_t	data_size	= Min( reg.second - reg.first, buf->createInfo.size - reg.first );
					const uint64_t	buf_begin	= buf->memOffset + reg.first;
					const uint64_t	buf_end		= buf->memOffset + reg.second;
					uint64_t		data_begin, data_end;
				
					if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, buf_begin, buf_end,
										  OUT data_begin, OUT data_end ) )
					{
						ASSERT( data_begin == buf_begin and data_end == buf_end );
						
						uint64_t	block_offset = buf_begin - block.memOffset;
						ASSERT( block_offset < block.dataSize	and
								block_offset + data_size <= block.dataSize );

						DataID	data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
						CHECK_ERR( data_id != ~DataID(0) );

						packer.Begin( EPacketID::FgUpdateBuffer );
						packer << uint(0);	// TODO: thread id
						packer << _fgConv._bufferConv->Remap( bufferId, pos ).Index();
						packer << reg.first;
						packer << data_size;
						packer << data_id;
						packer.End( EPacketID::FgUpdateBuffer );
					
						iter = regions.erase( iter );
					}
					else
						++iter;
				}
			}
		}

		CHECK_ERR( regions.empty() );
		return true;
	}


}	// VTC
