// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

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
