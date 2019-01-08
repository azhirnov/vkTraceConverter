// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/FrameGraph/FrameGraphConverter.h"
#include "framegraph/Public/IPipelineCompiler.h"

namespace VTC
{

	//
	// Pipeline Converter
	//

	class FrameGraphConverter::PipelineConverter
	{
	// types
	public:
		using DataID	= TraceConverterBase::DataID;

		struct ShaderDataInfo
		{
			DataID			dataId		= UMax;
			uint			dataSize	= 0;
			uint			uid			= 0;
		};

		using ShaderDataCache_t		= HashMap< Array<uint>, ShaderDataInfo >;
		using ShaderDataPtr			= Pair< const Array<uint>, ShaderDataInfo > *;
		using ShaderMap_t			= HashMap< ResourceID, ShaderDataPtr >;

		using SpecConstants_t		= FG::PipelineDescription::SpecConstants_t;
		using FragmentOutputs_t		= FG::GraphicsPipelineDesc::FragmentOutputs_t;
		using VertexAttribs_t		= FG::GraphicsPipelineDesc::VertexAttribs_t;
		using TopologyBits_t		= FG::GraphicsPipelineDesc::TopologyBits_t;

		struct ShaderStage
		{
			EShader				shaderType		= Default;
			ShaderDataPtr		code			= null;
			String				entry;
			SpecConstants_t		specConstants;

			ShaderStage () {}

			ND_ bool  operator == (const ShaderStage &) const;
		};
		
		struct ShaderStageHash {
			ND_ HashVal  operator () (const ShaderStage &) const noexcept;
		};
		using ShaderStages_t	= FixedArray< ShaderStage, 8 >;

		using FG_PipelineLayout	= PipelineDescription::PipelineLayout;


		struct FG_GraphicsPipeline
		{
			FG_PipelineLayout	layout;
			RenderState			renderState;
			ShaderStages_t		shaders;
			FragmentOutputs_t	fragOutput;
			VertexAttribs_t		attribs;
			TopologyBits_t		supportedTopology;
			uint				patchControlPoints	= 0;
			bool				earlyFragmentTests	= true;

			FG_GraphicsPipeline () {}

			ND_ bool  operator == (const FG_GraphicsPipeline &) const;
		};

		struct FG_GraphicsPipelineHash {
			ND_ size_t  operator () (const FG_GraphicsPipeline &) const noexcept;
		};

		using FG_GraphicsPipelines_t	= HashMap< FG_GraphicsPipeline, RawGPipelineID, FG_GraphicsPipelineHash >;
		using FG_GraphicsPipelinePtr	= Pair< const FG_GraphicsPipeline, RawGPipelineID > *;


		struct FG_ComputePipeline
		{
			FG_PipelineLayout	layout;
			ShaderStage			shader;
			uint3				localGroupSize;
			uint3				localSizeSpec	{ ~0u };

			FG_ComputePipeline () {}

			ND_ bool  operator == (const FG_ComputePipeline &) const;
		};

		struct FG_ComputePipelineHash {
			ND_ size_t  operator () (const FG_ComputePipeline &) const noexcept;
		};

		using FG_ComputePipelines_t		= HashMap< FG_ComputePipeline, RawCPipelineID, FG_ComputePipelineHash >;
		using FG_ComputePipelinePtr		= Pair< const FG_ComputePipeline, RawCPipelineID > *;
		//-----------------------------------------------------------------


		struct GraphicsPipelineInfo
		{
			using DynamicStates_t	= HashSet< VkDynamicState >;
			using Viewports_t		= FixedArray< VkViewport, FG_MaxViewports >;
			using Scissors_t		= FixedArray< VkRect2D, FG_MaxViewports >;

			DynamicStates_t				dynamicStates;
			Viewports_t					viewports;
			Scissors_t					scissors;
			VertexInputState			vertexInput;
			ResourceID					layout			= 0;
			EPrimitive					topology		= Default;
			bool						primitiveRestart= false;
			FG_GraphicsPipelinePtr		fgPipeline		= null;
		};

		struct ComputePipelineInfo
		{
			ResourceID					layout	= 0;
			FG_ComputePipelinePtr		fgPipeline		= null;
		};

		struct PipelineLayoutInfo
		{
			using DsLayouts_t		= FixedArray< ResourceID, FG_MaxDescriptorSets >;
			using PushConstants_t	= FixedMap< PushConstantID, VkPushConstantRange, FG_MaxPushConstants >;

			DsLayouts_t			dslayouts;
			PushConstants_t		pushConstantRanges;

			ND_ bool IsCompatiblePushConstants (const PipelineLayoutInfo &) const;
		};


		struct DescriptorSetLayout
		{
			struct Descriptor
			{
			    VkDescriptorType	descriptorType	= VK_DESCRIPTOR_TYPE_MAX_ENUM;
			    VkShaderStageFlags	stageFlags		= 0;
			};

			Array<Descriptor>	descriptors;
		};


		using GraphicsPipelines_t		= HashMap< ResourceID, GraphicsPipelineInfo >;
		using ComputePipelines_t		= HashMap< ResourceID, ComputePipelineInfo >;
		using PipelineLayouts_t			= HashMap< ResourceID, PipelineLayoutInfo >;
		using DescriptorSetLayouts_t	= HashMap< ResourceID, DescriptorSetLayout >;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		ShaderMap_t				_shaderMap;
		ShaderDataCache_t		_shaderDataCache;
		uint					_shaderCounter			= 0;

		GraphicsPipelines_t		_graphicsPipelines;
		FG_GraphicsPipelines_t	_gpipelineCache;
		uint					_graphicsPplnCounter	= 0;

		ComputePipelines_t		_computePipelines;
		FG_ComputePipelines_t	_cpipelineCache;
		uint					_computePplnCounter		= 0;

		PipelineLayouts_t		_pipelineLayouts;
		DescriptorSetLayouts_t	_dsLayouts;

		IPipelineCompilerPtr	_pplnCompiler;


	// methods
	public:
		explicit PipelineConverter (FrameGraphConverter &conv) : _fgConv{conv} {}
		
		bool Convert (INOUT TracePacker &) const;

		bool CreateShaderModule (const TraceRange::Iterator &);
		bool DestroyShaderModule (const TraceRange::Iterator &);
		bool CreateDescriptorSetLayout (const TraceRange::Iterator &);
		bool DestroyDescriptorSetLayout (const TraceRange::Iterator &);
		bool CreatePipelineLayout (const TraceRange::Iterator &);
		bool DestroyPipelineLayout (const TraceRange::Iterator &);
		bool CreateGraphicsPipelines (const TraceRange::Iterator &);
		bool CreateComputePipelines (const TraceRange::Iterator &);
		bool DestroyPipeline (const TraceRange::Iterator &);

		ND_ GraphicsPipelineInfo const*  FindGraphicsPipeline (ResourceID id) const;
		ND_ ComputePipelineInfo const*   FindComputePipeline (ResourceID id) const;
		ND_ PipelineLayoutInfo const*    FindPipelineLayout (ResourceID id) const;
		ND_ DescriptorSetLayout const*   FindDescriptorSetLayout (ResourceID id) const;

		ND_ RawGPipelineID	RemapGraphicsPipeline (ResourceID id) const;
		ND_ RawCPipelineID	RemapComputePipeline (ResourceID id) const;

		ND_ uint  GetShaderModuleCount () const				{ return _shaderCounter; }
		ND_ uint  GetGraphicsPipelineCount () const			{ return _graphicsPplnCounter; }
		ND_ uint  GetComputePipelineCount() const			{ return _computePplnCounter; }
		ND_ uint  GetMeshPipelineCount () const;
		ND_ uint  GetRayTracingPipelineCount () const;


	private:
		bool _ConvertGraphicsPipeline (OUT FG_GraphicsPipeline &, const VkGraphicsPipelineCreateInfo &);
		bool _GetShaderReflection (INOUT FG_GraphicsPipeline &, const VkGraphicsPipelineCreateInfo &);
		bool _ConvertVertexInput (const VkGraphicsPipelineCreateInfo &, OUT VertexInputState &) const;
		
		bool _ConvertComputePipeline (OUT FG_ComputePipeline &, const VkComputePipelineCreateInfo &);

		bool _GetShaderReflection (INOUT FG_ComputePipeline &, const VkComputePipelineCreateInfo &);
		bool _UpdateDynamicOffsetIndices (INOUT FG_PipelineLayout &) const;

		bool _PackShaderModule (const ShaderDataInfo &, INOUT TracePacker &) const;
		bool _PackGraphicsPipeline (const FG_GraphicsPipeline &, RawGPipelineID, INOUT TracePacker &) const;
		bool _PackComputePipeline (const FG_ComputePipeline &, RawCPipelineID, INOUT TracePacker &) const;
		bool _PackPipelineLayout (const FG_PipelineLayout &layout, INOUT TracePacker &) const;
	};

	

	inline FrameGraphConverter::PipelineConverter::GraphicsPipelineInfo const*
			FrameGraphConverter::PipelineConverter::FindGraphicsPipeline (ResourceID id) const
	{
		auto	iter = _graphicsPipelines.find( id );
		return iter != _graphicsPipelines.end() ? &iter->second : null;
	}
	
	inline FrameGraphConverter::PipelineConverter::ComputePipelineInfo const*
			FrameGraphConverter::PipelineConverter::FindComputePipeline (ResourceID id) const
	{
		auto	iter = _computePipelines.find( id );
		return iter != _computePipelines.end() ? &iter->second : null;
	}
		
	inline FrameGraphConverter::PipelineConverter::PipelineLayoutInfo const*
			FrameGraphConverter::PipelineConverter::FindPipelineLayout (ResourceID id) const
	{
		auto	iter = _pipelineLayouts.find( id );
		return iter != _pipelineLayouts.end() ? &iter->second : null;
	}
	
	inline FrameGraphConverter::PipelineConverter::DescriptorSetLayout const*
			FrameGraphConverter::PipelineConverter::FindDescriptorSetLayout (ResourceID id) const
	{
		auto	iter = _dsLayouts.find( id );
		return iter != _dsLayouts.end() ? &iter->second : null;
	}
	
	inline RawGPipelineID  FrameGraphConverter::PipelineConverter::RemapGraphicsPipeline (ResourceID id) const
	{
		auto	info = FindGraphicsPipeline( id );
		CHECK_ERR( info );
		return info->fgPipeline->second;
	}

	inline RawCPipelineID  FrameGraphConverter::PipelineConverter::RemapComputePipeline (ResourceID id) const
	{
		auto	info = FindComputePipeline( id );
		CHECK_ERR( info );
		return info->fgPipeline->second;
	}


}	// VTC
