// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Utils/TracePacker.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	TracePacker::TracePacker (const AllResourcesBookmarks *rbm) :
		_resBookmarks{ rbm },
		_currPacket{ EPacketID::Unknown }
	{
		_tempData.reserve( 4 << 20 );
		_packedData.reserve( 128 << 20 );
	}
	
/*
=================================================
	Begin
=================================================
*/
	void TracePacker::Begin (EPacketID packetId)
	{
		ASSERT( _currPacket == EPacketID::Unknown );

		_currPacket = packetId;
		_pointerStack.push_back({ null, {} });
	}
	
/*
=================================================
	End
=================================================
*/
	void TracePacker::End (EPacketID packetId)
	{
		ASSERT( _currPacket == packetId );
		ASSERT( _tempData.size() > 0 );

		Flush();

		_currPacket = EPacketID::Unknown;

		ASSERT( _pointerStack.size() == 1 );
		_pointerStack.pop_back();
	}
	
/*
=================================================
	SetArray
=================================================
*/
	void TracePacker::SetArray (const void *data, size_t size)
	{
		const uint8_t* ptr = Cast<uint8_t>( data );

		_pointerStack.push_back({ data, Buffer_t{ptr, ptr + size} });

		Pop( data );
	}
	
/*
=================================================
	_Store
=================================================
*/
	void TracePacker::_Store (const void *data, size_t size)
	{
		const uint8_t* ptr = Cast<uint8_t>( data );

		ASSERT( not _pointerStack.empty() );
		_pointerStack.back().second.insert( _pointerStack.back().second.end(), ptr, ptr + size );
	}
	
/*
=================================================
	_PopAndStorePtr
=================================================
*/
	void TracePacker::_PopAndStorePtr ()
	{
		auto&			buf = _pointerStack.back().second;
		const size_t	off = _tempData.size();

		_tempData.insert( _tempData.end(), buf.begin(), buf.end() );
		_pointerStack.pop_back();

		_Store( &off, sizeof(off) );
	}

/*
=================================================
	Clear
=================================================
*/
	void TracePacker::Clear ()
	{
		_tempData.clear();
		_packedData.clear();

		_structStack.clear();
		_pointerStack.clear();
	}
	
/*
=================================================
	Flush
=================================================
*/
	void TracePacker::Flush ()
	{
		if ( _tempData.empty() )
			return;

		struct PacketHeader {
			EPacketID	id;
			uint		size;
		};

		const PacketHeader	hdr{ _currPacket, uint(_tempData.size()) };
		const uint8_t *		ptr = BitCast<const uint8_t *>( &hdr );

		ASSERT( _tempData.size() < std::numeric_limits<uint>::max() );

		_packedData.insert( _packedData.end(), ptr, ptr + sizeof(hdr) );
		_packedData.insert( _packedData.end(), _tempData.begin(), _tempData.end() );
		_tempData.clear();
	}


}	// VTC
