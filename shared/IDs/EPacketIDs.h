// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


enum class EPacketID : uint32_t
{
	Unknown			= 0,

	_ApiOffset		= 20,
	_ApiMask		= 0xF << _ApiOffset,
	_VulkanApi		=   1 << _ApiOffset,
	//_VulkanEZApi	=   2 << _ApiOffset,
	_FrameGraphApi	=   3 << _ApiOffset,
	//_OpenGLApi	=   4 << _ApiOffset,

	_VersionOffset	= 24,
	_VersionMask	= 0x7F << _VersionOffset,
	_V100			=    1 << _VersionOffset,		// instruction set version

	_FlagsOffset	= 16,
	_FlagsMask		= 0xF << _FlagsOffset,
	_CustomBit		=   1 << _FlagsOffset,

	// special instructions
	End				= 0x0001 | _V100,
	SetData			= 0x0003 | _V100,
	CreateVkDevice	= 0x0004 | _V100,

	// Vulkan Packet IDs
#	include "IDs/VPacketIDs.h"
#	include "Generated/VulkanTracePacketIDs.h"

	// VulkanEZ Packet IDs

	// FrameGraph Packet IDs
#	include "IDs/FGPacketIDs.h"

	// ...
};

FG_BIT_OPERATORS( EPacketID );

