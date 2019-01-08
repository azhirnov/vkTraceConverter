// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#ifdef VTC_ENABLE_SPIRVCROSS

# ifdef VTC_ENABLE_SPIRVREFLECT
#	error spirv-cross and spirv-reflect are not compatible, select one of it
# endif

#include "Converters/FrameGraph/PipelineConverter.h"
#include "extensions/pipeline_compiler/VPipelineCompiler.h"
#include "Converters/FrameGraph/FGEnumCast.h"

#include "spirv_cross/spirv_glsl.hpp"

namespace VTC
{
	
/*
=================================================
	ConvertToGLSL
=================================================
*/
	ND_ static String  ConvertToGLSL (const Array<uint> &spv)
	{
		spirv_cross::CompilerGLSL			compiler{ spv.data(), spv.size() };
		spirv_cross::CompilerGLSL::Options	opt;

		opt.version						= 460;
		opt.es							= false;
		opt.vulkan_semantics			= true;
		opt.separate_shader_objects		= true;
		opt.enable_420pack_extension	= true;

		opt.vertex.fixup_clipspace					= false;
		opt.vertex.flip_vert_y						= false;
		opt.vertex.support_nonzero_base_instance	= false;

		opt.fragment.default_float_precision	= spirv_cross::CompilerGLSL::Options::Precision::Highp;
		opt.fragment.default_int_precision		= spirv_cross::CompilerGLSL::Options::Precision::Highp;

		compiler.set_common_options( opt );

		return compiler.compile();
	}
	
/*
=================================================
	ValidatePipelineLayout
=================================================
*/
	template <typename PplnType>
	static bool  ValidatePushConstants (const FrameGraphConverter::PipelineConverter::PipelineLayoutInfo &pplnLayout,
										const PipelineDescription::PipelineLayout &pplnLayoutDesc,
										INOUT PplnType &pipeline)
	{
		uint	pc_index = 0;
		for (auto& pc1 : pplnLayout.pushConstantRanges)
		{
			PipelineDescription::PushConstant const*	pc2		= null;
			EShaderStages								stages	= FGEnumCastStages( pc1.second.stageFlags );

			for (auto& pc : pplnLayoutDesc.pushConstants) {
				if ( uint(pc.second.offset)	== pc1.second.offset	and
					 uint(pc.second.size)	== pc1.second.size		and
					 pc.second.stageFlags	== stages )
				{
					pc2 = &pc.second;
					break;
				}
			}
			CHECK_ERR( pc2 );

			pipeline.layout.pushConstants.insert({ PushConstantID("pc" + ToString(pc_index)), *pc2 });
			++pc_index;
		}

		return true;
	}
	
/*
=================================================
	ValidatePipelineLayout
=================================================
*/
	template <typename PplnType>
	static bool  ValidatePipelineLayout (const FrameGraphConverter::PipelineConverter &pipelineConverter,
										 const FrameGraphConverter::PipelineConverter::PipelineLayoutInfo &pplnLayout,
										 const PipelineDescription::PipelineLayout &pplnLayoutDesc,
										 INOUT PplnType &pipeline)
	{
		CHECK_ERR( pplnLayout.dslayouts.size() >= pplnLayoutDesc.descriptorSets.size() );
		CHECK_ERR( pplnLayout.pushConstantRanges.size() == pplnLayoutDesc.pushConstants.size() );

		const size_t	un_count = Min( pplnLayout.dslayouts.size(), pplnLayoutDesc.descriptorSets.size() );

		for (size_t i = 0; i < un_count; ++i)
		{
			auto*	ds_layout = pipelineConverter.FindDescriptorSetLayout( pplnLayout.dslayouts[i] );
			CHECK_ERR( ds_layout );

			auto&	ds = pplnLayoutDesc.descriptorSets[i];
			CHECK_ERR( ds.bindingIndex == i );
			
			PipelineDescription::UniformMap_t	dst_uniforms;

			for (size_t j = 0; j < ds_layout->descriptors.size(); ++j)
			{
				const auto&							un1 = ds_layout->descriptors[j];
				const PipelineDescription::Uniform*	un2 = null;

				for (auto& un : *ds.uniforms) {
					if ( un.second.index.VKBinding() == j ) {
						un2 = &un.second;
						break;
					}
				}

				if ( not un2 )
					continue;

				ENABLE_ENUM_CHECKS();
				switch ( un1.descriptorType )
				{
					case VK_DESCRIPTOR_TYPE_SAMPLER :
						CHECK_ERR( std::holds_alternative<PipelineDescription::Sampler>( un2->data ));
						dst_uniforms.insert_or_assign( UniformID{"un" + ToString(j)}, *un2 );
						break;

					case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER :
						CHECK_ERR( std::holds_alternative<PipelineDescription::Texture>( un2->data ));
						dst_uniforms.insert_or_assign( UniformID{"un" + ToString(j)}, *un2 );
						break;
						
					case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE :
						CHECK_ERR( std::holds_alternative<PipelineDescription::Image>( un2->data ));
						dst_uniforms.insert_or_assign( UniformID{"un" + ToString(j)}, *un2 );
						break;

					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC :
						CHECK_ERR( std::holds_alternative<PipelineDescription::UniformBuffer>( un2->data ));
						dst_uniforms.insert_or_assign( UniformID{"un" + ToString(j)}, *un2 );
						break;

					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC :
						CHECK_ERR( std::holds_alternative<PipelineDescription::StorageBuffer>( un2->data ));
						dst_uniforms.insert_or_assign( UniformID{"un" + ToString(j)}, *un2 );
						break;

					case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT :
						CHECK_ERR( std::holds_alternative<PipelineDescription::SubpassInput>( un2->data ));
						dst_uniforms.insert_or_assign( UniformID{"un" + ToString(j)}, *un2 );
						break;

					case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER :
					case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER :
					case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE :
					case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT :
					case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV :
					case VK_DESCRIPTOR_TYPE_RANGE_SIZE :
					case VK_DESCRIPTOR_TYPE_MAX_ENUM :
						RETURN_ERR( "not supported" );
				}
				DISABLE_ENUM_CHECKS();
			}
			
			if ( dst_uniforms.empty() )
				continue;

			pipeline.layout.descriptorSets.push_back({ DescriptorSetID{"ds" + ToString(i)}, uint(i),
									MakeShared<PipelineDescription::UniformMap_t>(std::move(dst_uniforms)) });
		}

		CHECK_ERR( ValidatePushConstants( pplnLayout, pplnLayoutDesc, INOUT pipeline ));
		return true;
	}

/*
=================================================
	_GetShaderReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetShaderReflection (INOUT FG_GraphicsPipeline &pipeline, const VkGraphicsPipelineCreateInfo &info)
	{
		CHECK_ERR( info.stageCount and info.pStages );

		GraphicsPipelineDesc	desc;

		for (uint i = 0; i < info.stageCount; ++i)
		{
			auto&	src = info.pStages[i];
			ASSERT( src.pNext == null );

			auto	sh_iter = _shaderMap.find( ResourceID(src.module) );
			CHECK_ERR( sh_iter != _shaderMap.end() );

			auto&	spv_data	= sh_iter->second->first;
			String	source		= ConvertToGLSL( spv_data );

			desc.AddShader( FGEnumCast( src.stage ), EShaderLangFormat::VKSL_110, "main", std::move(source) );
		}

		if ( not _pplnCompiler )
		{
			auto	comp = MakeShared<VPipelineCompiler>();
			comp->SetCompilationFlags( (_fgConv._config.forceDBO ? EShaderCompilationFlags::AlwaysBufferDynamicOffset : Default) |
									   EShaderCompilationFlags::Optimize );

			_pplnCompiler = comp;
		}

		CHECK_ERR( _pplnCompiler->Compile( INOUT desc, EShaderLangFormat::SPIRV_110 ));


		// validate
		auto*	ppln_layout = FindPipelineLayout( ResourceID(info.layout) );
		CHECK_ERR( ppln_layout );

		CHECK_ERR( pipeline.patchControlPoints == desc._patchControlPoints );
		CHECK_ERR( ValidatePipelineLayout( *this, *ppln_layout, desc._pipelineLayout, INOUT pipeline ));

		return true;
	}
	
/*
=================================================
	_GetShaderReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetShaderReflection (INOUT FG_ComputePipeline &pipeline, const VkComputePipelineCreateInfo &info)
	{
		ComputePipelineDesc		desc;
		
		auto	sh_iter = _shaderMap.find( ResourceID(info.stage.module) );
		CHECK_ERR( sh_iter != _shaderMap.end() );

		desc.AddShader( EShaderLangFormat::VKSL_110, "main", ConvertToGLSL( sh_iter->second->first ) );
		
		if ( not _pplnCompiler )
		{
			auto	comp = MakeShared<VPipelineCompiler>();
			comp->SetCompilationFlags( EShaderCompilationFlags::GenerateDebugInfo );

			_pplnCompiler = comp;
		}

		CHECK_ERR( _pplnCompiler->Compile( INOUT desc, EShaderLangFormat::SPIRV_110 ));

		pipeline.localGroupSize	= desc._defaultLocalGroupSize;
		pipeline.localSizeSpec	= desc._localSizeSpec;
		

		// validate
		auto*	ppln_layout = FindPipelineLayout( ResourceID(info.layout) );
		CHECK_ERR( ppln_layout );

		CHECK_ERR( ValidatePipelineLayout( *this, *ppln_layout, desc._pipelineLayout, INOUT pipeline ));
		return true;
	}


}	// VTC

#endif	// VTC_ENABLE_SPIRVCROSS
