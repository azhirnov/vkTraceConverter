// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "TraceReader.h"

namespace VTPlayer
{

/*
=================================================
	constructor
=================================================
*/
	TraceReader::TraceReader (const SharedPtr<RStream> &file) :
		_packet{},		_file{ file }
	{
		if ( _file and _file->IsOpen() )
		{
			_offset = _file->Position();
		}

		_buffer.reserve( _MaxBufferSize );
	}
	
/*
=================================================
	destructor
=================================================
*/
	TraceReader::~TraceReader ()
	{
	}
	
/*
=================================================
	ReadNext
=================================================
*/
	bool TraceReader::ReadNext ()
	{
		if ( not _file or _offset >= _file->Size() ) {
			//ASSERT(false);
			return false;
		}

		/*if ( not _file->SeekSet( _offset ) ) {
			ASSERT(false);
			return false;
		}*/

		CHECK_ERR( _file->Read( OUT _packet ));

		_buffer.resize( _packet.size );

		CHECK_ERR( _file->Read( _buffer.data(), BytesU(_packet.size) ));

		_offset += _packet.size + sizeof(_packet);
		return true;
	}

}	// VTPlayer
