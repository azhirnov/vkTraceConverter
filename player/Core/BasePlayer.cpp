// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "BasePlayer.h"

namespace VTPlayer
{

/*
=================================================
	_SetSourceFPS
=================================================
*
	bool BasePlayer::_SetSourceFPS (Unpacker &unpacker)
	{
		_sourceFPS << unpacker;
		return true;
	}

/*
=================================================
	_CalcFirstFrame
=================================================
*
	BasePlayer::FrameID  BasePlayer::_CalcFirstFrame (FrameID frameId, uint64_t dataSize)
	{
		return FrameID( uint64_t(frameId) - Max( uint64_t(frameId), (dataSize >> 24) ));
	}
	
/*
=================================================
	_SetSourceFPS
=================================================
*
	bool BasePlayer::_SetData (Unpacker &unpacker)
	{
		FilePart	part;
		part.id << unpacker;
		part.offset << unpacker;
		part.size << unpacker;
		part.firstFrame << unpacker;
		part.lastFrame << unpacker;

		_unloadEvents.insert({ part.lastFrame, {} }).first->second.push_back( part.id );
		_loadEvents.insert({ part.firstFrame, {} }).first->second.push_back( std::move(part) );

		return true;
	}
	*/

}	// VTPlayer
