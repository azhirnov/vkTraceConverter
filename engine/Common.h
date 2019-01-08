// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "stl/Algorithms/Cast.h"
#include "stl/Containers/Union.h"
#include "stl/Stream/FileStream.h"

#include "framework/Vulkan/VulkanDeviceExt.h"
#include "framework/Vulkan/VulkanSwapchain.h"
#include "framework/Window/IWindow.h"


namespace VTC
{
	using namespace FG;


	// for raw vulkan calls
	class VApp;
	using VDrawFrame_t = void (*) (const VApp &);


	// for framegraph
	class FGApp;
	using FGDrawFrame_t = void (*) (const FGApp &);
	


	// TODO: move it somewhere
	template <typename T, size_t S>
	inline void operator << (T (&dst)[S], const StaticArray<T,S> &src)
	{
		memcpy( dst, src.data(), sizeof(src) );
	}

}	// VTC
