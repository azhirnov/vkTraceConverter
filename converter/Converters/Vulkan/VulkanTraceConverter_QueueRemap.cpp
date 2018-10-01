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
	_OnCreateBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnCreateBuffer (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		return false;
	}
	
/*
=================================================
	_OnCreateImage
=================================================
*/
	bool VulkanTraceConverter::_OnCreateImage (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		return false;
	}
	
/*
=================================================
	_OnCmdWaitEvents
=================================================
*/
	bool VulkanTraceConverter::_OnCmdWaitEvents (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		return false;
	}
	
/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*/
	bool VulkanTraceConverter::_OnCmdPipelineBarrier (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		return false;
	}

}	// VTC
