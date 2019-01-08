// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

// from FrameGraph/stl
#include "stl/Common.h"
#include "stl/Containers/ArrayView.h"
#include "stl/Containers/FixedArray.h"
#include "stl/Containers/StaticString.h"
#include "stl/Containers/Ptr.h"
#include "stl/Algorithms/Cast.h"
#include "stl/Algorithms/EnumUtils.h"
#include "stl/Algorithms/StringUtils.h"
#include "stl/Math/Math.h"
#include "stl/Log/TimeProfiler.h"
#include "stl/Memory/MemUtils.h"
#include "stl/Stream/FileStream.h"

#ifndef FG_STD_FILESYSTEM
#	error C++17 filesystem support required!
#endif

//#define VTC_DETECT_RESOURCE_TRANSFER
#define VTC_DETECT_MEMORY_ALIASING

namespace VTC
{
	using namespace FG;
	namespace fs = std::filesystem;

}	// VTC
