// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	_GetRequiredForPackingFunctionsV1
=================================================
*/
	HashSet<StringView> const&  Generator::_GetRequiredForPackingFunctionsV1 ()
	{
		static const HashSet<StringView> requiredVkFunctions = {
			"vkGetDeviceQueue"sv,
			"vkQueueSubmit"sv,
			"vkQueueWaitIdle"sv,
			"vkDeviceWaitIdle"sv,
			"vkAllocateMemory"sv,
			"vkFreeMemory"sv,
			"vkFlushMappedMemoryRanges"sv,
			"vkBindBufferMemory"sv,
			"vkBindImageMemory"sv,
			"vkQueueBindSparse"sv,
			"vkCreateFence"sv,
			"vkDestroyFence"sv,
			"vkResetFences"sv,
			"vkWaitForFences"sv,
			"vkCreateSemaphore"sv,
			"vkDestroySemaphore"sv,
			"vkCreateEvent"sv,
			"vkDestroyEvent"sv,
			"vkSetEvent"sv,
			"vkResetEvent"sv,
			"vkCreateQueryPool"sv,
			"vkDestroyQueryPool"sv,
			"vkCreateBuffer"sv,
			"vkDestroyBuffer"sv,
			"vkCreateBufferView"sv,
			"vkDestroyBufferView"sv,
			"vkCreateImage"sv,
			"vkDestroyImage"sv,
			"vkCreateImageView"sv,
			"vkDestroyImageView"sv,
			"vkDestroyShaderModule"sv,
			"vkDestroyPipelineCache"sv,
			"vkMergePipelineCaches"sv,
			"vkCreateGraphicsPipelines"sv,
			"vkCreateComputePipelines"sv,
			"vkDestroyPipeline"sv,
			"vkCreatePipelineLayout"sv,
			"vkDestroyPipelineLayout"sv,
			"vkCreateSampler"sv,
			"vkDestroySampler"sv,
			"vkCreateDescriptorSetLayout"sv,
			"vkDestroyDescriptorSetLayout"sv,
			"vkCreateDescriptorPool"sv,
			"vkDestroyDescriptorPool"sv,
			"vkResetDescriptorPool"sv,
			"vkAllocateDescriptorSets"sv,
			"vkFreeDescriptorSets"sv,
			"vkUpdateDescriptorSets"sv,
			"vkCreateFramebuffer"sv,
			"vkDestroyFramebuffer"sv,
			"vkCreateRenderPass"sv,
			"vkDestroyRenderPass"sv,
			"vkCreateCommandPool"sv,
			"vkDestroyCommandPool"sv,
			"vkResetCommandPool"sv,
			"vkAllocateCommandBuffers"sv,
			"vkFreeCommandBuffers"sv,
			"vkBeginCommandBuffer"sv,
			"vkEndCommandBuffer"sv,
			"vkResetCommandBuffer"sv,
			"vkCmdBindPipeline"sv,
			"vkCmdSetViewport"sv,
			"vkCmdSetScissor"sv,
			"vkCmdSetLineWidth"sv,
			"vkCmdSetDepthBias"sv,
			"vkCmdSetBlendConstants"sv,
			"vkCmdSetDepthBounds"sv,
			"vkCmdSetStencilCompareMask"sv,
			"vkCmdSetStencilWriteMask"sv,
			"vkCmdSetStencilReference"sv,
			"vkCmdBindDescriptorSets"sv,
			"vkCmdBindIndexBuffer"sv,
			"vkCmdBindVertexBuffers"sv,
			"vkCmdDraw"sv,
			"vkCmdDrawIndexed"sv,
			"vkCmdDrawIndirect"sv,
			"vkCmdDrawIndexedIndirect"sv,
			"vkCmdDispatch"sv,
			"vkCmdDispatchIndirect"sv,
			"vkCmdCopyBuffer"sv,
			"vkCmdCopyImage"sv,
			"vkCmdBlitImage"sv,
			"vkCmdCopyBufferToImage"sv,
			"vkCmdCopyImageToBuffer"sv,
			"vkCmdFillBuffer"sv,
			"vkCmdClearColorImage"sv,
			"vkCmdClearDepthStencilImage"sv,
			"vkCmdClearAttachments"sv,
			"vkCmdResolveImage"sv,
			"vkCmdSetEvent"sv,
			"vkCmdResetEvent"sv,
			"vkCmdWaitEvents"sv,
			"vkCmdPipelineBarrier"sv,
			"vkCmdBeginQuery"sv,
			"vkCmdEndQuery"sv,
			"vkCmdResetQueryPool"sv,
			"vkCmdCopyQueryPoolResults"sv,
			"vkCmdBeginRenderPass"sv,
			"vkCmdNextSubpass"sv,
			"vkCmdEndRenderPass"sv,
			"vkCmdExecuteCommands"sv,
			"vkBindBufferMemory2"sv,				// and vkBindBufferMemory2KHR
			"vkBindImageMemory2"sv,					// and vkBindImageMemory2KHR
			"vkCmdSetDeviceMask"sv,					// and vkCmdSetDeviceMaskKHR
			"vkCmdDispatchBase"sv,					// and vkCmdDispatchBaseKHR
			"vkTrimCommandPool"sv,					// and vkTrimCommandPoolKHR
			"vkGetDeviceQueue2"sv,
			"vkCreateSamplerYcbcrConversion"sv,		// and vkCreateSamplerYcbcrConversionKHR
			"vkDestroySamplerYcbcrConversion"sv,	// and vkDestroySamplerYcbcrConversionKHR
			"vkCreateDescriptorUpdateTemplate"sv,	// and vkCreateDescriptorUpdateTemplateKHR
			"vkDestroyDescriptorUpdateTemplate"sv,	// and vkDestroyDescriptorUpdateTemplateKHR
			"vkCmdPushDescriptorSetKHR"sv,
			"vkCreateRenderPass2KHR"sv,
			"vkCmdBeginRenderPass2KHR"sv,
			"vkCmdNextSubpass2KHR"sv,
			"vkCmdEndRenderPass2KHR"sv,
			"vkCmdDrawIndirectCountKHR"sv,			// and vkCmdDrawIndirectCountAMD
			"vkCmdDrawIndexedIndirectCountKHR"sv,	// and vkCmdDrawIndexedIndirectCountAMD
			"vkCmdBeginConditionalRenderingEXT"sv,
			"vkCmdEndConditionalRenderingEXT"sv,
			"vkCmdProcessCommandsNVX"sv,
			"vkCmdReserveSpaceForCommandsNVX"sv,
			"vkCreateIndirectCommandsLayoutNVX"sv,
			"vkDestroyIndirectCommandsLayoutNVX"sv,
			"vkCreateObjectTableNVX"sv,
			"vkDestroyObjectTableNVX"sv,
			"vkRegisterObjectsNVX"sv,
			"vkUnregisterObjectsNVX"sv,
			"vkCmdSetViewportWScalingNV"sv,
			"vkCmdSetDiscardRectangleEXT"sv,
			"vkCmdSetSampleLocationsEXT"sv,
			"vkDebugMarkerSetObjectNameEXT"sv,
			"vkCmdDebugMarkerBeginEXT"sv,
			"vkCmdDebugMarkerEndEXT"sv,
			"vkCmdDebugMarkerInsertEXT"sv,
			"vkCmdPushConstants"sv,
			//"vkMapMemory"sv,
			//"vkUnmapMemory"sv,
			//"vkGetQueryPoolResults"sv,
			//"vkCreateShaderModule"sv,
			//"vkCreatePipelineCache"sv,
			//"vkCmdUpdateBuffer"sv,
			//"vkCmdWriteTimestamp"sv,
			//"vkAcquireNextImageKHR"sv,
			//"vkAcquireNextImage2KHR"sv,
			//"vkQueuePresentKHR"sv,
			//"vkCmdWriteBufferMarkerAMD"sv,
			//"vkSetHdrMetadataEXT"sv,
			//"vkCmdPushDescriptorSetWithTemplateKHR"sv,
			//"vkUpdateDescriptorSetWithTemplate"sv,	// and vkUpdateDescriptorSetWithTemplateKHR
		};
		return requiredVkFunctions;
	}
	
/*
=================================================
	_GetRequiredForPackingStructures
=================================================
*/
	HashSet<StringView> const&  Generator::_GetRequiredForPackingStructures ()
	{
		static const HashSet<StringView> requiredStructures = {
		// VkSubmitInfo :
			//"VkD3D12FenceSubmitInfoKHR"sv,
			"VkDeviceGroupSubmitInfo"sv,
			"VkProtectedSubmitInfo"sv,
			//"VkWin32KeyedMutexAcquireReleaseInfoKHR"sv,
			//"VkWin32KeyedMutexAcquireReleaseInfoNV"sv,
		// VkMemoryAllocateInfo : 
			"VkDedicatedAllocationMemoryAllocateInfoNV"sv,
			//"VkExportMemoryAllocateInfo"sv,
			//"VkExportMemoryAllocateInfoNV"sv,
			//"VkExportMemoryWin32HandleInfoKHR"sv,
			//"VkExportMemoryWin32HandleInfoNV"sv,
			//"VkImportAndroidHardwareBufferInfoANDROID"sv,
			//"VkImportMemoryFdInfoKHR"sv,
			//"VkImportMemoryHostPointerInfoEXT"sv,
			//"VkImportMemoryWin32HandleInfoKHR"sv,
			//"VkImportMemoryWin32HandleInfoNV"sv,
			"VkMemoryAllocateFlagsInfo"sv,
			"VkMemoryDedicatedAllocateInfo"sv,
		// VkMappedMemoryRange :
		// VkBindSparseInfo :
			"VkDeviceGroupBindSparseInfo"sv,
		// VkFenceCreateInfo :
			//"VkExportFenceCreateInfo"sv,
			//"VkExportFenceWin32HandleInfoKHR"sv,
		// VkSemaphoreCreateInfo :
			//"VkExportSemaphoreCreateInfo"sv,
			//"VkExportSemaphoreWin32HandleInfoKHR"sv,
		// VkEventCreateInfo :
		// VkQueryPoolCreateInfo :
		// VkBufferCreateInfo :
			"VkDedicatedAllocationBufferCreateInfoNV"sv,
			//"VkExternalMemoryBufferCreateInfo"sv,
		// VkBufferViewCreateInfo :
		// VkImageCreateInfo :
			"VkDedicatedAllocationImageCreateInfoNV"sv,
			//"VkExternalFormatANDROID"sv,
			//"VkExternalMemoryImageCreateInfo"sv,
			//"VkExternalMemoryImageCreateInfoNV"sv,
			"VkImageFormatListCreateInfoKHR"sv,
			"VkImageSwapchainCreateInfoKHR"sv,
		// VkImageViewCreateInfo :
			"VkImageViewASTCDecodeModeEXT"sv,
			"VkImageViewUsageCreateInfo"sv,
			"VkSamplerYcbcrConversionInfo"sv,
		// VkShaderModuleCreateInfo :
			//"VkShaderModuleValidationCacheCreateInfoEXT"sv,
		// VkPipelineCacheCreateInfo :
		// VkGraphicsPipelineCreateInfo :
			"VkPipelineDiscardRectangleStateCreateInfoEXT"sv,
			"VkPipelineRepresentativeFragmentTestStateCreateInfoNV"sv,
		// VkPipelineShaderStageCreateInfo :
		// VkPipelineVertexInputStateCreateInfo :
			"VkPipelineVertexInputDivisorStateCreateInfoEXT"sv,
		// VkPipelineInputAssemblyStateCreateInfo :
		// VkPipelineTessellationStateCreateInfo :
			"VkPipelineTessellationDomainOriginStateCreateInfo"sv,
		// VkPipelineViewportStateCreateInfo :
			"VkPipelineViewportCoarseSampleOrderStateCreateInfoNV"sv,
			"VkPipelineViewportExclusiveScissorStateCreateInfoNV"sv,
			"VkPipelineViewportShadingRateImageStateCreateInfoNV"sv,
			"VkPipelineViewportSwizzleStateCreateInfoNV"sv,
			"VkPipelineViewportWScalingStateCreateInfoNV"sv,
		// VkPipelineRasterizationStateCreateInfo :
			"VkPipelineRasterizationConservativeStateCreateInfoEXT"sv,
			"VkPipelineRasterizationStateRasterizationOrderAMD"sv,
		// VkPipelineMultisampleStateCreateInfo :
			"VkPipelineCoverageModulationStateCreateInfoNV"sv,
			"VkPipelineCoverageToColorStateCreateInfoNV"sv,
			"VkPipelineSampleLocationsStateCreateInfoEXT"sv,
		// VkPipelineDepthStencilStateCreateInfo :
		// VkPipelineColorBlendStateCreateInfo :
			"VkPipelineColorBlendAdvancedStateCreateInfoEXT"sv,
		// VkPipelineDynamicStateCreateInfo :
		// VkComputePipelineCreateInfo :
		// VkPipelineLayoutCreateInfo :
		// VkSamplerCreateInfo :
			"VkSamplerReductionModeCreateInfoEXT"sv,
			"VkSamplerYcbcrConversionInfo"sv,
		// VkDescriptorSetLayoutCreateInfo :
			"VkDescriptorSetLayoutBindingFlagsCreateInfoEXT"sv,
		// VkDescriptorPoolCreateInfo :
			"VkDescriptorPoolInlineUniformBlockCreateInfoEXT"sv,
		// VkDescriptorSetAllocateInfo :
			"VkDescriptorSetVariableDescriptorCountAllocateInfoEXT"sv,
		// VkWriteDescriptorSet :
			//"VkDescriptorAccelerationStructureInfoNVX"sv,
			"VkWriteDescriptorSetInlineUniformBlockEXT"sv,
		// VkCopyDescriptorSet :
		// VkFramebufferCreateInfo :
		// VkRenderPassCreateInfo :
			"VkRenderPassInputAttachmentAspectCreateInfo"sv,
			"VkRenderPassMultiviewCreateInfo"sv,
		// VkCommandPoolCreateInfo :
		// VkCommandBufferAllocateInfo :
		// VkCommandBufferBeginInfo :
			"VkDeviceGroupCommandBufferBeginInfo"sv,
			"VkCommandBufferInheritanceInfo"sv,
			"VkCommandBufferInheritanceConditionalRenderingInfoEXT"sv,
		// VkMemoryBarrier :
		// VkBufferMemoryBarrier :
		// VkImageMemoryBarrier :
			"VkSampleLocationsInfoEXT"sv,
		// VkRenderPassBeginInfo :
			"VkDeviceGroupRenderPassBeginInfo"sv,
			"VkRenderPassSampleLocationsBeginInfoEXT"sv,
		// VkBindBufferMemoryInfo :
			"VkBindBufferMemoryDeviceGroupInfo"sv,
		// VkBindImageMemoryInfo :
			"VkBindImageMemoryDeviceGroupInfo"sv,
			"VkBindImageMemorySwapchainInfoKHR"sv,
			"VkBindImagePlaneMemoryInfo"sv,
		// VkDeviceQueueInfo2 :
		// VkSamplerYcbcrConversionCreateInfo :
			//"VkExternalFormatANDROID"sv,
		// VkDescriptorUpdateTemplateCreateInfo :
		// VkPresentInfoKHR :
			//"VkDeviceGroupPresentInfoKHR"sv,
			//"VkDisplayPresentInfoKHR"sv,
			//"VkPresentRegionsKHR"sv,
			//"VkPresentTimesInfoGOOGLE"sv,
		// VkAcquireNextImageInfoKHR :
		// VkRenderPassCreateInfo2KHR :
		// VkSubpassBeginInfoKHR :
		// VkSubpassEndInfoKHR :
		// VkConditionalRenderingBeginInfoEXT :
		// VkCmdProcessCommandsInfoNVX :
		// VkCmdReserveSpaceForCommandsInfoNVX :
		// VkIndirectCommandsLayoutCreateInfoNVX :
		// VkObjectTableCreateInfoNVX :
		// VkDebugMarkerObjectNameInfoEXT :
		// VkDebugMarkerMarkerInfoEXT :
		};
		return requiredStructures;
	}
	
/*
=================================================
	_IsRequiredForPackingFunction
=================================================
*/
	bool Generator::_IsRequiredForPackingFunction (StringView vkFunc)
	{
		return _GetRequiredForPackingFunctionsV1().find( vkFunc ) != _GetRequiredForPackingFunctionsV1().end();
	}

/*
=================================================
	_VulkanTracePacker_MarkRequiredTypes
=================================================
*/
	bool Generator::_VulkanTracePacker_MarkRequiredTypes (ArrayView<StringView> types) const
	{
		for (auto& type : types)
		{
			auto struct_info = _structs.find( SearchableStruct{type} );
			if ( struct_info != _structs.end() )
			{
				if ( struct_info->data.required )
					return false;

				struct_info->data.required = true;

				for (auto& field : struct_info->data.fields)
				{
					_VulkanTracePacker_MarkRequiredTypes( field.type );
				}
				return true;
			}
		}
		return false;
	}

/*
=================================================
	_VulkanTracePacker_MarkRequiredTypes
=================================================
*/
	bool Generator::_VulkanTracePacker_MarkRequiredTypes () const
	{
		const auto&		required_structs = _GetRequiredForPackingStructures();


		// reset all
		for (auto& en : _enums) {
			en.data.required = false;
		}
		for (auto& bf : _bitfields) {
			bf.data.required = false;
		}
		for (auto& st : _structs) {
			st.data.required = false;
		}
		

		// refresh all
		for (auto& st : _structs)
		{
			st.data.required |=	(required_structs.find( st.data.name ) != required_structs.end());

			if ( st.data.required ) {
				for (auto& field : st.data.fields) {
					_VulkanTracePacker_MarkRequiredTypes( field.type );
				}
			}
		}

		for (auto& func : _funcs)
		{
			func.data.required = _IsRequiredForPackingFunction( func.data.name );

			if ( func.data.required ) {
				for (auto& arg : func.data.args) {
					_VulkanTracePacker_MarkRequiredTypes( arg.type );
				}
			}
		}
		return true;
	}
	
/*
=================================================
	_VulkanTracePacker_ProcessVar
=================================================
*/
	bool Generator::_VulkanTracePacker_ProcessVar (StringView fieldName, ArrayView<StringView> fieldType, StringView indent,
												   StringView counterName, bool isField, INOUT String &str) const
	{
		StructMap_t::const_iterator		struct_info		= _structs.end();
		uint							num_pointers	= 0;
		bool							is_array		= false;
		bool							is_const		= false;
		bool							has_stype		= false;

		for (size_t i = 0; i < fieldType.size(); ++i)
		{
			auto&	type = fieldType[i];

			if ( struct_info == _structs.end() )
			{
				struct_info = _structs.find( SearchableStruct{type} );
			}

			num_pointers += uint(type == "*");
			is_const	 |= (type == "const");
			
			if ( type == "[" )
			{
				CHECK_ERR( fieldType.size() > i+2 and fieldType[i+2] == "]" );

				is_array	= true;
				counterName	= fieldType[i+1];
				break;
			}
		}

		if ( struct_info != _structs.end() )
		{
			ASSERT( struct_info->data.required );

			has_stype = _HasSType( struct_info->data );
		}
		
		// build counter name
		String	counter;
		if ( not counterName.empty() )
		{
			if ( counterName.front() == '(' and counterName.back() == ')' )
				counter = counterName;
			else
			if ( _IsNumber( counterName ) or is_array )
				counter = "std::size(obj->"s << fieldName << ")";
			else
				counter << "obj->" << counterName;
		}
		

		// pack output parameter(s)
		/*if ( not is_const and num_pointers > 0 and not isField )
		{
			ASSERT( struct_info == _structs.end() );

			if ( counterName.empty() )
				str << indent << "packer.SetOutput( obj->" << fieldName << " );\n";
			else
				str << indent << "packer.SetOutput( obj->" << fieldName << ", " << counter << " );\n";
		}
		else*/
		
		// pack arrays of pointers to objects
		if ( num_pointers == 2 and not counterName.empty() and struct_info != _structs.end() )
		{
			str << indent << "packer.Push( obj->" << fieldName << " );\n"
				<< indent << "for (uint i = 0; obj->" << fieldName << " and i < " << counter << "; ++i) {\n";
		
			if ( has_stype )
				str << indent << "\tVPackStruct( BitCast<VkBaseInStructure const*>(obj->" << fieldName << "[i]), packer );\n";
			else
				str << indent << "\tVPack_" << struct_info->data.name << "( obj->" << fieldName << "[i], packer );\n";

			str << indent << "}\n"
				<< indent << "packer.Pop( obj->" << fieldName << " );\n";
		}
		else

		// ...
		if ( num_pointers > 1 )
		{
			ASSERT(false);
		}
		else
			
		// special cases
		if ( num_pointers == 1 and struct_info != _structs.end() and
			 struct_info->data.name == "VkAllocationCallbacks" )
		{
			ASSERT( not isField );
			str << indent << "packer << static_cast<VkAllocationCallbacks const*>(null);\n";
			return true;
		}
		else

		// pack 'const void *' array
		if ( fieldType.size() == 3 and fieldType[0] == "const" and fieldType[1] == "void" and fieldType[2] == "*" )
		{
			CHECK_ERR( not counter.empty() );

			str << indent << "packer.SetArray( obj->" << fieldName << ", " << counter << " );\n";
		}
		else

		// pack arrays
		if ( (num_pointers == 1 or is_array) and not counterName.empty() )
		{
			str << indent << "packer.Push( obj->" << fieldName << ", " << counter << " );\n"
				<< indent << "for (uint i = 0; obj->" << fieldName << " and i < " << counter << "; ++i) {\n";
		
			if ( struct_info != _structs.end() and has_stype )
				str << indent << "\tVPackStruct( BitCast<VkBaseInStructure const*>(obj->" << fieldName << " + i), packer );\n";
			else
			if ( struct_info != _structs.end() )
				str << indent << "\tVPack_" << struct_info->data.name << "( obj->" << fieldName << " + i, packer );\n";
			else
				str << indent << "\tpacker << (obj->" << fieldName << "[i]);\n";

			str << indent << "}\n"
				<< indent << "packer.Pop( obj->" << fieldName << " );\n";
		}
		else

		// pack pointer to single object
		if ( num_pointers == 1 and struct_info != _structs.end() )
		{
			CHECK_ERR( counterName.empty() );

			str << indent << "packer.Push( obj->" << fieldName << " );\n";

			if ( has_stype )
				str << indent << "VPackStruct( BitCast<VkBaseInStructure const*>(obj->" << fieldName << "), packer );\n";
			else
				str << indent << "VPack_" << struct_info->data.name << "( obj->" << fieldName << ", packer );\n";

			str << indent << "packer.Pop( obj->" << fieldName << " );\n";
		}
		else

		// pack pointer to basic type
		if ( num_pointers == 1 )
		{
			CHECK_ERR( counterName.empty() );

			if ( fieldName == "pUserData" ) {
				str << indent << "packer << static_cast<const void *>(null); // pUserData\n";
				return true;
			}

			str << indent << "packer << (obj->" << fieldName << ");\n";
		}
		else

		// pack single object
		if ( num_pointers == 0 and struct_info != _structs.end() )
		{
			CHECK_ERR( counterName.empty() );

			if ( has_stype )
				str << indent << "VPackStruct( BitCast<VkBaseInStructure const*>(&obj->" << fieldName << "), packer );\n";
			else
				str << indent << "VPack_" << struct_info->data.name << "( &obj->" << fieldName << ", packer );\n";
		}
		else

		// pack basic type
		if ( num_pointers == 0 )
		{
			CHECK_ERR( counterName.empty() );

			str << indent << "packer << (obj->" << fieldName << ");\n";
		}
		else

		{
			ASSERT(false);
		}

		return true;
	}
	
/*
=================================================
	_VulkanTracePacker_ProcessStruct
=================================================
*/
	bool Generator::_VulkanTracePacker_ProcessStruct (const VkStructInfo &info, StringView stype, OUT String &str) const
	{
		str.clear();

		str << "void VPack_" << info.name << " (const " << info.name << " *obj, VPacker &packer)\n"
			<< "{\n"
			<< "	if ( obj == null ) return;\n"
			<< "	packer.BeginStruct( obj );\n";
		
		String	fields;

		if ( not stype.empty() )
		{
			str << "	ASSERT( obj->sType == " << stype << " );\n"
				<< "	packer << obj->sType;\n"
				<< "	packer.Push( obj->pNext );\n"
				<< "	VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );\n"
				<< "	packer.Pop( obj->pNext );\n";
		}
	
		for (auto& field : info.fields)
		{
			if ( field.name == "pNext" or field.name == "sType" )
				continue;

			CHECK_ERR( _VulkanTracePacker_ProcessVar( field.name, field.type, "\t",
													  _GetStructFieldCounterName( info.name, field.name ), true,
													  INOUT fields ));
		}

		str	<< fields
			<< "	packer.EndStruct( obj );\n"
			<< "}\n\n";

		return true;
	}

/*
=================================================
	_GenPacketIDName
=================================================
*/
	String  Generator::_GenPacketIDName (StringView vkFunc)
	{
		return "V"s << vkFunc.substr( 2 );
	}

/*
=================================================
	_VulkanTracePacker_GenIDs
=================================================
*/
	bool Generator::_VulkanTracePacker_GenIDs (const fs::path &output) const
	{
		String				str = "// auto-generated file\n\n";
		Array<StringView>	sorted;

		// version 1.0
		{
			for (auto& func : _GetRequiredForPackingFunctionsV1())
			{
				sorted.push_back( func );
			}

			std::sort( sorted.begin(), sorted.end() );

			uint	id = 0x1001;

			for (auto& func : sorted)
			{
				str << "\t" << _GenPacketIDName( func ) << " = " << ToString<16>( id++ ) << ",\n";
			}
		}

		// TODO: add other versions

		HddWFile	file{ output };
		CHECK_ERR( file.IsOpen() );	
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}
	
/*
=================================================
	_VulkanTracePacker_GenStructPacker
=================================================
*/
	bool Generator::_VulkanTracePacker_GenStructPacker (const fs::path &headerFile, const fs::path &sourceFile) const
	{
		String	header = "// auto-generated file\n\n";
		String	str1, str2;
	
		header << "void VPackStruct (const VkBaseInStructure*, VPacker&);\n";

		str1 << "// auto-generated file\n\n"
			<< "void VPackStruct (const VkBaseInStructure *ptr, VPacker &packer)\n"
			<< "{\n"
			<< "	if ( ptr == null ) return;\n"
			<< "	ENABLE_ENUM_CHECKS();\n"
			<< "	switch ( ptr->sType )\n"
			<< "	{\n";
	
		auto	st_types = _enums.find( SearchableEnum{"VkStructureType"} );
		CHECK_ERR( st_types != _enums.end() );

		Array<EnumField>	enum_fields = st_types->data.fields;
		String				temp;
	

		for (auto& info : _structs)
		{
			if ( not info.data.required )
				continue;

			CHECK_ERR( info.data.fileIndex == 0 );

			const bool	has_stype = _HasSType( info.data );

			if ( info.data.name == "VkBaseInStructure" or
				 info.data.name == "VkBaseOutStructure" )
				continue;
		
			header << "void VPack_" << info.data.name << " (const " << info.data.name << "*, VPacker&);\n";

			if ( not has_stype )
			{
				CHECK_ERR( _VulkanTracePacker_ProcessStruct( info.data, "", OUT temp ));
			
				str2 << temp << "\n";
				continue;
			}
		

			StringView	enum_name = _FindStructTypeEnum( info.data.name, INOUT enum_fields );
		
			CHECK_ERR( _VulkanTracePacker_ProcessStruct( info.data, enum_name, OUT temp ));
		
			str2 << temp << "\n";

			str1 << "\t\tcase " << enum_name << " : {\n"
				<< "\t\t\t" << info.data.name << " const *  obj = BitCast<" << info.data.name << " const *>( ptr );\n"
				<< "\t\t\tVPack_" << info.data.name << "( obj, packer );\n"
				<< "\t\t\tbreak;\n"
				<< "\t\t}\n\n";
		}
	

		for (auto& field : enum_fields)
		{
			if ( not _IsNumber( field.value ) and field.name != "VK_STRUCTURE_TYPE_RANGE_SIZE" )
				continue;	// skip aliases

			str1 << "\t\tcase " << field.name << " : ASSERT(false); break;\n";
		}

		str1 << "	}\n"
			<< "	DISABLE_ENUM_CHECKS();\n"
			<< "}\n\n";


		// store header to file
		{
			HddWFile	file{ headerFile };
			CHECK_ERR( file.IsOpen() );
			CHECK_ERR( file.Write( StringView(header) ));
		}
		// store source to file
		{
			HddWFile	file{ sourceFile };
			CHECK_ERR( file.IsOpen() );
			CHECK_ERR( file.Write( StringView(str1) ));
			CHECK_ERR( file.Write( StringView(str2) ));
		}
		return true;
	}
	
/*
=================================================
	_VulkanTracePacker_GenFuncPacker
=================================================
*/
	bool Generator::_VulkanTracePacker_GenFuncPacker (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\nENABLE_ENUM_CHECKS();\nswitch ( iter->packet_id )\n{\n";
		
		for (auto& packet : _packetIDs)
		{
			auto	func = _funcs.find( SearchableFunc{packet.vkFunc} );

			if ( func == _funcs.end() or not func->data.required )
			{
				str << "\tcase " << packet.id << " : break;\n";
				continue;
			}
			
			String		temp;
			const bool	returns_vkresult = (func->data.result.type.size() == 1 and func->data.result.type[0] == "VkResult");

			str << "\tcase " << packet.id << " : {\n"
				<< "\t\tauto const*  obj = iter.Cast< packet_" << packet.suffix << " *>();\n"
				<< (returns_vkresult ? "\t\tVK_CALL( obj->result );\n" : "")
				<< "\t\tpacker.Begin( EPacketID::" << _GenPacketIDName( func->data.name ) << " );\n";
			
			for (auto& arg : func->data.args)
			{
				CHECK_ERR( _VulkanTracePacker_ProcessVar( arg.name, arg.type, "\t\t",
														  _GetFuncArgCounterName( packet.vkFunc, arg.name ), false,
														  INOUT temp ));
			}

			str	<< temp
				<< "\t\tpacker.End( EPacketID::" << _GenPacketIDName( func->data.name ) << " );\n"
				<< "\t}\n\n";
		}
		
		str << "}\nDISABLE_ENUM_CHECKS();\n";
		

		HddWFile	file{ output };
		CHECK_ERR( file.IsOpen() );	
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

/*
=================================================
	GenVulkanTracePacker
=================================================
*/
	bool Generator::GenVulkanTracePacker (const fs::path &packetIDsFile, const fs::path &structHeaderFile,
										  const fs::path &structSourceFile, const fs::path &funcFile) const
	{
		CHECK_ERR( _VulkanTracePacker_MarkRequiredTypes() );
		CHECK_ERR( _VulkanTracePacker_GenIDs( packetIDsFile ));
		CHECK_ERR( _VulkanTracePacker_GenStructPacker( structHeaderFile, structSourceFile ));
		CHECK_ERR( _VulkanTracePacker_GenFuncPacker( funcFile ));

		return true;
	}

}	// VTC
