// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Common.h"
#include <iostream>

extern void Test_VPacker ();
extern void Test_FGPacker ();
extern void Test_BrotliStream ();


int main ()
{
	Test_BrotliStream();
	Test_VPacker();
	Test_FGPacker();
	
    FG_LOGI( "Tests.Player finished" );
    std::cin.ignore();
	return 0;
}
