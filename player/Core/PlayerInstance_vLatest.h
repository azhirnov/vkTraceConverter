// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "IPlayerInstance.h"
#include "Reader/TraceReader.h"
#include <atomic>
#include <thread>

namespace VTPlayer
{

	//
	// Player (latest version)
	//

	class PlayerInstance_vLatest final : public IPlayerInstance
	{
	// types
	private:
		using PipelineCacheData_t	= Array<uint8_t>;
		using PipelineCache_t		= Array< PipelineCacheData_t >;
		
		using PlayerCtor_t			= std::function< IPlayer* () >;

		enum class EMsgBits : uint {
			None				= 0,
			Play				= 1 << 0,
			Pause				= 1 << 1,
			UpdatePplnCache		= 1 << 2,
			Exit				= 1 << 30,
		};


	// variables
	private:
		std::atomic<uint>		_messageBits;
		std::atomic<uint>		_playerFinished;
		std::thread				_playerThread;

		SharedPtr<RStream>		_traceFile;
		SharedPtr<RStream>		_dataFile;

		PipelineCache_t			_pplnCache;

		const PlayerSettings	_playerSettings;
		const WindowSettings	_windowSettings;
		const VulkanSettings	_vulkanSettings;


	// methods
	public:
		PlayerInstance_vLatest (PlayerSettings &&playerSettings, WindowSettings &&windowSettings,
								VulkanSettings &&vulkanSettings);
		~PlayerInstance_vLatest ();


	// IPlayer implementation
	public:
		bool IsInitialized () const override;
		bool Play () override;
		bool Pause () override;
		bool IsRunning () override;
		void Release () override;
		bool LoadVkPipelineCache (const void *, size_t) override;
		bool GetVkPipelineCache (OUT void const* &, OUT size_t &) override;


	private:
		bool _OpenTrace (OUT PlayerCtor_t &);
		bool _RunPlayerThread (const PlayerCtor_t &);
	};


}	// VTPlayer
