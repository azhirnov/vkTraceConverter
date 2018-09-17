// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

namespace VTC
{

	//
	// Float/Int Value
	//

	struct FIValue
	{
		union {
			float	f;
			int		i;
			uint	u;
		};

		FIValue () : i{0} {}
		FIValue (float val) : f{val} {}
		FIValue (int val) : i{val} {}
		FIValue (uint val) : u{val} {}
	};


}	// VTC
