// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Common.h"

namespace VTC
{
	struct BlockHeader
	{
		uint64_t	id			= 0;
		uint64_t	offset		= 0;
		uint64_t	dataSize	= 0;

		BlockHeader () {}
	};

	struct BlockInfo
	{
		uint64_t	dataSize	= 0;
	};

	static constexpr uint	ResourceFileMagicNumber	=	(uint('V') <<  0) |
														(uint('T') <<  8) |
														(uint('C') << 16) |
														(0x01 << 24);

}	// VTC
