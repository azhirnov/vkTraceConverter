// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Parser/AppTrace.h"

namespace VTC
{
	
/*
=================================================
	AddAnalyzer
=================================================
*/
	void AppTrace::AddAnalyzer (AnalyzerPtr &&value)
	{
		ASSERT( _fullTrace.empty() );	// trace already processed, new analyzer never be used

		_analyzers.push_back( std::move(value) );
	}
	
/*
=================================================
	GetAnalyzer
=================================================
*/
	IAnalyzer const*  AppTrace::GetAnalyzer (std::type_index id) const
	{
		for (auto& analyzer : _analyzers)
		{
			if ( analyzer->GetType() == id )
				return analyzer.get();
		}
		return null;
	}

/*
=================================================
	GetFrameTrace
=================================================
*/
	TraceRange  AppTrace::GetFrameTrace (FrameID id) const
	{
		CHECK_ERR( id < _presentBookmarks.size() );

		if ( id == 0 )
			return _fullTrace.SubRange( _fullTrace.FirstBookmark(), _presentBookmarks.front() );

		return _fullTrace.SubRange( _presentBookmarks[id-1], _presentBookmarks[id] );
	}

/*
=================================================
	Open
=================================================
*/
	bool AppTrace::Open (StringView filename)
	{
		Close();
		FG_TIMEPROFILER();

		_traceFile.reset( new FileRStream{ filename });
		CHECK_ERR( _traceFile->IsOpen() );

		return _ProcessTrace();
	}

	bool AppTrace::Open (const fs::path &path)
	{
		Close();
		FG_TIMEPROFILER();
		
		_traceFile.reset( new FileRStream{ path });
		CHECK_ERR( _traceFile->IsOpen() );

		return _ProcessTrace();
	}
	
/*
=================================================
	Close
=================================================
*/
	void AppTrace::Close ()
	{
		_fullTrace	= Default;
		_traceFile	= null;

		_fileHeader	= Default;
		_gpuInfo.clear();
		_portabilityTable.clear();

		_presentBookmarks.clear();
	}
	
/*
=================================================
	_ProcessTrace
----
	this is first trace processing pass,
	run analyzers for each packet,
	bookmark all resource usage
=================================================
*/
	bool AppTrace::_ProcessTrace ()
	{
		CHECK_ERR( _traceFile->Read( OUT _fileHeader ));
		CHECK_ERR( _traceFile->Read( _fileHeader.n_gpuinfo, _gpuInfo ));

		_fullTrace = TraceRange{ _traceFile };

		FrameID		frame_id	= 0;
		bool		new_frame	= false;
		uint		progress	= 0;
		
		// pre processing
		for (auto& analyzer : _analyzers) {
			analyzer->PreProcess( *this );
		}

		for (auto iter = _fullTrace.begin(); iter < _fullTrace.LastBookmark(); ++iter)
		{
			ASSERT( iter->tracer_id == VKTRACE_TID_VULKAN );

			_uniqueThreads.insert( iter->thread_id );

			// add bookmark to next frame
			if ( new_frame )
			{
				ASSERT( frame_id != UMax );
				++frame_id;

				_presentBookmarks.push_back( iter.GetBookmark() );
				new_frame = false;
			}

			// skip packet if failed
			if ( not CheckPacketErrors( iter ) )
				continue;

			// analyze before bookmarking
			for (auto& analyzer : _analyzers)
			{
				analyzer->Process( iter );
			}

			// search in function arguments and struct data to find vulkan resource usage and add bookmarks
#			include "Generated/BuildFunctionResourceBookmarks.h"


			// divide by frames
			switch ( iter->packet_id )
			{
				case VKTRACE_TPI_VK_vkQueuePresentKHR :
					new_frame = true;
					break;
			}

			const BytesU	diff		= _fullTrace.LastBookmark().Value() - iter.GetBookmark().Value();
			const uint		curr_progr	= 8 - uint((diff * 8) / _fullTrace.LastBookmark().Value());

			if ( curr_progr > progress )
			{
				progress = curr_progr;
				FG_LOGI( "progress: "s << ToString( (100 * progress + 7) / 8 ) << " %" );
			}
		}
		
		_presentBookmarks.push_back( _fullTrace.LastBookmark() );

		// post processing
		FG_LOGI( "run analyzers post process step" );

		for (auto& analyzer : _analyzers) {
			analyzer->PostProcess();
		}

		FG_LOGI( "total frames: "s << ToString(_presentBookmarks.size()) );
		FG_LOGI( "unique threads: "s << ToString(_uniqueThreads.size()) );
		return true;
	}
	
/*
=================================================
	CheckPacketErrors
=================================================
*/
	bool AppTrace::CheckPacketErrors (const Iterator &iter)
	{
		bool	result = true;

#		include "Generated/CheckPacketError.h"

		return result;
	}

/*
=================================================
	_AddStructBookmsrks
=================================================
*/
	void AppTrace::_AddStructBookmsrks (const VkBaseInStructure *header, const Iterator &iter, FrameID frame_id)
	{
		if ( _OverrideStructBookmarks( header, iter, frame_id ) )
			return;

#		include "Generated/BuildStructResourceBookmarks.h"
	}
	
/*
=================================================
	_OverrideStructBookmarks
=================================================
*/
	bool AppTrace::_OverrideStructBookmarks (const VkBaseInStructure *header, const Iterator &iter, FrameID frame_id)
	{
		switch ( header->sType )
		{
			case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET : {
				VkWriteDescriptorSet const&  value = *BitCast<VkWriteDescriptorSet const *>( header );
				
				if ( (value).pNext )
					_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
				
				_AddResourceBookmark( VK_OBJECT_TYPE_DESCRIPTOR_SET, ResourceID((value).dstSet), iter, frame_id, EResOp::Access );
				
				for (uint a = 0; (value).pImageInfo and a < (value).descriptorCount; ++a)
				{
					if ( value.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER )
					{
						_AddResourceBookmark( VK_OBJECT_TYPE_SAMPLER, ResourceID(((value).pImageInfo[a]).sampler), iter, frame_id, EResOp::Access );
					}					
					if ( value.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT )
					{
						_AddResourceBookmark( VK_OBJECT_TYPE_IMAGE_VIEW, ResourceID(((value).pImageInfo[a]).imageView), iter, frame_id, EResOp::Access );
					}
				}

				for (uint a = 0; (value).pBufferInfo and a < (value).descriptorCount; ++a) 
				{
					if ( value.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC )
					{
						_AddResourceBookmark( VK_OBJECT_TYPE_BUFFER, ResourceID(((value).pBufferInfo[a]).buffer), iter, frame_id, EResOp::Access );
					}
				}

				for (uint a = 0; (value).pTexelBufferView and a < (value).descriptorCount; ++a)
				{
					if ( value.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER or
						 value.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER )
					{
						_AddResourceBookmark( VK_OBJECT_TYPE_BUFFER_VIEW, ResourceID((value).pTexelBufferView[a]), iter, frame_id, EResOp::Access );
					}
				}
				return true;
			}
		}
		return false;
	}


}	// VTC
