// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Interfaces for simple virtual file system.
	VFS used to pack shaders, buffer data, image data and all other large data.
*/

#pragma once

#include "VkTraceCommon.h"

namespace VTC
{

	//
	// Resource Data Writer interface
	//

	class IResourceDataWriter : public std::enable_shared_from_this< IResourceDataWriter >
	{
	public:
		using DataID	= uint;

		virtual ~IResourceDataWriter () {}

		// create new archive.
		// all data will be packed into this archive.
		virtual bool Create (StringView filename) = 0;

		// write some additional information to the archive and close.
		virtual bool Close () = 0;

		// store data into current archive, error will be generated if archive doesn't exists.
		// information for fast access stored into header and will be saved when archive closed.
		virtual bool StoreData (OUT DataID &dataID, const void *data, BytesU size) = 0;

		virtual bool AddDataUsage (DataID id, FrameID frameId) = 0;
	};



	//
	// Resource Data Reader interface
	//
	/*
	class IResourceDataReader
	{
	public:
		virtual ~IResourceDataReader () {}

		virtual bool Open (StringView filename) = 0;

		virtual bool Close () = 0;

		virtual bool LoadData (uint64_t dataID, OUT Array<uint8_t> &data) = 0;
	};*/


	using ResourceDataWriterPtr = SharedPtr< IResourceDataWriter >;


}	// VTC
