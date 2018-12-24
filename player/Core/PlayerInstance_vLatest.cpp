// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "PlayerInstance_vLatest.h"
#include "Public/VTPlayer.h"
#include "Vulkan/VkPlayer.h"
#include "FrameGraph/FGPlayer.h"
#include "framework/Window/WindowGLFW.h"
#include "framework/Window/WindowSDL2.h"
#include "framework/Window/WindowSFML.h"

namespace VTPlayer
{

/*
=================================================
	constructor
=================================================
*/
	PlayerInstance_vLatest::PlayerInstance_vLatest (PlayerSettings &&playerSettings, WindowSettings &&windowSettings,
													VulkanSettings &&vulkanSettings) :
		_playerFinished{ ATOMIC_FLAG_INIT },
		_playerSettings{ playerSettings },	_windowSettings{ windowSettings },
		_vulkanSettings{ vulkanSettings }
	{
		_messageBits = 0;
		_playerFinished = 0;
	}
	
/*
=================================================
	destructor
=================================================
*/
	PlayerInstance_vLatest::~PlayerInstance_vLatest ()
	{
	}
	
/*
=================================================
	IsInitialized
=================================================
*/
	bool PlayerInstance_vLatest::IsInitialized () const
	{
		return (_traceFile != null);
	}

/*
=================================================
	Play
=================================================
*/
	bool PlayerInstance_vLatest::Play ()
	{
		if ( IsInitialized() )
		{
			_messageBits |= uint(EMsgBits::Play);
			return true;
		}

		PlayerCtor_t	ctor;
		CHECK_ERR( _OpenTrace( OUT ctor ));

		_playerThread = std::thread{ [ctor = std::move(ctor), this] ()
		{
			_RunPlayerThread( ctor );
		}};

		return true;
	}
	
/*
=================================================
	Pause
=================================================
*/
	bool PlayerInstance_vLatest::Pause ()
	{
		_messageBits |= uint(EMsgBits::Pause);
		return true;
	}
	
/*
=================================================
	IsRunning
=================================================
*/
	bool PlayerInstance_vLatest::IsRunning ()
	{
		return not _playerFinished;
	}

/*
=================================================
	Release
=================================================
*/
	void PlayerInstance_vLatest::Release ()
	{
		_messageBits |= uint(EMsgBits::Exit);
		_playerThread.join();

		delete this;
	}
	
/*
=================================================
	LoadVkPipelineCache
=================================================
*/
	bool PlayerInstance_vLatest::LoadVkPipelineCache (const void *data, size_t dataSize)
	{
		_pplnCache.push_back( PipelineCacheData_t{ BitCast<const uint8_t*>(data), BitCast<const uint8_t*>(data) + dataSize });

		// TODO
		_messageBits |= uint(EMsgBits::UpdatePplnCache);
		return false;
	}
	
/*
=================================================
	GetVkPipelineCache
=================================================
*/
	bool PlayerInstance_vLatest::GetVkPipelineCache (OUT void const* &data, OUT size_t &size)
	{
		// TODO:
		// merge all pipeline cache into one, get cache data and return
		return false;
	}
	
/*
=================================================
	_OpenTrace
=================================================
*/
	bool PlayerInstance_vLatest::_OpenTrace (OUT PlayerCtor_t &ctor)
	{
		_traceFile.reset( new FileRStream{ _playerSettings.traceFilename });
		CHECK_ERR( _traceFile->IsOpen() );

		if ( _playerSettings.dataFilename.size() > 0 )
		{
			_dataFile.reset( new FileRStream{ _playerSettings.dataFilename });
			CHECK_ERR( _dataFile->IsOpen() );
		}


		// read header
		TraceFileHeader		header;
		CHECK_ERR( _traceFile->Read( OUT header ));

		CHECK_ERR( header.magic == TraceFileHeader::MagicNumber );
		CHECK_ERR( header.pointerSize == sizeof(void*) );
		CHECK_ERR( header.instructionBlockOffset == sizeof(header) );	// not supported
		CHECK_ERR( header.dataBlockOffset == UMax );					// not supported

		switch ( header.archiveType )
		{
			case TraceFileHeader::EArchiveType::None :
				break;

			case TraceFileHeader::EArchiveType::Brotli : {
				// reopen as brotli decoder stream
				ASSERT(false);	// TODO
				break;
			}

			default :
				RETURN_ERR( "unsupported archive type!" );
		}

		switch ( header.instructionSet )
		{
			case EPacketID::_VulkanApi | EPacketID::_V100 :
				ctor = [this] () { return new VkPlayer_v100( _vulkanSettings, _windowSettings, _playerSettings, _traceFile, _dataFile ); };
				break;
				
			case EPacketID::_FrameGraphApi | EPacketID::_V100 :
				ctor = [this] () { return new FGPlayer_v100( _vulkanSettings, _windowSettings, _playerSettings, _traceFile, _dataFile ); };
				break;

			default :
				RETURN_ERR( "unsupported instruction set!" );
		}

		return true;
	}
	
/*
=================================================
	_RunPlayerThread
=================================================
*/
	bool PlayerInstance_vLatest::_RunPlayerThread (const PlayerCtor_t &ctor)
	{
		UniquePtr<IPlayer>	player{ ctor() };
		WindowPtr			window;
		
#	 if defined(FG_ENABLE_GLFW)
		window.reset( new WindowGLFW() );

#	 elif defined(FG_ENABLE_SDL2)
		window.reset( new WindowSDL2() );
		
#	 elif defined(FG_ENABLE_SFML)
		window.reset( new WindowSFML() );

#	 else
#		error unknown window library!
#	 endif
		
		CHECK_ERR( window->Create( _windowSettings.size, _windowSettings.title ));
		//window->AddListener( this );

		CHECK_ERR( player->Init( window.get() ));


		// main loop
		for (;;)
		{
			const EMsgBits	msg = EMsgBits(_messageBits.exchange( 0 ));

			if ( EnumEq( msg, EMsgBits::Exit ) )
				break;

			if ( EnumEq( msg, EMsgBits::Pause ) )
				CHECK( player->Pause() );

			if ( EnumEq( msg, EMsgBits::Play ) )
				CHECK( player->Play() );

			if ( not player->Draw() )
				break;
		}

		player.reset();
		window.reset();

		_playerFinished = true;
		return true;
	}


}	// VTPlayer

