// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Common.h"
#include "stl/Stream/FileStream.h"
#include "../utils/Stream/BrotliStream.h"

using namespace VTC;



extern void Test_BrotliStream ()
{
	const String	str1 = "12i12ienmqpwom12euj1029podmksjhjbjcnalsmoiiwujkcmsalsc,posaasjncsalkmxaz";

	// compress
	{
		BrotliWStream	encoder{ UniquePtr<WStream>{ new FileWStream{"temp.bin"}} };

		TEST( encoder.IsOpen() );
		TEST( encoder.Write( str1 ));
	}

	// uncompress
	{
		BrotliRStream	decoder{ UniquePtr<RStream>{ new FileRStream("temp.bin")} };
		String			str2;

		TEST( decoder.IsOpen() );
		TEST( decoder.Read( str1.length(), OUT str2 ));

		TEST( str1 == str2 );
	}
}
