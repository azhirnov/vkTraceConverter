// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "framegraph/Vulkan/Utils/FGEnumCast.h"

namespace FG
{

/*
=================================================
	FGEnumCast (VkFilter)
=================================================
*/
	ND_ inline EFilter  FGEnumCast (VkFilter value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_FILTER_NEAREST :		return EFilter::Nearest;
			case VK_FILTER_LINEAR :			return EFilter::Linear;
			case VK_FILTER_CUBIC_IMG :
			case VK_FILTER_RANGE_SIZE :
			case VK_FILTER_MAX_ENUM :		break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown filter type!" );
	}
	
/*
=================================================
	FGEnumCast (VkSamplerMipmapMode)
=================================================
*/
	ND_ inline EMipmapFilter  FGEnumCast (VkSamplerMipmapMode value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_SAMPLER_MIPMAP_MODE_NEAREST :		return EMipmapFilter::Nearest;
			case VK_SAMPLER_MIPMAP_MODE_LINEAR :		return EMipmapFilter::Linear;
			case VK_SAMPLER_MIPMAP_MODE_RANGE_SIZE :
			case VK_SAMPLER_MIPMAP_MODE_MAX_ENUM :		break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown mipmap filter type!" );
	}
	
/*
=================================================
	FGEnumCast (VkSamplerAddressMode)
=================================================
*/
	ND_ inline EAddressMode  FGEnumCast (VkSamplerAddressMode value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_SAMPLER_ADDRESS_MODE_REPEAT :				return EAddressMode::Repeat;
			case VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT :		return EAddressMode::MirrorRepeat;
			case VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE :		return EAddressMode::ClampToEdge;
			case VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER :		return EAddressMode::ClampToBorder;
			case VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE :	return EAddressMode::MirrorClampToEdge;
			case VK_SAMPLER_ADDRESS_MODE_MAX_ENUM :				break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown address type!" );
	}
	
/*
=================================================
	FGEnumCast (VkCompareOp)
=================================================
*/
	ND_ inline ECompareOp  FGEnumCast (VkCompareOp value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_COMPARE_OP_NEVER :				return ECompareOp::Never;
			case VK_COMPARE_OP_LESS :				return ECompareOp::Less;
			case VK_COMPARE_OP_EQUAL :				return ECompareOp::Equal;
			case VK_COMPARE_OP_LESS_OR_EQUAL :		return ECompareOp::LEqual;
			case VK_COMPARE_OP_GREATER :			return ECompareOp::Greater;
			case VK_COMPARE_OP_NOT_EQUAL :			return ECompareOp::NotEqual;
			case VK_COMPARE_OP_GREATER_OR_EQUAL :	return ECompareOp::GEqual;
			case VK_COMPARE_OP_ALWAYS :				return ECompareOp::Always;
			case VK_COMPARE_OP_RANGE_SIZE :
			case VK_COMPARE_OP_MAX_ENUM :			break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown compare op type!" );
	}
	
/*
=================================================
	FGEnumCast (VkBorderColor)
=================================================
*/
	ND_ inline EBorderColor  FGEnumCast (VkBorderColor value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK :	return EBorderColor::FloatTransparentBlack;
			case VK_BORDER_COLOR_INT_TRANSPARENT_BLACK :	return EBorderColor::IntTransparentBlack;
			case VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK :		return EBorderColor::FloatOpaqueBlack;
			case VK_BORDER_COLOR_INT_OPAQUE_BLACK :			return EBorderColor::IntOpaqueBlack;
			case VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE :		return EBorderColor::FloatOpaqueWhite;
			case VK_BORDER_COLOR_INT_OPAQUE_WHITE :			return EBorderColor::IntOpaqueWhite;
			case VK_BORDER_COLOR_RANGE_SIZE :
			case VK_BORDER_COLOR_MAX_ENUM :					break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown compare op type!" );
	}

/*
=================================================
	FGEnumCast (VkShaderStageFlagBits)
=================================================
*/
	ND_ inline EShader  FGEnumCast (VkShaderStageFlagBits value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_SHADER_STAGE_VERTEX_BIT :					return EShader::Vertex;
			case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT :		return EShader::TessControl;
			case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT :	return EShader::TessEvaluation;
			case VK_SHADER_STAGE_GEOMETRY_BIT :					return EShader::Geometry;
			case VK_SHADER_STAGE_FRAGMENT_BIT :					return EShader::Fragment;
			case VK_SHADER_STAGE_COMPUTE_BIT :					return EShader::Compute;
			case VK_SHADER_STAGE_RAYGEN_BIT_NV :				return EShader::RayGen;
			case VK_SHADER_STAGE_ANY_HIT_BIT_NV :				return EShader::RayAnyHit;
			case VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV :			return EShader::RayClosestHit;
			case VK_SHADER_STAGE_MISS_BIT_NV :					return EShader::RayMiss;
			case VK_SHADER_STAGE_INTERSECTION_BIT_NV :			return EShader::RayIntersection;
			case VK_SHADER_STAGE_CALLABLE_BIT_NV :				return EShader::RayCallable;
			case VK_SHADER_STAGE_TASK_BIT_NV :					return EShader::MeshTask;
			case VK_SHADER_STAGE_MESH_BIT_NV :					return EShader::Mesh;
			case VK_SHADER_STAGE_ALL_GRAPHICS :					break;
			case VK_SHADER_STAGE_ALL :							break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown shader type!" );
	}
	
/*
=================================================
	FGEnumCast (VkPrimitiveTopology)
=================================================
*/
	ND_ inline EPrimitive  FGEnumCast (VkPrimitiveTopology value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_PRIMITIVE_TOPOLOGY_POINT_LIST :						return EPrimitive::Point;
			case VK_PRIMITIVE_TOPOLOGY_LINE_LIST :						return EPrimitive::LineList;
			case VK_PRIMITIVE_TOPOLOGY_LINE_STRIP :						return EPrimitive::LineStrip;
			case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST :					return EPrimitive::TriangleList;
			case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP :					return EPrimitive::TriangleStrip;
			case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN :					return EPrimitive::TriangleFan;
			case VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY :		return EPrimitive::LineListAdjacency;
			case VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY :		return EPrimitive::LineStripAdjacency;
			case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY :	return EPrimitive::TriangleListAdjacency;
			case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY :	return EPrimitive::TriangleStripAdjacency;
			case VK_PRIMITIVE_TOPOLOGY_PATCH_LIST :						return EPrimitive::Patch;
			case VK_PRIMITIVE_TOPOLOGY_RANGE_SIZE :
			case VK_PRIMITIVE_TOPOLOGY_MAX_ENUM :						break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown primitive topology!" );
	}
	
/*
=================================================
	FGEnumCast (VkPolygonMode)
=================================================
*/
	ND_ inline EPolygonMode  FGEnumCast (VkPolygonMode value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_POLYGON_MODE_FILL :					return EPolygonMode::Fill;
			case VK_POLYGON_MODE_LINE :					return EPolygonMode::Line;
			case VK_POLYGON_MODE_POINT :				return EPolygonMode::Point;
			case VK_POLYGON_MODE_FILL_RECTANGLE_NV :
			case VK_POLYGON_MODE_RANGE_SIZE :
			case VK_POLYGON_MODE_MAX_ENUM :				break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown primitive topology!" );
	}
	
/*
=================================================
	FGEnumCast (VkCullModeFlags)
=================================================
*/
	ND_ inline ECullMode  FGEnumCast (VkCullModeFlags value)
	{
		ECullMode	result = ECullMode::None;

		if ( EnumEq( value, VK_CULL_MODE_FRONT_BIT ) )
			result |= ECullMode::Front;

		if ( EnumEq( value, VK_CULL_MODE_BACK_BIT ) )
			result |= ECullMode::Back;

		return result;
	}
	
/*
=================================================
	FGEnumCast (VkStencilOp)
=================================================
*/
	ND_ inline EStencilOp  FGEnumCast (VkStencilOp value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_STENCIL_OP_KEEP :					return EStencilOp::Keep;
			case VK_STENCIL_OP_ZERO :					return EStencilOp::Zero;
			case VK_STENCIL_OP_REPLACE :				return EStencilOp::Replace;
			case VK_STENCIL_OP_INCREMENT_AND_CLAMP :	return EStencilOp::Incr;
			case VK_STENCIL_OP_DECREMENT_AND_CLAMP :	return EStencilOp::Decr;
			case VK_STENCIL_OP_INVERT :					return EStencilOp::Invert;
			case VK_STENCIL_OP_INCREMENT_AND_WRAP :		return EStencilOp::IncrWrap;
			case VK_STENCIL_OP_DECREMENT_AND_WRAP :		return EStencilOp::DecrWrap;
			case VK_STENCIL_OP_RANGE_SIZE :
			case VK_STENCIL_OP_MAX_ENUM :				break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown stencil operation!" );
	}
	
/*
=================================================
	FGEnumCast (VkBlendOp)
=================================================
*/
	ND_ inline EBlendOp  FGEnumCast (VkBlendOp value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_BLEND_OP_ADD :				return EBlendOp::Add;
			case VK_BLEND_OP_SUBTRACT :			return EBlendOp::Sub;
			case VK_BLEND_OP_REVERSE_SUBTRACT :	return EBlendOp::RevSub;
			case VK_BLEND_OP_MIN :				return EBlendOp::Min;
			case VK_BLEND_OP_MAX :				return EBlendOp::Max;
			case VK_BLEND_OP_ZERO_EXT :
			case VK_BLEND_OP_SRC_EXT :
			case VK_BLEND_OP_DST_EXT :
			case VK_BLEND_OP_SRC_OVER_EXT :
			case VK_BLEND_OP_DST_OVER_EXT :
			case VK_BLEND_OP_SRC_IN_EXT :
			case VK_BLEND_OP_DST_IN_EXT :
			case VK_BLEND_OP_SRC_OUT_EXT :
			case VK_BLEND_OP_DST_OUT_EXT :
			case VK_BLEND_OP_SRC_ATOP_EXT :
			case VK_BLEND_OP_DST_ATOP_EXT :
			case VK_BLEND_OP_XOR_EXT :
			case VK_BLEND_OP_MULTIPLY_EXT :
			case VK_BLEND_OP_SCREEN_EXT :
			case VK_BLEND_OP_OVERLAY_EXT :
			case VK_BLEND_OP_DARKEN_EXT :
			case VK_BLEND_OP_LIGHTEN_EXT :
			case VK_BLEND_OP_COLORDODGE_EXT :
			case VK_BLEND_OP_COLORBURN_EXT :
			case VK_BLEND_OP_HARDLIGHT_EXT :
			case VK_BLEND_OP_SOFTLIGHT_EXT :
			case VK_BLEND_OP_DIFFERENCE_EXT :
			case VK_BLEND_OP_EXCLUSION_EXT :
			case VK_BLEND_OP_INVERT_EXT :
			case VK_BLEND_OP_INVERT_RGB_EXT :
			case VK_BLEND_OP_LINEARDODGE_EXT :
			case VK_BLEND_OP_LINEARBURN_EXT :
			case VK_BLEND_OP_VIVIDLIGHT_EXT :
			case VK_BLEND_OP_LINEARLIGHT_EXT :
			case VK_BLEND_OP_PINLIGHT_EXT :
			case VK_BLEND_OP_HARDMIX_EXT :
			case VK_BLEND_OP_HSL_HUE_EXT :
			case VK_BLEND_OP_HSL_SATURATION_EXT :
			case VK_BLEND_OP_HSL_COLOR_EXT :
			case VK_BLEND_OP_HSL_LUMINOSITY_EXT :
			case VK_BLEND_OP_PLUS_EXT :
			case VK_BLEND_OP_PLUS_CLAMPED_EXT :
			case VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT :
			case VK_BLEND_OP_PLUS_DARKER_EXT :
			case VK_BLEND_OP_MINUS_EXT :
			case VK_BLEND_OP_MINUS_CLAMPED_EXT :
			case VK_BLEND_OP_CONTRAST_EXT :
			case VK_BLEND_OP_INVERT_OVG_EXT :
			case VK_BLEND_OP_RED_EXT :
			case VK_BLEND_OP_GREEN_EXT :
			case VK_BLEND_OP_BLUE_EXT :
			case VK_BLEND_OP_RANGE_SIZE :
			case VK_BLEND_OP_MAX_ENUM :		break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown blend operation!" );
	}
	
/*
=================================================
	FGEnumCast (VkBlendFactor)
=================================================
*/
	ND_ inline EBlendFactor  FGEnumCast (VkBlendFactor value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_BLEND_FACTOR_ZERO :						return EBlendFactor::Zero;
			case VK_BLEND_FACTOR_ONE :						return EBlendFactor::One;
			case VK_BLEND_FACTOR_SRC_COLOR :				return EBlendFactor::SrcColor;
			case VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR :		return EBlendFactor::OneMinusSrcColor;
			case VK_BLEND_FACTOR_DST_COLOR :				return EBlendFactor::DstColor;
			case VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR :		return EBlendFactor::OneMinusDstColor;
			case VK_BLEND_FACTOR_SRC_ALPHA :				return EBlendFactor::SrcAlpha;
			case VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA :		return EBlendFactor::OneMinusSrcAlpha;
			case VK_BLEND_FACTOR_DST_ALPHA :				return EBlendFactor::DstAlpha;
			case VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA :		return EBlendFactor::OneMinusDstAlpha;
			case VK_BLEND_FACTOR_CONSTANT_COLOR :			return EBlendFactor::ConstColor;
			case VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR :	return EBlendFactor::OneMinusConstColor;
			case VK_BLEND_FACTOR_CONSTANT_ALPHA :			return EBlendFactor::ConstAlpha;
			case VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA :	return EBlendFactor::OneMinusConstAlpha;
			case VK_BLEND_FACTOR_SRC_ALPHA_SATURATE :		return EBlendFactor::SrcAlphaSaturate;
			case VK_BLEND_FACTOR_SRC1_COLOR :				return EBlendFactor::Src1Color;
			case VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR :		return EBlendFactor::OneMinusSrc1Color;
			case VK_BLEND_FACTOR_SRC1_ALPHA :				return EBlendFactor::Src1Alpha;
			case VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA :		return EBlendFactor::OneMinusSrc1Alpha;
			case VK_BLEND_FACTOR_RANGE_SIZE :
			case VK_BLEND_FACTOR_MAX_ENUM :					break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown blend factor!" );
	}
	
/*
=================================================
	FGEnumCast (VkLogicOp)
=================================================
*/
	ND_ inline ELogicOp  FGEnumCast (VkLogicOp value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_LOGIC_OP_CLEAR :			return ELogicOp::Clear;
			case VK_LOGIC_OP_AND :				return ELogicOp::And;
			case VK_LOGIC_OP_AND_REVERSE :		return ELogicOp::AndReverse;
			case VK_LOGIC_OP_COPY :				return ELogicOp::Copy;
			case VK_LOGIC_OP_AND_INVERTED :		return ELogicOp::AndInverted;
			case VK_LOGIC_OP_NO_OP :			return ELogicOp::NoOp;
			case VK_LOGIC_OP_XOR :				return ELogicOp::Xor;
			case VK_LOGIC_OP_OR :				return ELogicOp::Or;
			case VK_LOGIC_OP_NOR :				return ELogicOp::NotOr;
			case VK_LOGIC_OP_EQUIVALENT :		return ELogicOp::Equiv;
			case VK_LOGIC_OP_INVERT :			return ELogicOp::Invert;
			case VK_LOGIC_OP_OR_REVERSE :		return ELogicOp::OrReverse;
			case VK_LOGIC_OP_COPY_INVERTED :	return ELogicOp::CopyInverted;
			case VK_LOGIC_OP_OR_INVERTED :		return ELogicOp::OrInverted;
			case VK_LOGIC_OP_NAND :				return ELogicOp::NotAnd;
			case VK_LOGIC_OP_SET :				return ELogicOp::Set;
			case VK_LOGIC_OP_RANGE_SIZE :
			case VK_LOGIC_OP_MAX_ENUM :			break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown logic operation!" );
	}
	
/*
=================================================
	FGEnumCastAttrib (VkFormat)
=================================================
*/
	ND_ inline EVertexType  FGEnumCastAttrib (VkFormat value)
	{
		switch ( value )
		{
			case VK_FORMAT_R8_SINT :
			case VK_FORMAT_R16_SINT :
			case VK_FORMAT_R32_SINT :				return EVertexType::Int;
				
			case VK_FORMAT_R8G8_SINT :
			case VK_FORMAT_R16G16_SINT :
			case VK_FORMAT_R32G32_SINT :			return EVertexType::Int2;
				
			case VK_FORMAT_R8G8B8_SINT :
			case VK_FORMAT_R16G16B16_SINT :
			case VK_FORMAT_R32G32B32_SINT :			return EVertexType::Int3;
				
			case VK_FORMAT_R8G8B8A8_SINT :
			case VK_FORMAT_R16G16B16A16_SINT :
			case VK_FORMAT_R32G32B32A32_SINT :		return EVertexType::Int4;

			case VK_FORMAT_R8_UINT :
			case VK_FORMAT_R16_UINT :
			case VK_FORMAT_R32_UINT :				return EVertexType::UInt;

			case VK_FORMAT_R8G8_UINT :
			case VK_FORMAT_R16G16_UINT :
			case VK_FORMAT_R32G32_UINT :			return EVertexType::UInt2;
				
			case VK_FORMAT_R8G8B8_UINT :
			case VK_FORMAT_R16G16B16_UINT :
			case VK_FORMAT_R32G32B32_UINT :			return EVertexType::UInt3;

			case VK_FORMAT_R8G8B8A8_UINT :
			case VK_FORMAT_R16G16B16A16_UINT :
			case VK_FORMAT_R32G32B32A32_UINT :		return EVertexType::UInt4;

			case VK_FORMAT_R64_SINT :				return EVertexType::Long;
			case VK_FORMAT_R64G64_SINT :			return EVertexType::Long2;
			case VK_FORMAT_R64G64B64_SINT :			return EVertexType::Long3;
			case VK_FORMAT_R64G64B64A64_SINT :		return EVertexType::Long4;

			case VK_FORMAT_R64_UINT :				return EVertexType::ULong;
			case VK_FORMAT_R64G64_UINT :			return EVertexType::ULong2;
			case VK_FORMAT_R64G64B64_UINT :			return EVertexType::ULong3;
			case VK_FORMAT_R64G64B64A64_UINT :		return EVertexType::ULong4;
				
			case VK_FORMAT_R8_UNORM :
			case VK_FORMAT_R8_SNORM :
			case VK_FORMAT_R8_USCALED :
			case VK_FORMAT_R8_SSCALED :
			case VK_FORMAT_R16_UNORM :
			case VK_FORMAT_R16_SNORM :
			case VK_FORMAT_R16_USCALED :
			case VK_FORMAT_R16_SSCALED :
			case VK_FORMAT_R32_SFLOAT :				return EVertexType::Float;

			case VK_FORMAT_R8G8_UNORM :
			case VK_FORMAT_R8G8_SNORM :
			case VK_FORMAT_R8G8_USCALED :
			case VK_FORMAT_R8G8_SSCALED :
			case VK_FORMAT_R16G16_UNORM :
			case VK_FORMAT_R16G16_SNORM :
			case VK_FORMAT_R16G16_USCALED :
			case VK_FORMAT_R16G16_SSCALED :
			case VK_FORMAT_R32G32_SFLOAT :			return EVertexType::Float2;

			case VK_FORMAT_R8G8B8_UNORM :
			case VK_FORMAT_R8G8B8_SNORM :
			case VK_FORMAT_R8G8B8_USCALED :
			case VK_FORMAT_R8G8B8_SSCALED :
			case VK_FORMAT_R16G16B16_UNORM :
			case VK_FORMAT_R16G16B16_SNORM :
			case VK_FORMAT_R16G16B16_USCALED :
			case VK_FORMAT_R16G16B16_SSCALED :
			case VK_FORMAT_R32G32B32_SFLOAT :		return EVertexType::Float3;

			case VK_FORMAT_R8G8B8A8_UNORM :
			case VK_FORMAT_R8G8B8A8_SNORM :
			case VK_FORMAT_R8G8B8A8_USCALED :
			case VK_FORMAT_R8G8B8A8_SSCALED :
			case VK_FORMAT_R16G16B16A16_UNORM :
			case VK_FORMAT_R16G16B16A16_SNORM :
			case VK_FORMAT_R16G16B16A16_USCALED :
			case VK_FORMAT_R16G16B16A16_SSCALED :
			case VK_FORMAT_R32G32B32A32_SFLOAT :	return EVertexType::Float4;

			case VK_FORMAT_R64_SFLOAT :				return EVertexType::Double;
			case VK_FORMAT_R64G64_SFLOAT :			return EVertexType::Double2;
			case VK_FORMAT_R64G64B64_SFLOAT :		return EVertexType::Double3;
			case VK_FORMAT_R64G64B64A64_SFLOAT :	return EVertexType::Double4;
		}
		RETURN_ERR( "unknown vertex format!" );
	}
	
/*
=================================================
	FGEnumCastVertex (VkFormat)
=================================================
*/
	ND_ inline EVertexType  FGEnumCastVertex (VkFormat value)
	{
		switch ( value )
		{
			case VK_FORMAT_R8_SINT :				return EVertexType::Byte;
			case VK_FORMAT_R8G8_SINT :				return EVertexType::Byte2;
			case VK_FORMAT_R8G8B8_SINT :			return EVertexType::Byte3;
			case VK_FORMAT_R8G8B8A8_SINT :			return EVertexType::Byte4;
				
			case VK_FORMAT_R8_UINT :				return EVertexType::UByte;
			case VK_FORMAT_R8G8_UINT :				return EVertexType::UByte2;
			case VK_FORMAT_R8G8B8_UINT :			return EVertexType::UByte3;
			case VK_FORMAT_R8G8B8A8_UINT :			return EVertexType::UByte4;

			case VK_FORMAT_R16_SINT :				return EVertexType::Short;
			case VK_FORMAT_R16G16_SINT :			return EVertexType::Short2;
			case VK_FORMAT_R16G16B16_SINT :			return EVertexType::Short3;
			case VK_FORMAT_R16G16B16A16_SINT :		return EVertexType::Short4;
				
			case VK_FORMAT_R16_UINT :				return EVertexType::UShort;
			case VK_FORMAT_R16G16_UINT :			return EVertexType::UShort2;
			case VK_FORMAT_R16G16B16_UINT :			return EVertexType::UShort3;
			case VK_FORMAT_R16G16B16A16_UINT :		return EVertexType::UShort4;

			case VK_FORMAT_R32_SINT :				return EVertexType::Int;
			case VK_FORMAT_R32G32_SINT :			return EVertexType::Int2;
			case VK_FORMAT_R32G32B32_SINT :			return EVertexType::Int3;
			case VK_FORMAT_R32G32B32A32_SINT :		return EVertexType::Int4;

			case VK_FORMAT_R32_UINT :				return EVertexType::UInt;
			case VK_FORMAT_R32G32_UINT :			return EVertexType::UInt2;
			case VK_FORMAT_R32G32B32_UINT :			return EVertexType::UInt3;
			case VK_FORMAT_R32G32B32A32_UINT :		return EVertexType::UInt4;

			case VK_FORMAT_R64_SINT :				return EVertexType::Long;
			case VK_FORMAT_R64G64_SINT :			return EVertexType::Long2;
			case VK_FORMAT_R64G64B64_SINT :			return EVertexType::Long3;
			case VK_FORMAT_R64G64B64A64_SINT :		return EVertexType::Long4;

			case VK_FORMAT_R64_UINT :				return EVertexType::ULong;
			case VK_FORMAT_R64G64_UINT :			return EVertexType::ULong2;
			case VK_FORMAT_R64G64B64_UINT :			return EVertexType::ULong3;
			case VK_FORMAT_R64G64B64A64_UINT :		return EVertexType::ULong4;

			case VK_FORMAT_R8_SNORM :				return EVertexType::Byte_Norm;
			case VK_FORMAT_R8G8_SNORM :				return EVertexType::Byte2_Norm;
			case VK_FORMAT_R8G8B8_SNORM :			return EVertexType::Byte3_Norm;
			case VK_FORMAT_R8G8B8A8_SNORM :			return EVertexType::Byte4_Norm;
				
			case VK_FORMAT_R8_UNORM :				return EVertexType::UByte_Norm;
			case VK_FORMAT_R8G8_UNORM :				return EVertexType::UByte2_Norm;
			case VK_FORMAT_R8G8B8_UNORM :			return EVertexType::UByte3_Norm;
			case VK_FORMAT_R8G8B8A8_UNORM :			return EVertexType::UByte4_Norm;
				
			case VK_FORMAT_R8_SSCALED :				return EVertexType::Byte_Scaled;
			case VK_FORMAT_R8G8_SSCALED :			return EVertexType::Byte2_Scaled;
			case VK_FORMAT_R8G8B8_SSCALED :			return EVertexType::Byte3_Scaled;
			case VK_FORMAT_R8G8B8A8_SSCALED :		return EVertexType::Byte4_Scaled;
				
			case VK_FORMAT_R8_USCALED :				return EVertexType::UByte_Scaled;
			case VK_FORMAT_R8G8_USCALED :			return EVertexType::UByte2_Scaled;
			case VK_FORMAT_R8G8B8_USCALED :			return EVertexType::UByte3_Scaled;
			case VK_FORMAT_R8G8B8A8_USCALED :		return EVertexType::UByte4_Scaled;

			case VK_FORMAT_R16_SNORM :				return EVertexType::Short_Norm;
			case VK_FORMAT_R16G16_SNORM :			return EVertexType::Short2_Norm;
			case VK_FORMAT_R16G16B16_SNORM :		return EVertexType::Short3_Norm;
			case VK_FORMAT_R16G16B16A16_SNORM :		return EVertexType::Short4_Norm;

			case VK_FORMAT_R16_UNORM :				return EVertexType::UShort_Norm;
			case VK_FORMAT_R16G16_UNORM :			return EVertexType::UShort2_Norm;
			case VK_FORMAT_R16G16B16_UNORM :		return EVertexType::UShort3_Norm;
			case VK_FORMAT_R16G16B16A16_UNORM :		return EVertexType::UShort4_Norm;
				
			case VK_FORMAT_R16_SSCALED :			return EVertexType::Short_Scaled;
			case VK_FORMAT_R16G16_SSCALED :			return EVertexType::Short2_Scaled;
			case VK_FORMAT_R16G16B16_SSCALED :		return EVertexType::Short3_Scaled;
			case VK_FORMAT_R16G16B16A16_SSCALED :	return EVertexType::Short4_Scaled;

			case VK_FORMAT_R16_USCALED :			return EVertexType::UShort_Scaled;
			case VK_FORMAT_R16G16_USCALED :			return EVertexType::UShort2_Scaled;
			case VK_FORMAT_R16G16B16_USCALED :		return EVertexType::UShort3_Scaled;
			case VK_FORMAT_R16G16B16A16_USCALED :	return EVertexType::UShort4_Scaled;

			case VK_FORMAT_R32_SFLOAT :				return EVertexType::Float;
			case VK_FORMAT_R32G32_SFLOAT :			return EVertexType::Float2;
			case VK_FORMAT_R32G32B32_SFLOAT :		return EVertexType::Float3;
			case VK_FORMAT_R32G32B32A32_SFLOAT :	return EVertexType::Float4;

			case VK_FORMAT_R64_SFLOAT :				return EVertexType::Double;
			case VK_FORMAT_R64G64_SFLOAT :			return EVertexType::Double2;
			case VK_FORMAT_R64G64B64_SFLOAT :		return EVertexType::Double3;
			case VK_FORMAT_R64G64B64A64_SFLOAT :	return EVertexType::Double4;
		}
		RETURN_ERR( "unknown vertex format!" );
	}
	
/*
=================================================
	FGEnumCast (VkIndexType)
=================================================
*/
	ND_ inline EIndex  FGEnumCast (VkIndexType value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_INDEX_TYPE_UINT16 :			return EIndex::UShort;
			case VK_INDEX_TYPE_UINT32 :			return EIndex::UInt;
			case VK_INDEX_TYPE_NONE_NV :
			case VK_INDEX_TYPE_RANGE_SIZE :
			case VK_INDEX_TYPE_MAX_ENUM :		break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown index type!" );
	}
	
/*
=================================================
	FGEnumCast (VkAttachmentLoadOp)
=================================================
*/
	ND_ inline EAttachmentLoadOp  FGEnumCast (VkAttachmentLoadOp value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_ATTACHMENT_LOAD_OP_LOAD :		return EAttachmentLoadOp::Load;
			case VK_ATTACHMENT_LOAD_OP_CLEAR :		return EAttachmentLoadOp::Clear;
			case VK_ATTACHMENT_LOAD_OP_DONT_CARE :	return EAttachmentLoadOp::Invalidate;
			case VK_ATTACHMENT_LOAD_OP_RANGE_SIZE :
			case VK_ATTACHMENT_LOAD_OP_MAX_ENUM :	break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown image aspect type!" );
	}
	
/*
=================================================
	FGEnumCast (VkAttachmentStoreOp)
=================================================
*/
	ND_ inline EAttachmentStoreOp  FGEnumCast (VkAttachmentStoreOp value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_ATTACHMENT_STORE_OP_STORE :		return EAttachmentStoreOp::Store;
			case VK_ATTACHMENT_STORE_OP_DONT_CARE :	return EAttachmentStoreOp::Invalidate;
			case VK_ATTACHMENT_STORE_OP_RANGE_SIZE :
			case VK_ATTACHMENT_STORE_OP_MAX_ENUM :	break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown image aspect type!" );
	}
	
/*
=================================================
	FGEnumCast (VkImageViewType)
=================================================
*/
	ND_ inline EImage  FGEnumCast (VkImageViewType value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_IMAGE_VIEW_TYPE_1D :			return EImage::Tex1D;
			case VK_IMAGE_VIEW_TYPE_2D :			return EImage::Tex2D;
			case VK_IMAGE_VIEW_TYPE_3D :			return EImage::Tex3D;
			case VK_IMAGE_VIEW_TYPE_CUBE :			return EImage::TexCube;
			case VK_IMAGE_VIEW_TYPE_1D_ARRAY :		return EImage::Tex1DArray;
			case VK_IMAGE_VIEW_TYPE_2D_ARRAY :		return EImage::Tex2DArray;
			case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY :	return EImage::TexCubeArray;
			case VK_IMAGE_VIEW_TYPE_RANGE_SIZE :
			case VK_IMAGE_VIEW_TYPE_MAX_ENUM :		break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown image view type!" );
	}
	
/*
=================================================
	FGEnumCast (VkVertexInputRate)
=================================================
*/
	ND_ inline EVertexInputRate  FGEnumCast (VkVertexInputRate value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case VK_VERTEX_INPUT_RATE_VERTEX :		return EVertexInputRate::Vertex;
			case VK_VERTEX_INPUT_RATE_INSTANCE :	return EVertexInputRate::Instance;
			case VK_VERTEX_INPUT_RATE_RANGE_SIZE :
			case VK_VERTEX_INPUT_RATE_MAX_ENUM :	break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown vertex input rate!" );
	}
	
/*
=================================================
	FGEnumCast (VkDynamicState)
=================================================
*
	ND_ inline EPipelineDynamicState  FGEnumCast (const HashSet<VkDynamicState> &values)
	{
		EPipelineDynamicState	result = Default;

		for (auto& value : values)
		{
			ENABLE_ENUM_CHECKS();
			switch ( value )
			{
				case VK_DYNAMIC_STATE_VIEWPORT :				result |= EPipelineDynamicState::Viewport;				break;
				case VK_DYNAMIC_STATE_SCISSOR :					result |= EPipelineDynamicState::Scissor;				break;
				case VK_DYNAMIC_STATE_LINE_WIDTH :				result |= EPipelineDynamicState::LineWidth;				break;
				case VK_DYNAMIC_STATE_DEPTH_BIAS :				result |= EPipelineDynamicState::DepthBias;				break;
				case VK_DYNAMIC_STATE_BLEND_CONSTANTS :			result |= EPipelineDynamicState::BlendConstants;		break;
				case VK_DYNAMIC_STATE_DEPTH_BOUNDS :			result |= EPipelineDynamicState::DepthBounds;			break;
				case VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK :	result |= EPipelineDynamicState::StencilCompareMask;	break;
				case VK_DYNAMIC_STATE_STENCIL_WRITE_MASK :		result |= EPipelineDynamicState::StencilWriteMask;		break;
				case VK_DYNAMIC_STATE_STENCIL_REFERENCE :		result |= EPipelineDynamicState::StencilReference;		break;
				case VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV :
				case VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT :
				case VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT :
				case VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV :
				case VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV :
				case VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV :
				case VK_DYNAMIC_STATE_RANGE_SIZE :
				case VK_DYNAMIC_STATE_MAX_ENUM :
				default :										RETURN_ERR( "unsupported dynamic state!" );
			}
			DISABLE_ENUM_CHECKS();
		}
		return result;
	}
	
/*
=================================================
	FGEnumCastStages
=================================================
*/
	ND_ inline EShaderStages  FGEnumCastStages (VkShaderStageFlags flags)
	{
		EShaderStages	result = Default;

		for (VkShaderStageFlags t = 1; t < VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM; t <<= 1)
		{
			if ( not EnumEq( flags, t ) )
				continue;

			ENABLE_ENUM_CHECKS();
			switch ( VkShaderStageFlagBits(t) )
			{
				case VK_SHADER_STAGE_VERTEX_BIT :					result |= EShaderStages::Vertex;			break;
				case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT :		result |= EShaderStages::TessControl;		break;
				case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT :	result |= EShaderStages::TessEvaluation;	break;
				case VK_SHADER_STAGE_GEOMETRY_BIT :					result |= EShaderStages::Geometry;			break;
				case VK_SHADER_STAGE_FRAGMENT_BIT :					result |= EShaderStages::Fragment;			break;
				case VK_SHADER_STAGE_COMPUTE_BIT :					result |= EShaderStages::Compute;			break;
				case VK_SHADER_STAGE_RAYGEN_BIT_NV :				result |= EShaderStages::RayGen;			break;
				case VK_SHADER_STAGE_ANY_HIT_BIT_NV :				result |= EShaderStages::RayAnyHit;			break;
				case VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV :			result |= EShaderStages::RayClosestHit;		break;
				case VK_SHADER_STAGE_MISS_BIT_NV :					result |= EShaderStages::RayMiss;			break;
				case VK_SHADER_STAGE_INTERSECTION_BIT_NV :			result |= EShaderStages::RayIntersection;	break;
				case VK_SHADER_STAGE_CALLABLE_BIT_NV :				result |= EShaderStages::RayCallable;		break;
				case VK_SHADER_STAGE_TASK_BIT_NV :					result |= EShaderStages::MeshTask;			break;
				case VK_SHADER_STAGE_MESH_BIT_NV :					result |= EShaderStages::Mesh;				break;
				case VK_SHADER_STAGE_ALL_GRAPHICS :
				case VK_SHADER_STAGE_ALL :							RETURN_ERR( "not supported" );
			}
			DISABLE_ENUM_CHECKS();
		}
		return result;
	}

}	// FG
