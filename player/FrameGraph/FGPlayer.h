// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Core/IPlayer.h"
#include "Reader/TraceReader.h"
#include "stl/Memory/LinearAllocator.h"
#include "FrameGraph/VFG.h"

#if defined(FG_OPTIMIZE_IDS) and FG_OPTIMIZE_IDS
#	error not supported
#endif

namespace VTPlayer
{
#	include "IDs/EFrameGraphPacketIDs.h"

	struct FGUnpacker;



	//
	// Frame Graph Trace Player
	//

	class FGPlayer_v100 final : public IPlayer, public IWindowEventListener
	{
	// types
	public:
		using DataID		= uint;
		using FrameID		= uint;
		using Index_t		= uint;
		
	private:
		class ShaderModule final : public PipelineDescription::IShaderData< ShaderModuleVk_t >
		{
		public:
			VkShaderModule		_module		= VK_NULL_HANDLE;
			StaticString<64>	_entry;
			
		public:
			ShaderModule (VkShaderModule module, StringView entry) :
				_module{ module }, _entry{ entry } {}
		
			ShaderModuleVk_t const&		GetData () const override		{ return BitCast<ShaderModuleVk_t>( _module ); }
			StringView					GetEntry () const override		{ return _entry; }
			size_t						GetHashOfData () const override	{ ASSERT(false);  return 0; }
		};
		using VkShaderPtr	= PipelineDescription::VkShaderPtr;

		using Descriptors_t	= FixedArray< PipelineResources, FG_MaxDescriptorSets >;

		struct FrameData
		{
			FGThreadPtr		thread;
			Task			task;
			Descriptors_t	descriptors;
		};

		struct Resources
		{
			Array< GPipelineID >	gpipelines;
			Array< CPipelineID >	cpipelines;
			Array< MPipelineID >	mpipelines;
			Array< RTPipelineID >	rtpipelines;
			Array< SamplerID >		samplers;
			Array< ImageID >		images;
			Array< BufferID >		buffers;
			Array< VkShaderPtr >	shaders;
			Array< LogicalPassID >	logicalPasses;
		};
		
		struct FilePart
		{
			DataID				id				= UMax;
			uint64_t			offset			= 0;
			uint64_t			size			= 0;
			FrameID				firstFrame		= FrameID(0);	// frame when data will be requested at first time
			FrameID				lastFrame		= FrameID(0);	// frame when data can be unloaded
		};

		using DataBuffer_t		= Array<uint8_t>;
		using DataMap_t			= HashMap< DataID, DataBuffer_t >;
		using LoadEvents_t		= HashMap< FrameID, Array<FilePart> >;
		using UnloadEvents_t	= HashMap< FrameID, Array<DataID> >;
		
		using Nonoseconds		= std::chrono::nanoseconds;
		using TimePoint_t		= std::chrono::time_point< std::chrono::high_resolution_clock >;


	// variables
	private:
		TraceReader				_trace;
		SharedPtr<RStream>		_dataFile;

		VulkanDeviceExt			_vulkan;
		IWindow *				_window				= null;

		FGInstancePtr			_fgInstance;
		Array<FrameData>		_frameGraphThreads;

		Resources				_resources;
		
		FrameID					_currFrameId		= 0;
		bool					_isPaused			= false;
		bool					_playOneFrame		= false;
		bool					_isFinished			= false;
		bool					_playWithSourceFPS	= true;
		uint8_t					_visualizeGraph		= 0;
		uint					_graphCounter		= 0;
		TimePoint_t				_lastPresentTime;

		LinearAllocator<>		_perPacketAllocator;	// allocate memory when process packet and recycle before processing next packet
		
		DataMap_t				_loadableData;
		LoadEvents_t			_loadEvents;
		UnloadEvents_t			_unloadEvents;

		VulkanSettings const&	_vulkanSettings;
		WindowSettings const&	_windowSettings;
		PlayerSettings const&	_playerSettings;
		
		uint					_implementationFlags	= 0;
		
		// profiling
		struct {
			FrameID					frameId				= 0;
			uint					frameCounter		= 0;
			uint					averageFPS			= 0;	// measure in cpu-side
			Nonoseconds				averageFTime;				// measure in gpu-side
			Nonoseconds				accumFTime;
			TimePoint_t				lastUpdateTime;
		}						_profiling;
		

	// methods
	public:
		FGPlayer_v100 (const VulkanSettings &, const WindowSettings &, const PlayerSettings &,
					   const SharedPtr<RStream> &, const SharedPtr<RStream> &);
		~FGPlayer_v100 () override;


	// IPlayer implementation
	public:
		bool Play () override;
		bool Pause () override;
		bool Init (IWindow *) override;
		bool Draw () override;

	// IWindowEventListener implementation
	public:
		void OnResize (const uint2 &size) override;
		void OnRefresh () override {}
		void OnDestroy () override;
		void OnUpdate () override {}
		void OnKey (StringView, EKeyAction) override;
		void OnMouseMove (const float2 &) override {}


	private:
		void _Destroy ();

		bool _RunCommand ();
		bool _RunCommand2 (EFrameGraphPacketID, FGUnpacker &);

		bool _PrepareData (FrameID frameId);
		bool _LoadDataPart (FilePart &part);
		bool _SetData (FGUnpacker &);
		ND_ ArrayView<uint8_t>  _LoadData (DataID id) const;

		bool _CreateGraphicsPipeline (FGUnpacker &);
		bool _CreateComputePipeline (FGUnpacker &);
		bool _CreateMeshPipeline (FGUnpacker &);
		bool _CreateRayTracingPipeline (FGUnpacker &);
		bool _CreateSampler (FGUnpacker &);
		bool _CreateImage (FGUnpacker &);
		bool _CreateBuffer (FGUnpacker &);
		bool _CreateShaderModule (FGUnpacker &);
		bool _UnpackPipelineLayout (OUT PipelineDescription::PipelineLayout &, FGUnpacker &) const;
		bool _DestroyGraphicsPipeline (FGUnpacker &);
		bool _DestroyComputePipeline (FGUnpacker &);
		bool _DestroyMeshPipeline (FGUnpacker &);
		bool _DestroyRayTracingPipeline (FGUnpacker &);
		bool _DestroySampler (FGUnpacker &);
		bool _DestroyImage (FGUnpacker &);
		bool _DestroyBuffer (FGUnpacker &);
		bool _CreateRenderPass (FGUnpacker &);
		bool _CreateFrameGraphThread (FGUnpacker &);
		
		bool _SubmitRenderPass (FGUnpacker &);
		bool _DispatchCompute (FGUnpacker &);
		bool _DispatchComputeIndirect (FGUnpacker &);
		bool _CopyBuffer (FGUnpacker &);
		bool _CopyImage (FGUnpacker &);
		bool _CopyBufferToImage (FGUnpacker &);
		bool _CopyImageToBuffer (FGUnpacker &);
		bool _BlitImage (FGUnpacker &);
		bool _ResolveImage (FGUnpacker &);
		bool _FillBuffer (FGUnpacker &);
		bool _ClearColorImage (FGUnpacker &);
		bool _ClearDepthStencilImage (FGUnpacker &);
		bool _UpdateBuffer (FGUnpacker &);
		bool _ReadBuffer (FGUnpacker &);
		bool _UpdateImage (FGUnpacker &);
		bool _ReadImage (FGUnpacker &);
		bool _Present (FGUnpacker &);
		bool _PresentVR (FGUnpacker &);
		bool _BeginFrame (FGUnpacker &);
		bool _EndFrame (FGUnpacker &);
		bool _BeginThread (FGUnpacker &);
		bool _EndThread (FGUnpacker &);
		bool _UpdateHostBuffer (FGUnpacker &);
		
		bool _DrawVertices (FGUnpacker &);
		bool _DrawIndexed (FGUnpacker &);
		bool _DrawMeshes (FGUnpacker &);
		bool _DrawVerticesIndirect (FGUnpacker &);
		bool _DrawIndexedIndirect (FGUnpacker &);
		bool _DrawMeshesIndirect (FGUnpacker &);
		bool _ClearAttachments (FGUnpacker &);

		template <typename TaskType>
		bool _UnpackBaseDrawVertices (OUT _fg_hidden_::BaseDrawVertices<TaskType> &, FrameData &, FGUnpacker &) const;
		
		template <typename TaskType, typename PipelineID>
		bool _UnpackBaseDrawCall (OUT _fg_hidden_::BaseDrawCall<TaskType> &, FrameData &, const PipelineID &, FGUnpacker &) const;

		template <typename PipelineID>
		bool _UnpackDescriptors (OUT PipelineResourceSet &, FrameData &, const PipelineID &, FGUnpacker &) const;
		
		template <typename TaskType>
		bool _UnpackScissors (OUT _fg_hidden_::BaseDrawCall<TaskType> &, FGUnpacker &) const;

		bool _InitializeResource (EFrameGraphPacketID, FGUnpacker &);
		bool _CreateDevice (FGUnpacker &);
		bool _CreateDevice (const struct VulkanCreateInfo &ci);
		bool _CreateFrameGraph ();

		bool _UpdateFrameStatistic ();
	};


}	// VTPlayer
