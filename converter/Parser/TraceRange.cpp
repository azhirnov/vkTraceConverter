// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Parser/TraceRange.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	TraceRange::TraceRange (const RStreamPtr &file, BytesU first, BytesU last) :
		_file{file}, _firstPacketOffset{first}, _lastPacketOffset{last}
	{
		ASSERT( _file );
		ASSERT( _firstPacketOffset <= _lastPacketOffset );
		ASSERT( _lastPacketOffset <= _file->Size() );
	}
	
/*
=================================================
	constructor
=================================================
*/
	TraceRange::TraceRange (const RStreamPtr &file) :
		_file{ file },
		_firstPacketOffset{ file->Position() },
		_lastPacketOffset{ _file->Size() }
	{}

/*
=================================================
	begin
=================================================
*/
	TraceRange::Iterator  TraceRange::begin () const
	{
		return Iterator{ _file, _firstPacketOffset };
	}
	
/*
=================================================
	empty
=================================================
*/
	bool  TraceRange::empty () const
	{
		return	not _file	or
				_firstPacketOffset == _lastPacketOffset;
	}
	
/*
=================================================
	SubRange
=================================================
*/
	TraceRange  TraceRange::SubRange (const Bookmark &beginIter, const Bookmark &endIter) const
	{
		ASSERT( beginIter._offset <= endIter._offset );
		ASSERT( Contains( beginIter ) );
		ASSERT( Contains( endIter ) or endIter._offset == _lastPacketOffset );

		return TraceRange{ _file, beginIter._offset, endIter._offset };
	}
	
/*
=================================================
	Get
=================================================
*/
	TraceRange::Iterator  TraceRange::Get (const Bookmark &bookmark) const
	{
		ASSERT( Contains( bookmark ) );
		return Iterator{ _file, bookmark._offset };
	}

/*
=================================================
	Contains
=================================================
*/
	bool  TraceRange::Contains (const Iterator &value) const
	{
		return	_file == value._file					and
				value._offset >= _firstPacketOffset		and
				value._offset < _lastPacketOffset;
	}
	
/*
=================================================
	Contains
=================================================
*/
	bool  TraceRange::Contains (const Bookmark &value) const
	{
		return	value._offset >= _firstPacketOffset		and
				value._offset < _lastPacketOffset;
	}
	
/*
=================================================
	GetPositionInFile
=================================================
*/
	uint64_t  TraceRange::GetPositionInFile (const Iterator &iter, const void* hdr, const void* member) const
	{
		return GetPositionInFile( iter.GetBookmark(), hdr, member );
	}
	
/*
=================================================
	GetPositionInFile
=================================================
*/
	uint64_t  TraceRange::GetPositionInFile (const Bookmark &bookmark, const void* hdr, const void* member) const
	{
		const size_t	off_1	= BitCast<size_t>( hdr );
		const size_t	off_2	= BitCast<size_t>( member );
		CHECK_ERR( off_1 < off_2 );

		const uint64_t	result = uint64_t(bookmark._offset) + uint64_t(off_2 - off_1);
		CHECK_ERR( result >= _firstPacketOffset and result < _lastPacketOffset );

		return result;
	}

/*
=================================================
	UnpackPointer
=================================================
*/
	template <typename T>
	inline void  UnpackPointer (INOUT T &ptr, vktrace_trace_packet_header* header)
	{
		STATIC_ASSERT( IsPointer<T> );

		if ( ptr == null )
			return;

		const_cast< std::remove_const_t<T> &>(ptr) = BitCast<T>( BitCast<size_t>(header->pBody) + BitCast<size_t>(ptr) );
	}

/*
=================================================
	UnpackPacket
	UnpackStruct
	Unpack_***
=================================================
*/
# ifdef _MSC_VER
#	pragma warning (push)
#	pragma warning (disable: 4100)
#	pragma warning (disable: 4505)
# endif

#	include "Generated/UnpackPacket.h"

# ifdef _MSC_VER
#	pragma warning (pop)
# endif
	
/*
=================================================
	constructor
=================================================
*/
	TraceRange::Iterator::Iterator (const RStreamPtr &file, BytesU offset) :
		_file{file}, _offset{offset}
	{
		_buffer.reserve( _MaxBufferSize );
		_ReadPacket();
	}
		
	TraceRange::Iterator::Iterator ()
	{
		_buffer.reserve( _MaxBufferSize );
		STATIC_ASSERT( alignof(vktrace_trace_packet_header) <= _buffer.align() );
	}
	
/*
=================================================
	constructor
=================================================
*/
	TraceRange::Iterator::Iterator (Iterator &&other) :
		_buffer{ std::move(other._buffer) },
		_file{ std::move(other._file) },
		_offset{ other._offset },
		_nextOffset{ other._nextOffset }
	{
		if ( other._lastPacket )
		{
			_lastPacket			= BitCast<vktrace_trace_packet_header *>(_buffer.data());
			other._lastPacket	= null;
		}

		other._file			= null;
		other._offset		= Default;
		other._nextOffset	= Default;
	}
	
/*
=================================================
	operator =
=================================================
*/
	TraceRange::Iterator&  TraceRange::Iterator::operator = (Iterator &&rhs)
	{
		_buffer		= std::move(rhs._buffer);
		_file		= std::move(rhs._file);
		_offset		= rhs._offset;
		_nextOffset	= rhs._nextOffset;
		
		if ( rhs._lastPacket )
		{
			_lastPacket		= BitCast<vktrace_trace_packet_header *>(_buffer.data());
			rhs._lastPacket	= null;
		}

		rhs._file		= null;
		rhs._offset		= Default;
		rhs._nextOffset	= Default;

		return *this;
	}

/*
=================================================
	_ReadPacket
=================================================
*/
	bool TraceRange::Iterator::_ReadPacket ()
	{
		_ReleasePacket();

		if ( not _file or _offset >= _file->Size() ) {
			//ASSERT(false);
			return false;
		}

		if ( not _file->SeekSet( _offset ) ) {
			ASSERT(false);
			return false;
		}

		uint64_t		packet_size			= 0;
		const BytesU	packet_size_sizeof	= BytesU::SizeOf(packet_size);

		CHECK_ERR( _file->Read( OUT packet_size ));
		_buffer.resize( packet_size );

		_lastPacket = BitCast<vktrace_trace_packet_header *>(_buffer.data());
		CHECK_ERR( _lastPacket );
		CHECK_ERR( _file->Read( _lastPacket + packet_size_sizeof, (packet_size - packet_size_sizeof) ));

        _lastPacket->size = packet_size;
        _lastPacket->pBody = BitCast<uintptr_t>(_lastPacket) + sizeof(vktrace_trace_packet_header);	

		UnpackPacket( _lastPacket );

		_nextOffset = _file->Position();
		return true;
	}
	
/*
=================================================
	_ReleasePacket
=================================================
*/
	void TraceRange::Iterator::_ReleasePacket ()
	{
		if ( _buffer.capacity() > _MaxBufferSize*2 )
		{
			_buffer.resize( _MaxBufferSize );
			_buffer.shrink_to_fit();
		}

		_lastPacket = null;
	}


}	// VTC
