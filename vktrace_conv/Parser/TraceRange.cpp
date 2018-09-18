// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Parser/TraceRange.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	TraceRange::TraceRange (const RFilePtr &file, BytesU first, BytesU last) :
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
	TraceRange::TraceRange (const RFilePtr &file) :
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
	end
=================================================
*
	TraceRange::Iterator  TraceRange::end () const
	{
		return Iterator{ _file, _lastPacketOffset };
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
*
	TraceRange  TraceRange::SubRange (const Iterator &beginIter, const Iterator &endIter) const
	{
		ASSERT( beginIter._file == endIter._file );
		ASSERT( beginIter._offset <= endIter._offset );
		ASSERT( Contains( beginIter ) );
		ASSERT( Contains( endIter ) );

		return TraceRange{ beginIter._file, beginIter._offset, endIter._offset };
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
		ASSERT( Contains( endIter ) );

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
		if ( ptr == null )
			return;

		const_cast< std::remove_const_t<T> &>(ptr) = BitCast<T>( BitCast<size_t>(header->pBody) + BitCast<size_t>(ptr) );
	}

/*
=================================================
	PtrCast
=================================================
*/
	template <typename To, typename From>
	ND_ inline constexpr To*  PtrCast (const From *from) noexcept
	{
		STATIC_ASSERT( sizeof(To*) == sizeof(From*), "must be same size!" );

		return reinterpret_cast< To* >( const_cast< From* >(from) );
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
	TraceRange::Iterator::Iterator (const RFilePtr &file, BytesU offset) :
		_file{file}, _offset{offset}
	{
		_buffer.reserve( _MaxBufferSize );
		_ReadPacket();
	}
		
	TraceRange::Iterator::Iterator ()
	{
		_buffer.reserve( _MaxBufferSize );
		STATIC_ASSERT( alignof(vktrace_trace_packet_header) <= sizeof(_buffer[0]) );
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
		_buffer.resize( (packet_size + sizeof(_buffer[0])) / sizeof(_buffer[0]) );

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
