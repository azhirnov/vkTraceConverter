// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "IPlayer.h"

namespace VTPlayer
{

	//
	// Player Instance interface
	//

	class IPlayerInstance
	{
	// interface
	public:
		virtual bool IsInitialized () const = 0;

		virtual bool Play () = 0;
		virtual bool Pause () = 0;
		virtual void Release () = 0;

		// Vulkan only
		virtual bool LoadVkPipelineCache (const void *, size_t) = 0;
		virtual bool GetVkPipelineCache (OUT void const* &, OUT size_t &) = 0;
	};

}	// VTPlayer
