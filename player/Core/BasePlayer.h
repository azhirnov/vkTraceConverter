// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "IPlayer.h"

namespace VTPlayer
{
	struct Unpacker;


	//
	// Base Player
	//

	class BasePlayer : public IPlayer
	{
	// types
	public:
		using DataID			= uint;
		using FrameID			= uint;
		
		struct FilePart
		{
			DataID			id			= DataID(~0u);
			uint64_t		offset		= 0;
			uint64_t		size		= 0;
			FrameID			firstFrame	= FrameID(0);	// frame when data will be requested at first time
			FrameID			lastFrame	= FrameID(0);	// frame when data can be unloaded
		};
		
		using DataMap_t			= HashMap< DataID, Array<uint8_t> >;
		using LoadEvents_t		= HashMap< FrameID, Array<FilePart> >;
		using UnloadEvents_t	= HashMap< FrameID, Array<DataID> >;


	// variables
	protected:
		DataMap_t				_loadableData;
		LoadEvents_t			_loadEvents;
		UnloadEvents_t			_unloadEvents;
		
		uint					_sourceFPS;


	// methods
	public:
		BasePlayer ();

	protected:
		bool _SetSourceFPS (Unpacker &);
		bool _SetData (Unpacker &);

		ND_ static FrameID  _CalcFirstFrame (FrameID frameId, uint64_t dataSize);
	};


}	// VTPlayer
