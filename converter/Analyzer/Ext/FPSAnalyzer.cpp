// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Ext/FPSAnalyzer.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	FPSAnalyzer::FPSAnalyzer ()
	{
	}
	
/*
=================================================
	PreProcess
=================================================
*/
	void FPSAnalyzer::PreProcess (const class AppTrace &)
	{
		_averageFPS		= 0.0;
		_lastUpdateTime	= 0;
		_updateCounter	= 0;
		_fpsHistory.clear();
	}

/*
=================================================
	Process
=================================================
*/
	void FPSAnalyzer::Process (const TraceRange::Iterator &pos)
	{
		switch ( pos->packet_id )
		{
			// initialize
			case VKTRACE_TPI_VK_vkCreateDevice :
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :
			{
				_updateCounter	= 0;
				_lastUpdateTime = pos->vktrace_begin_time;
				break;
			}

			// Present
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
			{
				++_updateCounter;

				const uint64_t	dt = pos->vktrace_begin_time - _lastUpdateTime;

				if ( dt > _historyRate )
				{
					_fpsHistory.push_back( double(_updateCounter) * 1.0e9 / double(dt) );

					_updateCounter	= 0;
					_lastUpdateTime = pos->vktrace_begin_time;
				}
				break;
			}

			// last updates
			case VKTRACE_TPI_VK_vkDestroySurfaceKHR :
			case VKTRACE_TPI_VK_vkDestroySwapchainKHR :
			case VKTRACE_TPI_VK_vkDestroyDevice :
			{
				if ( _updateCounter )
				{
					_fpsHistory.push_back( double(_updateCounter) * 1.0e9 / double(pos->vktrace_begin_time - _lastUpdateTime) );

					_updateCounter	= 0;
					_lastUpdateTime = pos->vktrace_begin_time;
				}
				break;
			}
		}
	}
	
/*
=================================================
	PostProcess
=================================================
*/
	void FPSAnalyzer::PostProcess ()
	{
		_averageFPS = 0.0;

		for (auto& fps : _fpsHistory) {
			_averageFPS += fps;
		}

		_averageFPS /= double(_fpsHistory.size());
	}


}	// VTC
