// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	
*/

#pragma once

#include "Common.h"

namespace VTC
{

	enum class EPacketID : uint
	{
		Unknown = 0,

		// Vulkan Packet IDs
#		include "Converters/IDs/VPacketIDs.h"
#		include "Generated/VulkanTracePacketIDs.h"

		// VulkanEZ Packet IDs

		// FrameGraph Packet IDs

		// ...
	};

}	// VTC
