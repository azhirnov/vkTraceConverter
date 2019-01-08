// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Settings.h"

namespace VTPlayer
{

	//
	// Player interface
	//

	class IPlayer
	{
	// interface
	public:
		virtual ~IPlayer () {}

		virtual bool Play () = 0;
		virtual bool Pause () = 0;

		virtual bool Init (IWindow *) = 0;
		virtual bool Draw () = 0;
	};


}	// VTPlayer
