// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Vulkan/VulkanTraceConverter.h"

namespace VTC
{

/*
=================================================
	_OnCreateCommandPool
=================================================
*/
	bool VulkanTraceConverter::_OnCreateCommandPool (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		return false;
	}
	
/*
=================================================
	_OnWaitEvents3
=================================================
*/
	bool VulkanTraceConverter::_OnWaitEvents3 (const TraceRange::Iterator &pos) const
	{
		return false;
	}
	
/*
=================================================
	_OnPipelineBarrier3
=================================================
*/
	bool VulkanTraceConverter::_OnPipelineBarrier3 (const TraceRange::Iterator &pos) const
	{
		return false;
	}

}	// VTC
