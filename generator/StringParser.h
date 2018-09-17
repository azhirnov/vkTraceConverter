// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "stl/include/ArrayView.h"

namespace VTC
{
	using namespace FG;


	//
	// String Parser
	//

	struct StringParser
	{
		static void ToEndOfLine		(StringView str, INOUT size_t &pos);
		static void ToNextLine		(StringView str, INOUT size_t &pos);
		static void ToBeginOfLine	(StringView str, INOUT size_t &pos);

		static void DivideLines (StringView str, OUT Array<StringView> &lines);
		static bool DivideString_CPP (StringView str, OUT Array<StringView> &tokens);
	};


}	// VTC
