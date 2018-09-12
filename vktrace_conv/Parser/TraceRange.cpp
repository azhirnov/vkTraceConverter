// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Parser/TraceRange.h"

namespace VTC
{

/*
=================================================
	UnpackPointer
=================================================
*/
template <typename T>
inline void UnpackPointer (INOUT T &ptr, vktrace_trace_packet_header* header)
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
	_ReadPacket
=================================================
*/
	void TraceRange::Iterator::_ReadPacket ()
	{
		_ReleasePacket();

		if ( not _file or _offset >= _file->mFileLen ) {
			//ASSERT(false);
			return;
		}

		if ( vktrace_FileLike_SetCurrentPosition( _file, _offset ) == FALSE ) {
			ASSERT(false);
			return;
		}

		_lastPacket = vktrace_read_trace_packet( _file );
		ASSERT( _lastPacket );

		UnpackPacket( _lastPacket );

		_nextOffset = vktrace_FileLike_GetCurrentPosition( _file );
	}
	
/*
=================================================
	_ReleasePacket
=================================================
*/
	void TraceRange::Iterator::_ReleasePacket ()
	{
		vktrace_delete_trace_packet_no_lock( &_lastPacket );
		_lastPacket = null;
	}


}	// VTC
