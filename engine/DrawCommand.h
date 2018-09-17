// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "engine/ResourceIDs.h"

namespace VTC
{

	
	//
	// Draw Command
	//

	class DrawCommand
	{
	// types
	public:
		struct IndexBuffer
		{
			BufferID		buffer;
			VkDeviceSize 	offset;
			VkIndexType 	indexType;
		};
	
		struct Draw
		{
			uint32_t 		vertexCount;
			uint32_t 		instanceCount;
			uint32_t 		firstVertex;
			uint32_t 		firstInstance;
		};
		
		struct DrawIndexed
		{
			IndexBuffer		indexBuffer;
			uint32_t 		indexCount;
			uint32_t 		instanceCount;
			uint32_t 		firstIndex;
			int32_t 		vertexOffset;
			uint32_t 		firstInstance;
		};
		
		struct DrawIndirect
		{
			BufferID 		buffer;
			VkDeviceSize	offset;
			uint32_t 		drawCount;
			uint32_t 		stride;
		};
		
		struct DrawIndexedIndirect
		{
			IndexBuffer		indexBuffer;
			BufferID 		buffer;
			VkDeviceSize	offset;
			uint32_t 		drawCount;
			uint32_t 		stride;
		};
		
		struct DrawIndirectCount
		{
			BufferID 		buffer;
			VkDeviceSize	offset;
			BufferID 		countBuffer;
			VkDeviceSize	countBufferOffset;
			uint32_t 		maxDrawCount;
			uint32_t 		stride;
		};
		
		struct DrawIndexedIndirectCount
		{
			IndexBuffer		indexBuffer;
			BufferID 		buffer;
			VkDeviceSize	offset;
			BufferID 		countBuffer;
			VkDeviceSize	countBufferOffset;
			uint32_t 		maxDrawCount;
			uint32_t 		stride;
		};
		
		struct Command
		{
			enum class EMode {
				Unknown,
				Draw,
				DrawIndexed,
				DrawIndirect,
				DrawIndexedIndirect,
				DrawIndirectCount,
				DrawIndexedIndirectCount,
			};
			
			union {
				Draw						draw;
				DrawIndexed					drawIndexed;
				DrawIndirect				drawIndirect;
				DrawIndexedIndirect			drawIndexedIndirect;
				DrawIndirectCount			drawIndirectCount;
				DrawIndexedIndirectCount	drawIndexedIndirectCount;
			};
			EMode		mode;
			
			Command () : mode{EMode::Unknown} {}
			Command (const Draw &value) : draw{value}, mode{EMode::Draw} {}
			Command (const DrawIndexed &value) : drawIndexed{value}, mode{EMode::DrawIndexed} {}
			Command (const DrawIndirect &value) : drawIndirect{value}, mode{EMode::DrawIndirect} {}
			Command (const DrawIndexedIndirect &value) : drawIndexedIndirect{value}, mode{EMode::DrawIndexedIndirect} {}
			Command (const DrawIndirectCount &value) : drawIndirectCount{value}, mode{EMode::DrawIndirectCount} {}
			Command (const DrawIndexedIndirectCount &value) : drawIndexedIndirectCount{value}, mode{EMode::DrawIndexedIndirectCount} {}
		};
		
		static constexpr uint	MaxViewports 			= 16;
		static constexpr uint	MaxDiscardRectangles	= 8;
		static constexpr uint	MaxSampleLocations		= 16;
		static constexpr uint	MaxDynamicStates		= 8;
		static constexpr uint	MaxVertexBuffers		= 16;
		
		
		struct ViewportState
		{
			FixedArray<VkViewport, MaxViewports>	values;
		};
		
		struct ScissorState
		{
			FixedArray<VkRect2D, MaxViewports>		values;
		};
		
		struct LineWidthState
		{
			float		value;
		};
		
		struct DepthBiasState
		{
			float 		depthBiasConstantFactor;
			float 		depthBiasClamp;
			float 		depthBiasSlopeFactor;
		};
		
		struct BlendConstantsState
		{
			float 		color[4];
		};
		
		struct DepthBoundsState
		{
			float 		minDepthBounds;
			float 		maxDepthBounds;
		};
		
		struct StencilCompareMaskState
		{
			uint32_t 	frontFace;
			uint32_t 	backFace;
		};
		
		struct StencilWriteMaskState
		{
			uint32_t 	frontFace;
			uint32_t 	backFace;
		};
		
		struct StencilReferenceState
		{
			uint32_t 	frontFace;
			uint32_t 	backFace;
		};
		
		struct ViewportWScalingState
		{
			FixedArray<VkViewportWScalingNV, MaxViewports>	values;
		};
		
		struct DiscardRectangleState
		{
			FixedArray<VkRect2D, MaxDiscardRectangles>		values;
		};
		
		struct SampleLocationsState
		{
			VkSampleLocationsInfoEXT							info;
			FixedArray<VkSampleLocationEXT, MaxSampleLocations>	locations;
		};
		
		struct SetStateCommand
		{
			union {
				ViewportState				viewport;
				ScissorState				scissor;
				LineWidthState				lineWidth;
				DepthBiasState				depthBias;
				BlendConstantsState			blendConst;
				DepthBoundsState			depthBounds;
				StencilCompareMaskState		stencilCompareMask;
				StencilWriteMaskState		stencilWriteMask;
				StencilReferenceState		stencilReference;
				ViewportWScalingState		viewportWScaling;
				DiscardRectangleState		discardRectangles;
				SampleLocationsState		sampleLocations;
			};
			VkDynamicState				state;
			
			SetStateCommand () : state{VK_DYNAMIC_STATE_MAX_ENUM} {}
			SetStateCommand (const ViewportState &value) : viewport{value}, state{VK_DYNAMIC_STATE_VIEWPORT} {}
			SetStateCommand (const ScissorState &value) : scissor{value}, state{VK_DYNAMIC_STATE_SCISSOR} {}
			SetStateCommand (const LineWidthState &value) : lineWidth{value}, state{VK_DYNAMIC_STATE_LINE_WIDTH} {}
			SetStateCommand (const DepthBiasState &value) : depthBias{value}, state{VK_DYNAMIC_STATE_DEPTH_BIAS} {}
			SetStateCommand (const BlendConstantsState &value) : blendConst{value}, state{VK_DYNAMIC_STATE_BLEND_CONSTANTS} {}
			SetStateCommand (const DepthBoundsState &value) : depthBounds{value}, state{VK_DYNAMIC_STATE_DEPTH_BOUNDS} {}
			SetStateCommand (const StencilCompareMaskState &value) : stencilCompareMask{value}, state{VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK} {}
			SetStateCommand (const StencilWriteMaskState &value) : stencilWriteMask{value}, state{VK_DYNAMIC_STATE_STENCIL_WRITE_MASK} {}
			SetStateCommand (const StencilReferenceState &value) : stencilReference{value}, state{VK_DYNAMIC_STATE_STENCIL_REFERENCE} {}
			SetStateCommand (const ViewportWScalingState &value) : viewportWScaling{value}, state{VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV} {}
			SetStateCommand (const DiscardRectangleState &value) : discardRectangles{value}, state{VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT} {}
			SetStateCommand (const SampleLocationsState &value) : sampleLocations{value}, state{VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT} {}
			~SetStateCommand () {}
		};
		
		using DynamicStates_t = FixedArray< SetStateCommand, MaxDynamicStates >;
		
		
	private:
		using VertexBuffers_t		= FixedArray< BufferID, MaxVertexBuffers >;
		using VertexBufferOffsets_t	= FixedArray< VkDeviceSize, MaxVertexBuffers >;
	
		
	// variables
	private:
		Command					_cmd;
		DynamicStates_t			_dynamicStates;
		
		VertexBuffers_t			_vertexBuffers;
		VertexBufferOffsets_t	_vertexBufferOffsets;
		
	
	// methods
	public:
		DrawCommand () {}
		
		template <typename CmdType>
		DrawCommand (const CmdType &cmd,
					 ArrayView<SetStateCommand> dynamicStates,
					 ArrayView<Pair<BufferID, VkDeviceSize>> vertexBuffers) :
			_cmd{cmd}
		{
			for (auto& ds : dynamicStates) {
				_dynamicStates.push_back(SetStateCommand{ ds });
			}
			for (auto& vb : vertexBuffers) {
				_vertexBuffers.push_back( vb.first );
				_vertexBufferOffsets.push_back( vb.second );	
			}
		}
	};


}	// VTC
