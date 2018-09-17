// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Interfaces for simple virtual file system.
	VFS used to pack shaders, buffer data, image data and all other loadable data.
*/

#pragma once

#include "Common.h"

namespace VTC
{

	//
	// Resource Data Writer interface
	//

	class IResourceDataWriter
	{
	public:
		virtual ~IResourceDataWriter () {}

		// create new archive.
		// all data will be packed into this archive.
		virtual bool Create (StringView filename) = 0;

		// write some additional information to the archive and close.
		virtual bool Close () = 0;

		// store data into current archive, error will be generated if archive doesn't exists.
		// information for fast access stored into header and will be saved when archive closed.
		virtual bool StoreData (uint64_t dataID, ArrayView<uint8_t> data) = 0;
	};



	//
	// Resource Data Reader interface
	//

	class IResourceDataReader
	{
	public:
		virtual ~IResourceDataReader () {}

		virtual bool Open (StringView filename) = 0;

		virtual bool Close () = 0;

		virtual bool LoadData (uint64_t dataID, OUT Array<uint8_t> &data) = 0;
	};


	using IResourceDataWriterPtr	= UniquePtr< IResourceDataWriter >;
	using IResourceDataReaderPtr	= UniquePtr< IResourceDataReader >;


}	// VTC
