// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/PipelineConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "framegraph/Shared/EnumUtils.h"

namespace VTC
{

/*
=================================================
	CalcPipelineLayoutHash
=================================================
*/
	ND_ static HashVal  CalcPipelineLayoutHash (const PipelineDescription::PipelineLayout &value)
	{
		HashVal	result;

		result << HashOf( value.descriptorSets.size() );

		for (auto& ds : value.descriptorSets)
		{
			ASSERT( ds.uniforms );
			result << HashOf( ds.id ) << HashOf( ds.bindingIndex ) << HashOf( ds.uniforms->size() );

			for (auto& un : *ds.uniforms)
			{
				result	<< HashOf( un.first ) << HashOf( un.second.index ) << HashOf( un.second.stageFlags )
						<< HashOf( un.second.data.index() );

				Visit( un.second.data,
						[&result] (const PipelineDescription::Texture &tex) {
							result << HashOf( tex.state ) << HashOf( tex.textureType );
						},
						[&result] (const PipelineDescription::SubpassInput &spi) {
							result << HashOf( spi.state ) << HashOf( spi.attachmentIndex ) << HashOf( spi.isMultisample );
						},
						[&result] (const PipelineDescription::Image &img) {
							result << HashOf( img.state ) << HashOf( img.imageType ) << HashOf( img.format );
						},
						[&result] (const PipelineDescription::UniformBuffer &ubuf) {
							result << HashOf( ubuf.state ) << HashOf( ubuf.size ) << HashOf( ubuf.dynamicOffsetIndex );
						},
						[&result] (const PipelineDescription::StorageBuffer &sbuf) {
							result	<< HashOf( sbuf.state ) << HashOf( sbuf.staticSize )
									<< HashOf( sbuf.dynamicOffsetIndex ) << HashOf( sbuf.arrayStride );
						},
						[&result] (const PipelineDescription::Sampler &) {},
						[&result] (const PipelineDescription::RayTracingScene &) {
							ASSERT(false);
						},
						[] (const std::monostate &) {
							ASSERT(false);
						}
					  );
			}
		}

		result << HashOf( value.pushConstants.size() );

		for (auto& pc : value.pushConstants)
		{
			result	<< HashOf( pc.first ) << HashOf( pc.second.stageFlags )
					<< HashOf( pc.second.offset ) << HashOf( pc.second.size );
		}
		return result;
	}

/*
=================================================
	ComparePipelineLayouts
=================================================
*/
	ND_ static bool  ComparePipelineLayouts (const PipelineDescription::PipelineLayout &lhs, const PipelineDescription::PipelineLayout &rhs)
	{
		if ( lhs.descriptorSets.size() != rhs.descriptorSets.size() or
			 lhs.pushConstants.size() != rhs.pushConstants.size() )
			return false;

		for (size_t i = 0; i < lhs.descriptorSets.size(); ++i)
		{
			auto&	lhs_ds	= lhs.descriptorSets[i];
			auto&	rhs_ds	= rhs.descriptorSets[i];

			if ( lhs_ds.bindingIndex		!= rhs_ds.bindingIndex	or
				 lhs_ds.uniforms			!= rhs_ds.uniforms		or
				 lhs_ds.uniforms->size()	!= rhs_ds.uniforms->size() )
				return false;

			for (auto lhs_un = lhs_ds.uniforms->begin(), rhs_un = rhs_ds.uniforms->begin();
				 lhs_un != lhs_ds.uniforms->end() and rhs_un != rhs_ds.uniforms->end();
				 ++lhs_un, ++rhs_un)
			{
				if ( lhs_un->first						!= rhs_un->first					or
					 lhs_un->second.index.VKBinding()	!= rhs_un->second.index.VKBinding()	or
					 lhs_un->second.stageFlags			!= rhs_un->second.stageFlags		or
					 lhs_un->second.data.index()		!= rhs_un->second.data.index() )
					return false;

				bool	eq = Visit( lhs_un->second.data,
						[rhs_un] (const PipelineDescription::Texture &lhs_tex)
						{
							auto&	rhs_tex = std::get<PipelineDescription::Texture>( rhs_un->second.data );
							return	lhs_tex.state		== rhs_tex.state	and
									lhs_tex.textureType	== rhs_tex.textureType;
						},

						[rhs_un] (const PipelineDescription::SubpassInput &lhs_spi)
						{
							auto&	rhs_spi = std::get<PipelineDescription::SubpassInput>( rhs_un->second.data );
							return	lhs_spi.state			== rhs_spi.state			and
									lhs_spi.attachmentIndex	== rhs_spi.attachmentIndex	and
									lhs_spi.isMultisample	== rhs_spi.isMultisample;
						},

						[rhs_un] (const PipelineDescription::Image &lhs_img)
						{
							auto&	rhs_img = std::get<PipelineDescription::Image>( rhs_un->second.data );
							return	lhs_img.state		== rhs_img.state		and
									lhs_img.imageType	== rhs_img.imageType	and
									lhs_img.format		== rhs_img.format;
						},

						[rhs_un] (const PipelineDescription::UniformBuffer &lhs_ubuf)
						{
							auto&	rhs_ubuf = std::get<PipelineDescription::UniformBuffer>( rhs_un->second.data );
							return	lhs_ubuf.state				== rhs_ubuf.state				and
									lhs_ubuf.dynamicOffsetIndex	== rhs_ubuf.dynamicOffsetIndex	and
									lhs_ubuf.size				== rhs_ubuf.size;
						},

						[rhs_un] (const PipelineDescription::StorageBuffer &lhs_sbuf)
						{
							auto&	rhs_sbuf = std::get<PipelineDescription::StorageBuffer>( rhs_un->second.data );
							return	lhs_sbuf.state				== rhs_sbuf.state				and
									lhs_sbuf.dynamicOffsetIndex	== rhs_sbuf.dynamicOffsetIndex	and
									lhs_sbuf.staticSize			== rhs_sbuf.staticSize			and
									lhs_sbuf.arrayStride		== rhs_sbuf.arrayStride;
						},

						[rhs_un] (const PipelineDescription::RayTracingScene &) {
							ASSERT(false);
							return false;	// TODO
						},

						[rhs_un] (const PipelineDescription::Sampler &) {
							return true;
						},

						[] (const std::monostate &) {
							return false;
						}
					  );

				if ( not eq )
					return false;
			}
		}
		return true;
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	ShaderStage::operator ==
=================================================
*/
	bool  FrameGraphConverter::PipelineConverter::ShaderStage::operator == (const ShaderStage &rhs) const
	{
		return	code			== rhs.code			and
				entry			== rhs.entry		and
				shaderType		== rhs.shaderType	and
				specConstants	== rhs.specConstants;
	}

/*
=================================================
	ShaderStageHash::operator ()
=================================================
*/
	ND_ HashVal  FrameGraphConverter::PipelineConverter::ShaderStageHash::operator () (const ShaderStage &stage) const noexcept
	{
		return HashVal{} << HashOf( stage.code ) << HashOf( stage.entry ) << HashOf( stage.shaderType ) << HashOf( stage.specConstants );
	}
//-----------------------------------------------------------------------------



/*
=================================================
	FG_GraphicsPipelineHash::operator ()
=================================================
*/
	size_t  FrameGraphConverter::PipelineConverter::FG_GraphicsPipelineHash::operator () (const FG_GraphicsPipeline &x) const noexcept
	{
		HashVal	result;
		result	<< HashOf( x.renderState );

		for (auto& stage : x.shaders) {
			result << ShaderStageHash{}( stage );
		}

		for (auto& frag : x.fragOutput) {
			result << HashOf( frag.id ) << HashOf( frag.index ) << HashOf( frag.type );
		}

		for (auto& attr : x.attribs) {
			result << HashOf( attr.id ) << HashOf( attr.index ) << HashOf( attr.type );
		}

		result	<< HashOf( x.supportedTopology )
				<< HashOf( x.patchControlPoints )
				<< HashOf( x.earlyFragmentTests );

		result << CalcPipelineLayoutHash( x.layout );

		return size_t(result);
	}
	
/*
=================================================
	FG_GraphicsPipeline::operator ==
=================================================
*/
	bool  FrameGraphConverter::PipelineConverter::FG_GraphicsPipeline::operator == (const FG_GraphicsPipeline &rhs) const
	{
		if ( this->renderState			!= rhs.renderState			or
			 this->supportedTopology	!= rhs.supportedTopology	or
			 this->patchControlPoints	!= rhs.patchControlPoints	or
			 this->earlyFragmentTests	!= rhs.earlyFragmentTests	or
			 this->shaders.size()		!= rhs.shaders.size()		or
			 this->fragOutput			!= rhs.fragOutput			or
			 this->attribs				!= rhs.attribs )
			return false;

		for (size_t i = 0; i < this->shaders.size(); ++i)
		{
			if ( not (this->shaders[i] == rhs.shaders[i]) )
				return false;
		}

		return ComparePipelineLayouts( this->layout, rhs.layout );
	}
//-----------------------------------------------------------------------------
	


/*
=================================================
	FG_ComputePipelineHash::operator ()
=================================================
*/
	size_t  FrameGraphConverter::PipelineConverter::FG_ComputePipelineHash::operator () (const FG_ComputePipeline &x) const noexcept
	{
		HashVal	result;
		
		result << ShaderStageHash{}( x.shader );
		result << CalcPipelineLayoutHash( x.layout );

		return size_t(result);
	}

/*
=================================================
	FG_ComputePipeline::operator ==
=================================================
*/
	bool  FrameGraphConverter::PipelineConverter::FG_ComputePipeline::operator == (const FG_ComputePipeline &rhs) const
	{
		if ( Any( this->localGroupSize	!= rhs.localGroupSize )	or
			 Any( this->localSizeSpec	!= rhs.localSizeSpec )	or
			 not (this->shader == rhs.shader) )
			return false;

		return ComparePipelineLayouts( this->layout, rhs.layout );
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	ConvertPipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::Convert (INOUT TracePacker &packer) const
	{
		for (auto& shader : _shaderDataCache) {
			CHECK_ERR( _PackShaderModule( shader.second, INOUT packer ));
		}

		for (auto& ppln : _gpipelineCache) {
			CHECK_ERR( _PackGraphicsPipeline( ppln.first, ppln.second, INOUT packer ));
		}

		for (auto& ppln : _cpipelineCache) {
			CHECK_ERR( _PackComputePipeline( ppln.first, ppln.second, INOUT packer ));
		}

		return true;
	}
	
/*
=================================================
	_PackShaderModule
----
	see unpacker in 'FGPlayer_v100::_CreateShaderModule'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackShaderModule (const ShaderDataInfo &info, INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateShaderModule );
		
		packer << info.uid;
		packer << info.dataId;

		packer.End( EPacketID::FgCreateShaderModule );
		return true;
	}
	
/*
=================================================
	_PackPipelineLayout
----
	see unpacker in 'FGPlayer_v100::_UnpackPipelineLayout'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackPipelineLayout (const FG_PipelineLayout &layout, INOUT TracePacker &packer) const
	{
		packer << uint(layout.descriptorSets.size());

		for (auto& ds : layout.descriptorSets)
		{
			ASSERT( ds.id.IsDefined() );
			ASSERT( ds.bindingIndex < FG_MaxDescriptorSets );

			packer << ds.id;
			packer << ds.bindingIndex;
			packer << uint(ds.uniforms->size());

			for (auto& un : *ds.uniforms)
			{
				ASSERT( un.first.IsDefined() );

				packer << un.first;
				packer << un.second.index.VKBinding();
				packer << un.second.stageFlags;
				packer << uint(un.second.data.index());

				Visit( un.second.data,
						[&packer] (const PipelineDescription::Texture &tex)
						{
							packer << tex.state;
							packer << tex.textureType;
						},
						[] (const PipelineDescription::Sampler &)
						{
						},
						[&packer] (const PipelineDescription::SubpassInput &spi)
						{
							packer << spi.state;
							packer << spi.attachmentIndex;
							packer << spi.isMultisample;
						},
						[&packer] (const PipelineDescription::Image &img)
						{
							packer << img.state;
							packer << img.imageType;
							packer << img.format;
						},
						[&packer] (const PipelineDescription::UniformBuffer &ubuf)
						{
							packer << ubuf.state;
							packer << ubuf.dynamicOffsetIndex;
							packer << uint64_t(ubuf.size);
						},
						[&packer] (const PipelineDescription::StorageBuffer &sbuf)
						{
							packer << sbuf.state;
							packer << sbuf.dynamicOffsetIndex;
							packer << uint64_t(sbuf.staticSize);
							packer << uint64_t(sbuf.arrayStride);
						},
						[&packer] (const PipelineDescription::RayTracingScene &)
						{
							ASSERT(false);
						},
						[] (const std::monostate &) { ASSERT(false); }
					);
			}
		}

		packer << uint(layout.pushConstants.size());

		for (auto& pc : layout.pushConstants)
		{
			packer << pc.first;
			packer << pc.second.stageFlags;
			packer << uint16_t(pc.second.offset);
			packer << uint16_t(pc.second.size);
		}

		return true;
	}

/*
=================================================
	_PackGraphicsPipeline
----
	see unpacker in 'FGPlayer_v100::_CreateGraphicsPipeline'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackGraphicsPipeline (const FG_GraphicsPipeline &ppln, RawGPipelineID id, INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateGraphicsPipeline );

		packer << uint(0);	// TODO: thread id
		packer << id.Index();

		packer << uint(ppln.shaders.size());
		for (auto& shader : ppln.shaders)
		{
			packer << shader.code->second.uid;
			packer << shader.shaderType;
		}

		packer << uint(ppln.fragOutput.size());
		for (auto& frag : ppln.fragOutput)
		{
			packer << frag.id;
			packer << frag.index;
			packer << frag.type;
		}

		packer << uint(ppln.attribs.size());
		for (auto& attr : ppln.attribs)
		{
			packer << attr.id;
			packer << attr.index;
			packer << attr.type;
		}

		packer << uint(ppln.supportedTopology.to_ulong());
		packer << ppln.patchControlPoints;
		packer << ppln.earlyFragmentTests;

		CHECK_ERR( _PackPipelineLayout( ppln.layout, packer ));

		packer.End( EPacketID::FgCreateGraphicsPipeline );
		return true;
	}
	
/*
=================================================
	_PackComputePipeline
----
	see unpacker in 'FGPlayer_v100::_CreateComputePipeline'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackComputePipeline (const FG_ComputePipeline &ppln, RawCPipelineID id, INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateComputePipeline );
		
		packer << uint(0);	// TODO: thread id
		packer << id.Index();
		packer << ppln.shader.code->second.uid;

		packer << ppln.localGroupSize.x;
		packer << ppln.localGroupSize.y;
		packer << ppln.localGroupSize.z;

		packer << ppln.localSizeSpec.x;
		packer << ppln.localSizeSpec.y;
		packer << ppln.localSizeSpec.z;
		
		CHECK_ERR( _PackPipelineLayout( ppln.layout, packer ));

		packer.End( EPacketID::FgCreateComputePipeline );
		return true;
	}

/*
=================================================
	CreateShaderModule
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateShaderModule (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkCreateShaderModule>();
		Array<uint>		data	{ packet.pCreateInfo->pCode, packet.pCreateInfo->pCode + (packet.pCreateInfo->codeSize / sizeof(uint)) };

		auto	data_iter = _shaderDataCache.find( data );
		
		if ( data_iter == _shaderDataCache.end() )
		{
			DataID		data_id = _fgConv._RequestData( pos, packet.header, packet.pCreateInfo->pCode, packet.pCreateInfo->codeSize, FrameID(0) );
			CHECK_ERR( data_id != UMax );

			ShaderDataInfo		info;
			info.dataId		= data_id;
			info.uid		= _shaderCounter++;
			info.dataSize	= uint(data.size());

			data_iter = _shaderDataCache.insert_or_assign( std::move(data), std::move(info) ).first;
		}

		_shaderMap.insert_or_assign( ResourceID(*packet.pShaderModule), data_iter.operator->() );
		return true;
	}

/*
=================================================
	DestroyShaderModule
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyShaderModule (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkDestroyShaderModule>();

		CHECK( _shaderMap.erase( ResourceID(packet.shaderModule) ) == 1 );
		return true;
	}
	
/*
=================================================
	CreateDescriptorSetLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateDescriptorSetLayout (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkCreateDescriptorSetLayout>();
		auto			iter	= _dsLayouts.insert({ ResourceID(*packet.pSetLayout), {} }).first;
		auto&			desc	= iter->second.descriptors;

		ASSERT( packet.pCreateInfo->pNext == null );

		for (uint i = 0; i < packet.pCreateInfo->bindingCount; ++i)
		{
			auto&	src = packet.pCreateInfo->pBindings[i];
			
			desc.resize( Max( desc.size(), src.binding + src.descriptorCount ));

			// TODO: check
			ASSERT( src.descriptorCount == 1 );

			for (uint j = 0; j < src.descriptorCount; ++j)
			{
				auto&	dst = desc[ src.binding + j ];

				ASSERT( dst.descriptorType == VK_DESCRIPTOR_TYPE_MAX_ENUM or
						dst.descriptorType == src.descriptorType );

				dst.descriptorType	 = src.descriptorType;
				dst.stageFlags		|= src.stageFlags;
			}
		}
		return true;
	}
	
/*
=================================================
	DestroyDescriptorSetLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyDescriptorSetLayout (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkDestroyDescriptorSetLayout>();

		CHECK( _dsLayouts.erase( ResourceID(packet.descriptorSetLayout) ) == 1 );
		return true;
	}
	
/*
=================================================
	CreatePipelineLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreatePipelineLayout (const TraceRange::Iterator &pos)
	{
		auto const&			packet	= pos.Cast<packet_vkCreatePipelineLayout>();
		PipelineLayoutInfo	info;

		info.dslayouts.resize( packet.pCreateInfo->setLayoutCount );

		for (uint i = 0; i < packet.pCreateInfo->setLayoutCount; ++i)
		{
			info.dslayouts[i] = ResourceID(packet.pCreateInfo->pSetLayouts[i]);
		}

		for (uint i = 0; i < packet.pCreateInfo->pushConstantRangeCount; ++i)
		{
			info.pushConstantRanges.insert({ PushConstantID{"pc"s << ToString(i)}, packet.pCreateInfo->pPushConstantRanges[i] });
		}

		_pipelineLayouts.insert_or_assign( ResourceID(*packet.pPipelineLayout), info );
		return true;
	}
	
/*
=================================================
	DestroyPipelineLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyPipelineLayout (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkDestroyPipelineLayout>();

		CHECK( _pipelineLayouts.erase( ResourceID(packet.pipelineLayout) ) == 1 );
		return true;
	}
	
/*
=================================================
	CreateGraphicsPipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateGraphicsPipelines (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkCreateGraphicsPipelines>();

		for (uint i = 0; i < packet.createInfoCount; ++i)
		{
			ASSERT( packet.pCreateInfos[i].pNext == null );

			const auto&		src  = packet.pCreateInfos[i];
			auto&			dst  = _graphicsPipelines.insert_or_assign( ResourceID(packet.pPipelines[i]), GraphicsPipelineInfo{} ).first->second;

			if ( src.pViewportState )
			{
				dst.viewports.resize( src.pViewportState->viewportCount );
				dst.scissors.resize( src.pViewportState->scissorCount );

				for (uint j = 0; src.pViewportState->pViewports and j < src.pViewportState->viewportCount; ++j) {
					dst.viewports[j] = src.pViewportState->pViewports[j];
				}

				for (uint j = 0; src.pViewportState->pScissors and j < src.pViewportState->scissorCount; ++j) {
					dst.scissors[j] = src.pViewportState->pScissors[j];
				}
			}

			if ( src.pDynamicState )
			{
				ASSERT( src.pDynamicState->pNext == null );
				for (uint j = 0; j < src.pDynamicState->dynamicStateCount; ++j) {
					dst.dynamicStates.insert( src.pDynamicState->pDynamicStates[j] );
				}
			}
			
			FG_GraphicsPipeline		info;
			CHECK_ERR( _ConvertGraphicsPipeline( OUT info, src ));

			auto[iter, inserted] = _gpipelineCache.insert({ info, RawGPipelineID{} });
			if ( inserted )
				iter->second = RawGPipelineID{ _graphicsPplnCounter++, 0 };

			dst.fgPipeline	= iter.operator->();
			dst.layout		= ResourceID(src.layout);

			if ( src.pInputAssemblyState )
			{
				dst.topology		= FGEnumCast( src.pInputAssemblyState->topology );
				dst.primitiveRestart= src.pInputAssemblyState->primitiveRestartEnable;
			}

			CHECK_ERR( _ConvertVertexInput( src, OUT dst.vertexInput ));
		}
		return true;
	}
	
/*
=================================================
	CreateComputePipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_ConvertGraphicsPipeline (OUT FG_GraphicsPipeline &result, const VkGraphicsPipelineCreateInfo &info)
	{
		if ( info.pVertexInputState )
		{
			for (uint i = 0; i < info.pVertexInputState->vertexAttributeDescriptionCount; ++i)
			{
				auto&							src = info.pVertexInputState->pVertexAttributeDescriptions[i];
				VertexInputState::VertexAttrib	dst;

				dst.id		= VertexID( "attr"s << ToString(src.location) );
				dst.index	= src.location;
				dst.type	= FGEnumCastAttrib( src.format );

				result.attribs.push_back( dst );
			}
		}

		if ( info.pInputAssemblyState )
		{
			result.renderState.inputAssembly.topology			= FGEnumCast( info.pInputAssemblyState->topology );
			result.renderState.inputAssembly.primitiveRestart	= info.pInputAssemblyState->primitiveRestartEnable;
		}

		if ( info.pTessellationState )
		{
			result.patchControlPoints	= info.pTessellationState->patchControlPoints;
		}

		if ( info.pColorBlendState )
		{
			auto&	cs = *info.pColorBlendState;

			for (uint i = 0; i < cs.attachmentCount; ++i)
			{
				RenderTargetID							id{ "rt"s << ToString(i) };
				RenderState::ColorBuffer				cb;
				GraphicsPipelineDesc::FragmentOutput	frag;

				frag.id		= id;
				frag.index	= i;
				frag.type	= EFragOutput::Float4;	// TODO

				cb.blend	= cs.pAttachments[i].blendEnable;

				if ( cb.blend )
				{
					cb.blendOp.color		= FGEnumCast( cs.pAttachments[i].colorBlendOp );
					cb.blendOp.alpha		= FGEnumCast( cs.pAttachments[i].alphaBlendOp );
					cb.colorMask.x			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_R_BIT );
					cb.colorMask.y			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_G_BIT );
					cb.colorMask.z			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_B_BIT );
					cb.colorMask.w			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_A_BIT );
					cb.srcBlendFactor.color	= FGEnumCast( cs.pAttachments[i].srcColorBlendFactor );
					cb.srcBlendFactor.alpha	= FGEnumCast( cs.pAttachments[i].srcAlphaBlendFactor );
					cb.dstBlendFactor.color	= FGEnumCast( cs.pAttachments[i].dstColorBlendFactor );
					cb.dstBlendFactor.alpha	= FGEnumCast( cs.pAttachments[i].dstAlphaBlendFactor );
				}

				result.renderState.color.buffers.insert_or_assign( id, cb );
				result.fragOutput.push_back( frag );
			}

			if ( cs.logicOpEnable )
				result.renderState.color.logicOp = FGEnumCast( cs.logicOp );

			result.renderState.color.blendColor = { cs.blendConstants[0], cs.blendConstants[1], cs.blendConstants[2], cs.blendConstants[3] };
		}

		if ( info.pViewportState )
		{
		}

		if ( info.pRasterizationState )
		{
			result.renderState.rasterization.polygonMode			= FGEnumCast( info.pRasterizationState->polygonMode );
			result.renderState.rasterization.lineWidth				= info.pRasterizationState->lineWidth;
			result.renderState.rasterization.depthBiasConstFactor	= info.pRasterizationState->depthBiasConstantFactor;
			result.renderState.rasterization.depthBiasClamp			= info.pRasterizationState->depthBiasClamp;
			result.renderState.rasterization.depthBiasSlopeFactor	= info.pRasterizationState->depthBiasSlopeFactor;
			result.renderState.rasterization.depthBias				= info.pRasterizationState->depthBiasEnable;
			result.renderState.rasterization.depthClamp				= info.pRasterizationState->depthClampEnable;
			result.renderState.rasterization.rasterizerDiscard		= info.pRasterizationState->rasterizerDiscardEnable;
			result.renderState.rasterization.frontFaceCCW			= (info.pRasterizationState->frontFace == VK_FRONT_FACE_COUNTER_CLOCKWISE);
			result.renderState.rasterization.cullMode				= FGEnumCast( info.pRasterizationState->cullMode );
		}

		if ( info.pMultisampleState )
		{
			result.renderState.multisample.samples				= MultiSamples{ uint(info.pMultisampleState->rasterizationSamples) };
			result.renderState.multisample.minSampleShading		= info.pMultisampleState->minSampleShading;
			result.renderState.multisample.sampleShading		= info.pMultisampleState->sampleShadingEnable;
			result.renderState.multisample.alphaToCoverage		= info.pMultisampleState->alphaToCoverageEnable;
			result.renderState.multisample.alphaToOne			= info.pMultisampleState->alphaToOneEnable;
		
			for (uint i = 0, count = (info.pMultisampleState->rasterizationSamples + 31) / 32;
				 info.pMultisampleState->pSampleMask and i < count; ++i)
			{
				result.renderState.multisample.sampleMask[i] = info.pMultisampleState->pSampleMask[i];
			}
		}

		if ( info.pDepthStencilState )
		{
			result.renderState.depth.test			= info.pDepthStencilState->depthTestEnable;
			result.renderState.depth.write			= info.pDepthStencilState->depthWriteEnable;
			result.renderState.depth.boundsEnabled	= info.pDepthStencilState->depthBoundsTestEnable;
			result.renderState.stencil.enabled		= info.pDepthStencilState->stencilTestEnable;

			if ( info.pDepthStencilState->depthTestEnable )
				result.renderState.depth.compareOp = FGEnumCast( info.pDepthStencilState->depthCompareOp );

			if ( info.pDepthStencilState->depthBoundsTestEnable ) {
				result.renderState.depth.bounds.x = info.pDepthStencilState->minDepthBounds;
				result.renderState.depth.bounds.y = info.pDepthStencilState->maxDepthBounds;
			}

			if ( info.pDepthStencilState->stencilTestEnable )
			{
				result.renderState.stencil.front.failOp			= FGEnumCast( info.pDepthStencilState->front.failOp );
				result.renderState.stencil.front.depthFailOp	= FGEnumCast( info.pDepthStencilState->front.depthFailOp );
				result.renderState.stencil.front.passOp			= FGEnumCast( info.pDepthStencilState->front.passOp );
				result.renderState.stencil.front.compareOp		= FGEnumCast( info.pDepthStencilState->front.compareOp );
				result.renderState.stencil.front.compareMask	= info.pDepthStencilState->front.compareMask;
				result.renderState.stencil.front.writeMask		= info.pDepthStencilState->front.writeMask;
				result.renderState.stencil.front.reference		= info.pDepthStencilState->front.reference;
				
				result.renderState.stencil.back.failOp			= FGEnumCast( info.pDepthStencilState->back.failOp );
				result.renderState.stencil.back.depthFailOp		= FGEnumCast( info.pDepthStencilState->back.depthFailOp );
				result.renderState.stencil.back.passOp			= FGEnumCast( info.pDepthStencilState->back.passOp );
				result.renderState.stencil.back.compareOp		= FGEnumCast( info.pDepthStencilState->back.compareOp );
				result.renderState.stencil.back.compareMask		= info.pDepthStencilState->back.compareMask;
				result.renderState.stencil.back.writeMask		= info.pDepthStencilState->back.writeMask;
				result.renderState.stencil.back.reference		= info.pDepthStencilState->back.reference;
			}
		}
		
		if ( info.stageCount and info.pStages )
		{
			for (uint i = 0; i < info.stageCount; ++i)
			{
				auto&			src = info.pStages[i];
				ShaderStage		dst;
				ASSERT( src.pNext == null );

				auto	sh_iter = _shaderMap.find( ResourceID(src.module) );
				CHECK_ERR( sh_iter != _shaderMap.end() );

				dst.code		= sh_iter->second;
				dst.entry		= src.pName;
				dst.shaderType	= FGEnumCast( src.stage );

				ASSERT( src.pSpecializationInfo == null );

				result.shaders.push_back( std::move(dst) );
			}

			CHECK_ERR( _GetShaderReflection( INOUT result, info ));
		}

		result.supportedTopology[ uint(result.renderState.inputAssembly.topology) ] = true;
		return true;
	}
	
/*
=================================================
	_ConvertVertexInput
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_ConvertVertexInput (const VkGraphicsPipelineCreateInfo &info, OUT VertexInputState &vertexInput) const
	{
		if ( not info.pVertexInputState )
			return true;

		for (uint i = 0; i < info.pVertexInputState->vertexBindingDescriptionCount; ++i)
		{
			auto&	bind = info.pVertexInputState->pVertexBindingDescriptions[i];

			vertexInput.Bind( VertexBufferID{"vb"s << ToString(bind.binding)}, BytesU{bind.stride}, bind.binding, FGEnumCast(bind.inputRate) );
		}

		for (uint i = 0; i < info.pVertexInputState->vertexAttributeDescriptionCount; ++i)
		{
			auto&	vert = info.pVertexInputState->pVertexAttributeDescriptions[i];

			vertexInput.Add( VertexID{"attr"s << ToString(vert.location)}, FGEnumCastVertex(vert.format), BytesU{vert.offset},
							 VertexBufferID{"vb"s << ToString(vert.binding)} );
		}

		return true;
	}

/*
=================================================
	CreateComputePipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateComputePipelines (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCreateComputePipelines>();
		
		for (uint i = 0; i < packet.createInfoCount; ++i)
		{
			ASSERT( packet.pCreateInfos[i].pNext == null );

			auto&	src	= packet.pCreateInfos[i];
			auto&	dst	= _computePipelines.insert_or_assign( ResourceID(packet.pPipelines[i]), ComputePipelineInfo{} ).first->second;

			FG_ComputePipeline	pipeline;
			CHECK_ERR( _ConvertComputePipeline( OUT pipeline, src ));
			
			auto[iter, inserted] = _cpipelineCache.insert({ pipeline, RawCPipelineID{} });
			if ( inserted )
				iter->second = RawCPipelineID{ _computePplnCounter++, 0 };
			
			dst.fgPipeline	= iter.operator->();
			dst.layout		= ResourceID(src.layout);
		}

		return true;
	}
	
/*
=================================================
	_ConvertComputePipeline
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_ConvertComputePipeline (OUT FG_ComputePipeline &result, const VkComputePipelineCreateInfo &info)
	{
		auto&			src = info.stage;
		ShaderStage&	dst = result.shader;
		ASSERT( src.pNext == null );

		auto	sh_iter = _shaderMap.find( ResourceID(src.module) );
		CHECK_ERR( sh_iter != _shaderMap.end() );

		dst.code		= sh_iter->second;
		dst.entry		= src.pName;
		dst.shaderType	= FGEnumCast( src.stage );

		ASSERT( src.pSpecializationInfo == null );
		
		CHECK_ERR( _GetShaderReflection( INOUT result, info ));
		return true;
	}

/*
=================================================
	DestroyPipeline
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyPipeline (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkDestroyPipeline>();

		CHECK( _graphicsPipelines.erase(ResourceID(packet.pipeline)) + _computePipelines.erase(ResourceID(packet.pipeline)) == 1 );
		return true;
	}
	
/*
=================================================
	_UpdateDynamicOffsetIndices
=================================================
*/	
	bool FrameGraphConverter::PipelineConverter::_UpdateDynamicOffsetIndices (INOUT FG_PipelineLayout &layout) const
	{
		Array< PipelineDescription::Uniform *>	sorted;

		for (auto& ds_layout : layout.descriptorSets)
		{
			for (auto& un : *ds_layout.uniforms)
			{
				if ( auto* ubuf = std::get_if< PipelineDescription::UniformBuffer >( &un.second.data ); ubuf and ubuf->dynamicOffsetIndex != UMax )
					sorted.push_back( const_cast< PipelineDescription::Uniform *>( &un.second ));
				else
				if ( auto* sbuf = std::get_if< PipelineDescription::StorageBuffer >( &un.second.data ); sbuf and sbuf->dynamicOffsetIndex != UMax )
					sorted.push_back( const_cast< PipelineDescription::Uniform *>( &un.second ));
			}
		}

		std::sort( sorted.begin(), sorted.end(), [] (auto& lhs, auto& rhs) { return lhs->index.VKBinding() < rhs->index.VKBinding(); });

		uint	dbo_index = 0;

		for (auto* un : sorted)
		{
			if ( auto* ubuf = std::get_if< PipelineDescription::UniformBuffer >( &un->data ))
				ubuf->dynamicOffsetIndex = dbo_index++;
			else
			if ( auto* sbuf = std::get_if< PipelineDescription::StorageBuffer >( &un->data ))
				sbuf->dynamicOffsetIndex = dbo_index++;
		}

		CHECK( dbo_index <= FG_MaxBufferDynamicOffsets );
		return true;
	}
//-----------------------------------------------------------------------------

	
/*
=================================================
	IsCompatiblePushConstants
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::PipelineLayoutInfo::IsCompatiblePushConstants (const PipelineLayoutInfo &other) const
	{
		if ( pushConstantRanges.size() != other.pushConstantRanges.size() )
			return false;

		for (auto& lhs : pushConstantRanges)
		{
			auto	rhs = other.pushConstantRanges.find( lhs.first );

			if ( rhs					== other.pushConstantRanges.end()	or
				 lhs.second.offset		!= rhs->second.offset				or
				 lhs.second.size		!= rhs->second.size					or
				 lhs.second.stageFlags	!= rhs->second.stageFlags )
				return false;
		}
		return true;
	}


}	// VTC

#ifdef VTC_ENABLE_SPIRVREFLECT
#	include "spirv_reflect.c"
#endif
