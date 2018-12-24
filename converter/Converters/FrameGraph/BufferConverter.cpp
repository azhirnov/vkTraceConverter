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
		for (auto iter = _pendingBuffers.begin(); iter != _pendingBuffers.end();)
		{
			if ( not iter->memBinded ) {
				++iter;
				continue;
			}

			packer.Begin( EPacketID::FgCreateBuffer );
			packer << uint(0);	// TODO: thread id
			packer << iter->id;
			FGPack_BufferDesc( iter->desc, packer );
			FGPack_MemoryDesc( iter->mem, packer );
			packer.End( EPacketID::FgCreateBuffer );

			iter = _pendingBuffers.erase( iter );
		}

		for (auto& buf : _hostBuffers)
		{
			CHECK_ERR( _UpdateBuffer( buf, submitPos, frameId, packer ));
			buf.lastPos = submitPos;
		}
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
		buf_desc.usage	= FGEnumCast( VkBufferUsageFlagBits(buffer->createInfo.usage) );

		ASSERT( buf_desc.usage != EBufferUsage::Unknown );

		_pendingBuffers.push_back({ resource->uniqueIndex, index, buf_desc, FG::MemoryDesc{}, false });
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
		
		auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_BUFFER, ResourceID(packet.buffer), pos.GetBookmark() );
		CHECK_ERR( resource );

		auto	result = _remapping[resource->localIndex];
		if ( not result )
			return true;	// already deleted or was not created

		_readyToDelete.push_back( result.Index() );

		for (auto iter = _hostBuffers.begin(); iter != _hostBuffers.end();)
		{
			if ( iter->buffer->id == ResourceID(packet.buffer) )
				iter = _hostBuffers.erase( iter );
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
	bool FrameGraphConverter::BufferConverter::BindMemory (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkBindBufferMemory>();

		for (auto& item : _pendingBuffers)
		{
			auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_BUFFER, ResourceID(packet.buffer), pos.GetBookmark() );

			if ( not resource or item.uid != resource->uniqueIndex or item.memBinded )
				continue;

			auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), pos.GetBookmark() );
			CHECK_ERR( mem );
			
			if ( mem->usage == EMemoryUsage::HostRead )
				continue;
			
			item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated :
							  EnumEq( mem->usage, EMemoryUsage::HostWrite ) ? EMemoryType::HostWrite : EMemoryType::Default;
			item.mem.poolId = MemPoolID{ ToString( mem->id )};
			item.memBinded	= true;
			
			_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
			_remapping[resource->localIndex] = RawBufferID{ item.id, 0 };

			_AddHostBuffer( packet.buffer, mem, pos.GetBookmark() );
			break;
		}
		return true;
	}
	
/*
=================================================
	BindMemory2
=================================================
*/
	bool FrameGraphConverter::BufferConverter::BindMemory2 (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkBindBufferMemory2>();

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			for (auto& item : _pendingBuffers)
			{
				auto*	resource = _fgConv._resourcesBookmarks->GetResource( VK_OBJECT_TYPE_BUFFER, ResourceID(packet.pBindInfos[i].buffer), pos.GetBookmark() );

				if ( not resource or item.uid != resource->uniqueIndex or item.memBinded )
					continue;

				auto*	mem		= _fgConv._memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.pBindInfos[i].memory), pos.GetBookmark() );
				CHECK_ERR( mem );
				
				if ( mem->usage == EMemoryUsage::HostRead )
					continue;

				item.mem.type	= EnumEq( mem->usage, MemoryObjAnalyzer::EMemoryUsage::Dedicated ) ? EMemoryType::Dedicated :
								  EnumEq( mem->usage, EMemoryUsage::HostWrite ) ? EMemoryType::HostWrite : EMemoryType::Default;
				item.mem.poolId = MemPoolID{ ToString( mem->id )};
				item.memBinded	= true;
				
				_remapping.resize(Max( resource->localIndex+1, _remapping.size() ));
				_remapping[resource->localIndex] = RawBufferID{ item.id, 0 };

				_AddHostBuffer( packet.pBindInfos[i].buffer, mem, pos.GetBookmark() );
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
	_AddHostBuffer
=================================================
*/
	bool FrameGraphConverter::BufferConverter::_AddHostBuffer (VkBuffer bufferId, MemoryObjAnalyzer::MemoryObjInfo_t const* mem, TraceRange::Bookmark pos)
	{

		auto*	buf = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(bufferId), pos );
		CHECK_ERR( buf and mem );
		
		if ( not EnumAny( mem->usage, EMemoryUsage::HostRead | EMemoryUsage::HostWrite ))
			return false;

		// skip staging buffers
		if ( not EnumAny( buf->createInfo.usage, ~(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT) ))
			return false;

		_hostBuffers.push_back({ buf, mem, mem->FirstBookmark().pos });
		return true;
	}

/*
=================================================
	_UpdateBuffer
----
	see unpacker in 'FGPlayer_v100::_UpdateHostBuffer'
=================================================
*/
	bool FrameGraphConverter::BufferConverter::_UpdateBuffer (const HostAccessibleBuffer &bufferInfo, TraceRange::Bookmark submitPos,
															  FrameID frameId, INOUT TracePacker &packer)
	{
		auto*	buf = bufferInfo.buffer;
		auto*	mem = bufferInfo.memory;

		auto	mem_last_bm = mem->bookmarks.end();

		for (auto iter = mem->bookmarks.begin(); iter != mem->bookmarks.end(); ++iter)
		{
			if ( iter->pos < bufferInfo.lastPos )
				continue;

			if ( iter->pos >= submitPos )
				break;

			mem_last_bm = iter;
		}
		
		Array<Pair<uint64_t, uint64_t>>		regions;
		regions.push_back({ 0, buf->createInfo.size });

		// find memory transfer to buffer
		for (auto bm_iter = std::make_reverse_iterator(mem_last_bm), bm_end = mem->bookmarks.rend();
			 bm_iter != bm_end and regions.size();
			 ++bm_iter)
		{
			auto&	bm = *bm_iter;

			if ( bm.packetId != VKTRACE_TPI_VK_vkFlushMappedMemoryRanges )
				continue;
			
			auto*	info = _fgConv._memTransferAnalyzer->GetTransfer( mem->id, bm.pos );
			CHECK_ERR( info );
			
			for (auto& block : info->blocks)
			{
				for (auto iter = regions.begin(); iter != regions.end();)
				{
					auto&	reg = *iter;
					
					uint64_t		data_size	= Min( reg.second - reg.first, buf->createInfo.size - reg.first );
					const uint64_t	buf_begin	= buf->memOffset + reg.first;
					const uint64_t	buf_end		= buf->memOffset + reg.second;
					uint64_t		data_begin, data_end;
				
					if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, buf_begin, buf_end,
										  OUT data_begin, OUT data_end ) )
					{
									data_size	 = data_end - data_begin;
						uint64_t	block_offset = data_begin - block.memOffset;
						uint64_t	buf_offset	 = reg.first + (data_begin - buf_begin);

						CHECK( block_offset < block.dataSize	and
							   block_offset + data_size <= block.dataSize );

						DataID	data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
						CHECK_ERR( data_id != UMax );

						packer.Begin( EPacketID::FgUpdateHostBuffer );
						packer << uint(0);	// TODO: thread id
						packer << _fgConv._bufferConv->Remap( buf->id, mem_last_bm->pos ).Index();
						packer << uint(1);	// count
						packer << buf_offset;
						packer << data_size;
						packer << data_id;
						packer.End( EPacketID::FgUpdateHostBuffer );
					
						iter = regions.erase( iter );
					}
					else
						++iter;
				}
			}
		}

		return true;
	}
	

}	// VTC
