// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


//
// Trace Packet Header
//

struct TracePacketHeader
{
	uint32_t	size;		// packet sizeof
	uint32_t	id;			// EPacketID
	uint32_t	offset;		// initial offset
};
