// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Core/Settings.h"
#include "stl/Containers/AlignedBuffer.h"
#include "stl/CompileTime/TypeList.h"

namespace VTPlayer
{
	using namespace FG;

#	include "Types/VkResourceTypes.h"
#	include "Types/TracePacketHeader.h"
#	include "Types/TraceFileHeader.h"
#	include "IDs/EPacketIDs.h"



	//
	// Trace Reader
	//

	class TraceReader
	{
	// variables
	private:
		AlignedBuffer<alignof(size_t)>	_buffer;
		TracePacketHeader				_packet;

		SharedPtr<RStream>				_file;
		BytesU							_offset;
		
		static constexpr size_t			_MaxBufferSize	= (4u << 20);


	// methods
	public:
		explicit TraceReader (const SharedPtr<RStream> &file);
		~TraceReader ();

		bool ReadNext ();

		ND_ bool		IsOpen ()			const		{ return _file and _file->IsOpen(); }
		ND_ EPacketID	GetPacketID ()		const		{ return BitCast<EPacketID>( _packet.id ); }
		ND_ void *		GetPacketData ()				{ return _buffer.data(); }
		ND_ void const*	GetPacketData ()	const		{ return _buffer.data(); }
		ND_ BytesU		GetPacketOffset ()	const		{ return BytesU(_packet.offset); }
		ND_ BytesU		GetPacketSize ()	const		{ return BytesU(_packet.size); }
	};


}	// VTPlayer
