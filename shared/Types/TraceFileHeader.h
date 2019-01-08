// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


//
// Trace File Header
//

struct TraceFileHeader
{
	enum class EArchiveType : uint32_t {
		None,		// without compression
		Brotli,
	};

	uint32_t		magic;
	uint32_t		instructionSet;	// EPacketID::_ApiMask | EPacketID::_VersionMask
	uint32_t		pointerSize;	// 4 or 8 bytes
	EArchiveType	archiveType;
	uint64_t		instructionBlockOffset;
	uint64_t		dataBlockOffset;

	// New Vulkan Trace File
	static constexpr uint32_t	MagicNumber	=	(uint32_t('V') << 0) |
												(uint32_t('T') << 8) |
												(uint32_t('F') << 16) |
												(2 << 24);	// version
};
