// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "engine/DrawCommand.h"

namespace VTC
{

	//
	// Command Buffer Builder
	//

	class CommandBufferBuilder
	{
	// variables
	private:
		CommandBufferID		_id;
		
	
	// methods
	public:
		CommandBufferBuilder ();
		
		void Draw (const DrawCommand &cmd);
	};


}	// VTC
