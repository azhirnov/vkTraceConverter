// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Common.h"

#ifdef _MSC_VER
#	pragma warning (push)
#	pragma warning (disable: 4668)
#	pragma warning (disable: 4505)
#	pragma warning (disable: 4005)
#	pragma warning (disable: 4996)
#	pragma warning (disable: 4702)
#endif

#include "vulkan/vulkan.h"
#include "vktrace_trace_packet_identifiers.h"
#include "vktrace_vk_vk_packets.h"		// only for packet_*** types

#ifdef _MSC_VER
#	pragma warning (pop)
#endif


namespace VTC
{
	using ResourceID	= uint64_t;
	using FrameID		= uint32_t;
	using PacketID		= decltype(vktrace_trace_packet_header::packet_id);
	using ThreadID		= decltype(vktrace_trace_packet_header::thread_id);
	using EResourceType = VkObjectType;


	enum class EResOp
	{
		Construct,		// on resource constructor call

		Access,			// resource specified in function arguments or in structure

		IndirectAccess,	// resource dosn't specified, but used resource assotiated with current resource.
						// for example: indirect access to image view when framebuffer binded.

		Destruct,		// on direct/indirect desctructor call
	};

}	// VTC
