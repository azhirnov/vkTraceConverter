// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Common.h"

extern void Test_VPacker ();
extern void Test_BrotliStream ();


int main ()
{
	Test_BrotliStream();
	Test_VPacker();

	return 0;
}
