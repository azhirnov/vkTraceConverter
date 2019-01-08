// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


enum class EVulkanPacketID : uint32_t
{
	_VulkanApi		= uint(EPacketID::_VulkanApi),
	_V100			= uint(EPacketID::_V100),
	_CustomBit		= uint(EPacketID::_CustomBit),

	End				= uint(EPacketID::End),
	SetData			= uint(EPacketID::SetData),
	CreateVkDevice	= uint(EPacketID::CreateVkDevice),

#	include "IDs/VPacketIDs.h"
#	include "Generated/VulkanTracePacketIDs.h"
};
