// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


enum class EFrameGraphPacketID : uint32_t
{
	_FrameGraphApi	= uint(EPacketID::_FrameGraphApi),
	_V100			= uint(EPacketID::_V100),
	_CustomBit		= uint(EPacketID::_CustomBit),

	End				= uint(EPacketID::End),
	SetData			= uint(EPacketID::SetData),
	CreateVkDevice	= uint(EPacketID::CreateVkDevice),
	
#	include "IDs/FGPacketIDs.h"
};
