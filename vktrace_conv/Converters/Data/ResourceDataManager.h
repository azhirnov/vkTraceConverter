// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "VkTraceCommon.h"		// for 64bit fseek
#include "Converters/Data/IResourceDataManager.h"
#include "Converters/Data/Block.h"

namespace VTC
{

	//
	// Resource Data Writer
	//

	class ResourceDataWriter final : public IResourceDataWriter
	{
	// variables
	private:
		Array< BlockHeader >	_blocks;		// will be stored at the end of archive
		FILE*					_file	= null;


	// methods
	public:
		ResourceDataWriter ();
		~ResourceDataWriter ();

		bool Create (StringView filename) override;
		bool Close () override;

		bool StoreData (uint64_t dataID, ArrayView<uint8_t> data) override;

	private:
		bool _Close ();
	};



	//
	// Resource Data Reader
	//

	class ResourceDataReader final : public IResourceDataReader
	{
	// variables
	private:
		HashMap< uint64_t, BlockHeader >	_blocks;
		FILE*								_file	= null;

		
	// methods
	public:
		ResourceDataReader ();
		~ResourceDataReader ();

		bool Open (StringView filename) override;
		bool Close () override;

		bool LoadData (uint64_t dataID, OUT Array<uint8_t> &data) override;

	private:
		bool _Close ();
	};

}	// VTC
//-----------------------------------------------------------------------------


	
#include "brotli/decode.h"
#include "brotli/encode.h"

namespace VTC
{
	//
	// Resource Data Encoder
	//
	/*
	class ResourceDataEncoder final : public IResourceDataWriter
	{
	// variables
	private:
		Array< BlockHeader >	_blocks;		// will be stored at the end of archive
		Array< uint8_t >		_temp;			// temporary buffer for compressing

		BrotliEncoderState*		_instance	= null;
		FILE*					_archive	= null;

		const uint				_quality;


	// methods
	public:
		ResourceDataEncoder ();
		~ResourceDataEncoder ();

		bool Create (StringView filename) override;
		bool Close () override;

		bool StoreData (uint64_t dataID, ArrayView<uint8_t> data) override;

	private:
		bool _Close ();
	};



	//
	// Resource Data Decoder
	//

	class ResourceDataDecoder final : public IResourceDataReader
	{
	// variables
	private:
		HashMap< uint64_t, BlockHeader >	_blocks;

		
	// methods
	public:
		ResourceDataDecoder ();
		~ResourceDataDecoder ();

		bool Open (StringView filename) override;
		bool Close () override;

		bool LoadData (uint64_t dataID, OUT Array<uint8_t> &data) override;

	private:
		bool _Close ();
	};
	
	*/
}	// VTC
