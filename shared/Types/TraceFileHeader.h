// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


//
// Trace File Header
//

struct TraceFileHeader
{
	uint32_t	magic;
	uint32_t	instructionSet;	// EPacketID::_ApiMask | EPacketID::_VersionMask
	uint32_t	pointerSize;	// 4 or 8 bytes

	// New Vulkan Trace File
	static constexpr uint32_t	MagicNumber	=	(uint32_t('N') <<  0) |
												(uint32_t('V') <<  8) |
												(uint32_t('T') << 16) |
												(uint32_t('F') << 24);
};
