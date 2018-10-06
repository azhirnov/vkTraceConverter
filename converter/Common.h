// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

// from FrameGraph/stl
#include "stl/CompileTime/DefaultType.h"
#include "stl/Containers/ArrayView.h"
#include "stl/Containers/FixedArray.h"
#include "stl/Containers/StaticString.h"
#include "stl/Algorithms/Cast.h"
#include "stl/Algorithms/MemUtils.h"
#include "stl/Algorithms/EnumUtils.h"
#include "stl/Algorithms/StringUtils.h"
#include "stl/Math/Math.h"
#include "stl/Log/TimeProfiler.h"
#include "stl/Stream/FileStream.h"

#include <filesystem>

namespace VTC
{
	using namespace FG;
	namespace fs = std::filesystem;

}	// VTC
