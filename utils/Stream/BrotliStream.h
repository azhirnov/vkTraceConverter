// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

// temp
#ifndef VTC_ENABLE_BROTLI
#	define VTC_ENABLE_BROTLI
#endif

#ifdef VTC_ENABLE_BROTLI

#include "stl/Stream/Stream.h"
#include "brotli/decode.h"
#include "brotli/encode.h"

namespace VTC
{
	using namespace FG;


	//
	// Read-only Brotli Uncompression Stream
	//

	class BrotliRStream final : public RStream
	{
	// variables
	private:
		UniquePtr<RStream>		_stream;
		BrotliDecoderState*		_instance	= null;
		Array<uint8_t>			_buffer;
		BytesU					_position;

		static const size_t		_BufferSize	= 4u << 20;


	// methods
	public:
		explicit BrotliRStream (UniquePtr<RStream> &&);
		~BrotliRStream () override;

		bool	IsOpen ()	const override		{ return _instance and _stream; }
		BytesU	Position ()	const override		{ return _position; }
		BytesU	Size ()		const override		{ return _stream->Size(); }
		
		bool	SeekSet (BytesU pos) override;
		BytesU	Read2 (OUT void *buffer, BytesU size) override;

	};


	
	//
	// Write-only Brotli Compression Stream
	//

	class BrotliWStream final : public WStream
	{
	// variables
	private:
		UniquePtr<WStream>		_stream;
		BrotliEncoderState*		_instance	= null;
		Array<uint8_t>			_buffer;
		BytesU					_position;

		static const size_t		_BufferSize	= 4u << 20;


	// methods
	public:
		explicit BrotliWStream (UniquePtr<WStream> &&);
		~BrotliWStream () override;
		
		bool	IsOpen ()	const override		{ return _instance and _stream; }
		BytesU	Position ()	const override		{ return _position; }
		BytesU	Size ()		const override		{ return Position(); }
		
		BytesU	Write2 (const void *buffer, BytesU size) override;
		void	Flush () override				{ _Flush(); }

	private:
		bool _Flush ();
	};


}	// VTC

#endif	// VTC_ENABLE_BROTLI
