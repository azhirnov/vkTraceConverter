// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Data/ResourceDataManager.h"
#include "Converters/Converter.h"

namespace VTC
{

/*
=================================================
	RunDataConverter
=================================================
*
	bool RunDataConverter (const AppTrace &trace, const ConverterConfig &config, const ResourceDataWriterPtr &writer)
	{
	}

/*
=================================================
	constructor
=================================================
*
	ResourceDataWriter::ResourceDataWriter ()
	{
		_blocks.reserve( (size_t(4) << 20) / sizeof(BlockHeader) );	// alloc 4Mb
	}
	
/*
=================================================
	destructor
=================================================
*
	ResourceDataWriter::~ResourceDataWriter ()
	{
		_Close();
	}
	
/*
=================================================
	Create
=================================================
*
	bool ResourceDataWriter::Create (StringView filename)
	{
		_Close();

		CHECK_ERR( fopen_s( OUT &_file, filename.data(), "wb" ) == 0 );

		// write margic number
		CHECK_ERR( fwrite( &ResourceFileMagicNumber, sizeof(ResourceFileMagicNumber), 1, _file ) == 1 );

		return true;
	}
	
/*
=================================================
	Close
=================================================
*
	bool ResourceDataWriter::Close ()
	{
		return _Close();
	}
	
	bool ResourceDataWriter::_Close ()
	{
		if ( not _file )
			return true;


		// save blocks
		if ( not _blocks.empty() )
		{
			const int64_t		header_begin	= Ftell( _file );
			const uint64_t		block_count		= _blocks.size();

			CHECK_ERR( fwrite( &block_count, sizeof(block_count), 1, _file ) == 1 );

			CHECK_ERR( fwrite( _blocks.data(), sizeof(_blocks[0]), _blocks.size(), _file ) == _blocks.size() );

			CHECK_ERR( fwrite( &header_begin, sizeof(header_begin), 1, _file ) == 1 );
		}


		// close file
		fclose( _file );

		_file = null;
		_blocks.clear();

		return true;
	}
	
/*
=================================================
	StoreData
=================================================
*
	bool ResourceDataWriter::StoreData (uint64_t dataID, ArrayView<uint8_t> data)
	{
		CHECK_ERR( _file );

		BlockHeader		block = {};

		block.id		= dataID;
		block.offset	= Ftell( _file );
		block.dataSize	= size_t(ArraySizeOf( data ));

		BlockInfo		info = {};
		info.dataSize	= block.dataSize;


		CHECK_ERR( fwrite( &info, sizeof(info), 1, _file ) == 1 );

		CHECK_ERR( fwrite( data.data(), sizeof(data[0]), data.size(), _file ) == data.size() );

		return true;
	}
//-----------------------------------------------------------------------------



/*
=================================================
	constructor
=================================================
*
	ResourceDataReader::ResourceDataReader ()
	{
	}
	
/*
=================================================
	destructor
=================================================
*
	ResourceDataReader::~ResourceDataReader ()
	{
		_Close();
	}
	
/*
=================================================
	Open
=================================================
*
	bool ResourceDataReader::Open (StringView filename)
	{
		_Close();

		CHECK_ERR( fopen_s( OUT &_file, filename.data(), "wb" ) == 0 );

		// check magic number
		uint	magic = 0;
		CHECK_ERR( fread( &magic, sizeof(magic), 1, _file ) == sizeof(magic) );
		CHECK_ERR( magic == ResourceFileMagicNumber );


		// read headers
		CHECK_ERR( Fseek( _file, 0, SEEK_END ) == 0 );

		int64_t		end = Ftell( _file );
		CHECK_ERR( end > 0 );

		int64_t		header_offset	= 0;
		CHECK_ERR( fread( &header_offset, sizeof(header_offset), 1, _file ) == sizeof(header_offset) );
		CHECK_ERR( header_offset > 0 and header_offset < end );


		// read blocks
		CHECK_ERR( Fseek( _file, header_offset, SEEK_SET ) == 0 );

		uint64_t	max_block_count = (end - sizeof(uint64_t)*2 - header_offset) / sizeof(BlockHeader);
		uint64_t	block_count		= 0;

		CHECK_ERR( fread( &block_count, sizeof(block_count), 1, _file ) == sizeof(block_count) );
		CHECK_ERR( block_count > 0 and block_count < max_block_count );

		
		Array< BlockHeader >	buf;
		buf.reserve( (size_t(4) << 20) / sizeof(BlockHeader) );	// alloc 4Mb

		for (; block_count > 0;)
		{
			buf.resize(Min( block_count, buf.capacity() ));
			CHECK_ERR( fread( buf.data(), sizeof(buf[0]), buf.size(), _file ) == size_t(ArraySizeOf(buf)) );

			for (auto& b : buf) {
				_blocks.insert({ b.id, b });
			}

			block_count -= buf.size();
			buf.clear();
		}

		return true;
	}
	
/*
=================================================
	Close
=================================================
*
	bool ResourceDataReader::Close ()
	{
		return _Close();
	}

	bool ResourceDataReader::_Close ()
	{
		_blocks.clear();

		if ( _file )
		{
			fclose( _file );
			_file = null;
		}
		return true;
	}
	
/*
=================================================
	LoadData
=================================================
*
	bool ResourceDataReader::LoadData (uint64_t dataID, OUT Array<uint8_t> &data)
	{
		return true;
	}*/
//-----------------------------------------------------------------------------


#if 0	
/*
=================================================
	constructor
=================================================
*/
	ResourceDataEncoder::ResourceDataEncoder () :
		_quality{ 9 }
	{
		_instance = BrotliEncoderCreateInstance( null, null, null );
		
		BrotliEncoderSetParameter( _instance, BROTLI_PARAM_QUALITY, _quality );
		//BrotliEncoderSetParameter( _instance, BROTLI_PARAM_LARGE_WINDOW, 1u );
		//BrotliEncoderSetParameter( _instance, BROTLI_PARAM_LGWIN, (uint32_t)context->lgwin);
	}
	
/*
=================================================
	destructor
=================================================
*/
	ResourceDataEncoder::~ResourceDataEncoder ()
	{
		_Close();

		BrotliEncoderDestroyInstance( _instance );
	}
	
/*
=================================================
	Create
=================================================
*/
	bool ResourceDataEncoder::Create (StringView filename)
	{
		_Close();

		CHECK_ERR( fopen_s( OUT &_archive, filename.data(), "wb" ) == 0 );

		return true;
	}
	
/*
=================================================
	Close
=================================================
*/
	bool ResourceDataEncoder::Close ()
	{
		return _Close();
	}
	
	bool ResourceDataEncoder::_Close ()
	{
		if ( not _archive )
			return true;

		fclose( _archive );
		_archive = null;

		_temp.clear();
		_blocks.clear();

		return true;
	}

/*
=================================================
	StoreData
=================================================
*/
	bool ResourceDataEncoder::StoreData (uint64_t dataID, ArrayView<uint8_t> data)
	{
		return true;
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	constructor
=================================================
*/
	ResourceDataDecoder::ResourceDataDecoder ()
	{
	}
	
/*
=================================================
	destructor
=================================================
*/
	ResourceDataDecoder::~ResourceDataDecoder ()
	{
		_Close();
	}
	
/*
=================================================
	Open
=================================================
*/
	bool ResourceDataDecoder::Open (StringView filename)
	{
		return true;
	}
	
/*
=================================================
	Close
=================================================
*/
	bool ResourceDataDecoder::Close ()
	{
		return _Close();
	}
	
	bool ResourceDataDecoder::_Close ()
	{
		return true;
	}

/*
=================================================
	LoadData
=================================================
*/
	bool ResourceDataDecoder::LoadData (uint64_t dataID, OUT Array<uint8_t> &data)
	{
		return true;
	}
#endif

}	// VTC
