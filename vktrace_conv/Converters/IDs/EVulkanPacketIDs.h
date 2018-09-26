// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Common.h"

namespace VTC
{

	enum class EVulkanPacketID
	{
#		include "Converters/IDs/VPacketIDs.h"
#		include "Generated/VulkanTracePacketIDs.h"
	};

}	// VTC
