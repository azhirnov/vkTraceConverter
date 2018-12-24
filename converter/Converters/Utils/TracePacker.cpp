// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Utils/TracePacker.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	TracePacker::TracePacker ()
	{
		_tempData.reserve( 4 << 20 );
	}

	TracePacker::TracePacker (Ptr<const AllResourcesBookmarks> rbm, bool uniqueIndices) :
		_resBookmarks{ rbm },
		_useUniqueIndices{ uniqueIndices }
	{
		_tempData.reserve( 4 << 20 );
	}
	
/*
=================================================
	Begin
=================================================
*/
	void TracePacker::Begin (EPacketID packetId)
	{
		ASSERT( _currPacket == EPacketID::Unknown );
		ASSERT( _tempData.empty() );

		_currPacket = packetId;
		_pointerStack.push_back({ null, {}, 0 });
	}
	
/*
=================================================
	End
=================================================
*/
	void TracePacker::End (EPacketID packetId)
	{
		ASSERT( _currPacket == packetId );

		Flush();

		_currPacket = EPacketID::Unknown;
	}
	
/*
=================================================
	AddArray
=================================================
*/
	void TracePacker::AddArray (const void *data, size_t size)
	{
		if ( size )
		{
			ASSERT( data and size );
			_Store( data, size, alignof(void*) );
		}
	}
	
/*
=================================================
	AddString
=================================================
*/
	void TracePacker::AddString (const char *str)
	{
		ASSERT( str );
		_Store( str, strlen(str) + 1, alignof(char*) );
	}

/*
=================================================
	_Store
=================================================
*/
	void TracePacker::_Store (const void *data, size_t size, size_t align)
	{
		ASSERT( not _pointerStack.empty() );

		if ( _pointerStack.back().align == 0 )
			_pointerStack.back().align = align;

		auto&			buf			= _pointerStack.back().buf;
		const size_t	src_size	= buf.size();
		const size_t	offset		= AlignToLarger( src_size, align );

		buf.resize( offset + size );
		DEBUG_ONLY( memset( buf.data() + BytesU(src_size), 0xAA, offset - src_size ));
		memcpy( buf.data() + BytesU(offset), data, size );
	}
	
/*
=================================================
	_PopAndPackPtr
=================================================
*/
	void TracePacker::_PopAndPackPtr (OUT size_t &result)
	{
		const auto&		buf			= _pointerStack.back().buf;
		const size_t	align		= _pointerStack.back().align;
		const size_t	src_size	= _tempData.size();
		const size_t	offset		= AlignToLarger( src_size, align );
		const size_t	ptr			= result == 0 ? UMax : offset;
		
		ASSERT( result or buf.empty() );
		
		_tempData.resize( offset + buf.size() );
		DEBUG_ONLY( memset( _tempData.data() + BytesU(src_size), 0xAA, offset - src_size ));
		memcpy( _tempData.data() + BytesU(offset), buf.data(), buf.size() );

		_pointerStack.pop_back();

		result = ptr;
	}

/*
=================================================
	Clear
=================================================
*/
	void TracePacker::Clear ()
	{
		_tempData.clear();
		_file.Clear();
		_pointerStack.clear();
	}
	
/*
=================================================
	Flush
=================================================
*/
	void TracePacker::Flush ()
	{
		ASSERT( _currPacket != EPacketID::Unknown );
		ASSERT( _pointerStack.size() == 1 );

		TracePacketHeader  hdr;
		hdr.id		= uint(_currPacket);
		hdr.offset	= uint(_tempData.size());
		ASSERT( _tempData.size() < std::numeric_limits<uint>::max() );
		
		// copy last part
		{
			const auto&		buf			= _pointerStack.back().buf;
			const size_t	align		= Max( 4u, _pointerStack.back().align );
			const size_t	src_size	= _tempData.size();
			const size_t	offset		= AlignToLarger( _tempData.size(), align );

			_tempData.resize( offset + buf.size() );
			DEBUG_ONLY( memset( _tempData.data() + BytesU(src_size), 0xAA, offset - src_size ));

			memcpy( _tempData.data() + BytesU(offset), buf.data(), buf.size() );
			_pointerStack.pop_back();
		}

		hdr.size = uint(_tempData.size());

		// store header
		CHECK( _file.Write( hdr ));

		// store data
		if ( _tempData.size() > 0 )
			_file.Write( _tempData.data(), BytesU(_tempData.size()) );

		_tempData.clear();
	}
	
/*
=================================================
	Append
=================================================
*/
	void TracePacker::Append (const TracePacker &other)
	{
		if ( other.GetData().empty() )
			return;

		CHECK( _file.Write( other.GetData() ));
	}


}	// VTC
