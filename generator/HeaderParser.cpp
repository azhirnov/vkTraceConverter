// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"
#include "StringParser.h"

namespace VTC
{
/*
=================================================
	_IsWord
=================================================
*/
	bool Generator::_IsWord (StringView value)
	{
		for (size_t i = 0; i < value.length(); ++i)
		{
			const char	c = value[i];
			bool		valid = false;

			valid |= (c >= 'a' and c <= 'z');
			valid |= (c >= 'A' and c <= 'Z');
			valid |= (c == '_');

			if ( i > 0 )
				valid |= (c >= '0' and c <= '9');

			if ( not valid )
				return false;
		}
		return true;
	}

/*
=================================================
	_IsNumber
=================================================
*/
	bool Generator::_IsNumber (StringView value)
	{
		if ( EndsWithIC( value, "ull" ) )
			value = value.substr( 0, value.length()-3 );
		else
		if ( EndsWithIC( value, "ul" ) )
			value = value.substr( 0, value.length()-2 );
		else
		if ( EndsWithIC( value, "u" ) )
			value = value.substr( 0, value.length()-1 );


		if ( StartsWithIC( value, "0x" ) )
		{
			value = value.substr( 2 );
			for (auto& c : value)
			{
				if ( not (c >= '0' and c <= '9') and
					 not (c >= 'A' and c <= 'F') and
					 not (c >= 'a' and c <= 'f') )
					return false;
			}
		}
		else
		{
			if ( value[0] == '-' or value[0] == '+' )
				value = value.substr( 1 );

			for (auto& c : value)
			{
				if ( not (c >= '0' and c <= '9') )
					return false;
			}
		}
		return true;
	}

/*
=================================================
	_IsTypeOrQual
=================================================
*/
	bool Generator::_IsTypeOrQual (StringView value)
	{
		return	value == "*"		or
				value == "["		or
				value == "]"		or
				_IsWord( value )	or
				_IsNumber( value );
	}

/*
=================================================
	_GenerateVK1
=================================================
*/
	bool Generator::_GenerateVK1 (StringView fileData,
												const uint fileIndex,
												ArrayView< StringView > enableIfdef,
												ArrayView< StringView > disableIfdef,
												bool defaultSkip,
												INOUT FuncMap_t &outFunctions,
												INOUT EnumMap_t &outEnums,
												INOUT StructMap_t &outStructs,
												INOUT BitfieldMap_t &outBitfields)
	{
		enum class EMode
		{
			None,
			Struct,
			Enum,
			Func,
			Define,
		};
	
		Array< StringView >	lines;
		StringParser::DivideLines( fileData, lines );

		VkEnumInfo			curr_enum;
		VkStructInfo		curr_struct;
		VkFunctionInfo		curr_func;

		Array< StringView >	tokens;
		EMode				mode			= EMode::None;
		bool				is_voidfunc		= false;

		Array<bool>			skip_stack;		skip_stack.push_back( defaultSkip );

		const Array< StringView >	skip_funcs = {
			// VkAllocationCallbacks
			"vkAllocationFunction",
			"vkReallocationFunction",
			"vkFreeFunction",
			"vkInternalAllocationNotification",
			"vkInternalFreeNotification",

			"vkVoidFunction",

			"VkDebugReportCallbackEXT",
		};

		const auto	ParseArgs	= [&mode, &is_voidfunc, &curr_func, &outFunctions] (ArrayView<StringView> tokens, size_t j)
								{{
									FuncArg		curr_arg;

									for (; j < tokens.size(); ++j)
									{
										if ( not is_voidfunc )
										{
											if ( tokens[j] == "," or tokens[j] == ")" )
											{
												// skip array type
												if ( curr_arg.type.back() == "]" )
												{
													ASSERT( curr_arg.type.size() > 3 );
													curr_arg.name = *(curr_arg.type.end()-4);
													curr_arg.type.erase( curr_arg.type.end()-4 );
												}
												else
												{
													curr_arg.name = curr_arg.type.back();
													curr_arg.type.pop_back();
												}

												ASSERT( _IsWord( curr_arg.name ) and not curr_arg.name.empty() );
												ASSERT( not curr_arg.type.empty() );

												curr_func.args.push_back( std::move(curr_arg) );
												curr_arg = Default;
											}
											else
											{
												ASSERT( _IsTypeOrQual( tokens[j] ) );
												curr_arg.type.push_back( tokens[j] );
											}
										}

										if ( tokens[j] == ")" )
										{
											mode = EMode::None;
											break;
										}
									}
				
									if ( mode == EMode::None and not is_voidfunc )
									{
										ASSERT( outFunctions.find( SearchableFunc{curr_func.name} ) == outFunctions.end() );

										outFunctions.insert( std::move(curr_func) );
										curr_func = Default;
									}
								}};

		const auto	ParseEnumField	= [] (ArrayView<StringView> tokens, size_t i, OUT EnumField &outValue)
									{{
										// find name
										if ( i < tokens.size() )
										{
											ASSERT( StartsWith( tokens[i], "VK_" ) );
											ASSERT( _IsWord( tokens[i] ) );

											outValue.name = tokens[i];
											++i;
										}

										// find value
										for (; i < tokens.size(); ++i)
										{
											if ( tokens[i] == "=" )
												continue;
									
											//ASSERT( _IsNumber( tokens[i] ) );

											outValue.value = tokens[i];
											break;
										}

										CHECK( not outValue.name.empty()  and
											   not outValue.value.empty() );
									}};

		const auto	ParseStructField = [] (ArrayView<StringView> tokens, size_t i, OUT FuncArg &outField)
									{{
										for (; i < tokens.size(); ++i)
										{
											if ( tokens[i] == ";" )
											{
												// skip array type
												if ( outField.type.back() == "]" )
												{
													ASSERT( outField.type.size() > 3 );
													outField.name = *(outField.type.end()-4);
													outField.type.erase( outField.type.end()-4 );
												}
												else
												{
													outField.name = outField.type.back();
													outField.type.pop_back();
												}

												ASSERT( _IsWord( outField.name ) and not outField.name.empty() );
												ASSERT( not outField.type.empty() );
												return;
											}
											else
											{
												ASSERT( _IsTypeOrQual( tokens[i] ) );
												outField.type.push_back( tokens[i] );
											}
										}
									}};

		for (auto& curr_line : lines)
		{
			StringParser::DivideString_CPP( curr_line, OUT tokens );


			switch ( mode )
			{
				case EMode::Struct :
				{
					if ( tokens.size() > 1 and
						 tokens[0] == "}" )
					{
						ASSERT( outStructs.find( SearchableStruct{curr_struct.name} ) == outStructs.end() );

						outStructs.insert( std::move(curr_struct) );

						curr_struct	= Default;
						mode		= EMode::None;
					}
					else
					{
						FuncArg		val;
						ParseStructField( tokens, 0, OUT val );
						curr_struct.fields.push_back( std::move(val) );
					}
					break;
				}

				case EMode::Enum :
				{
					if ( tokens.size() > 1 and
						 tokens[0] == "}" )
					{
						ASSERT( outEnums.find( SearchableEnum{curr_enum.name} ) == outEnums.end() );

						outEnums.insert( std::move(curr_enum) );

						curr_enum	= Default;
						mode		= EMode::None;
					}
					else
					{
						EnumField	val;
						ParseEnumField( tokens, 0, OUT val );
						curr_enum.fields.push_back( std::move(val) );
					}
					break;
				}

				case EMode::Func :
				{
					ParseArgs( tokens, 0 );
					break;
				}

				case EMode::Define :
				{
					if ( tokens.empty() or tokens.back() != "\\" )
					{
						mode = EMode::None;
					}
					break;
				}
			}
		

			if ( tokens.size() > 1 and
				 tokens[0] == "#" and
				 tokens[1] == "endif" )
			{
				skip_stack.pop_back();
				continue;
			}

			// is need to skip
			if ( tokens.size() > 2 and
				 tokens[0] == "#" and
				(tokens[1] == "ifdef" or tokens[1] == "ifndef") )
			{
				bool	is_ifdef	= ( tokens[1] == "ifdef" );
				bool	enabled		= false;
				bool	disabled	= false;

				for (auto& item : enableIfdef)
				{
					if ( item == tokens[2] )
					{
						enabled = true;
						break;
					}
				}
			
				for (auto& item : disableIfdef)
				{
					if ( item == tokens[2] )
					{
						disabled = true;
						break;
					}
				}

				//ASSERT( enabled != disabled );

				skip_stack.push_back( is_ifdef ? not enabled and disabled : not( not enabled and disabled ) );
				continue;
			}

			if ( tokens.size() > 2		and
				 tokens[0] == "#"		and
				 tokens[1] == "if" )
			{
				auto	last = skip_stack.back();
				skip_stack.push_back( last );
				continue;
			}

			if ( skip_stack.back() )
			{
				if ( tokens.size() > 2		and
					 tokens[0] == "#"		and
					 (tokens[1] == "ifdef" or tokens[1] == "ifndef" or tokens[1] == "if") )
				{
					auto	last = skip_stack.back();
					skip_stack.push_back( last );
				}
				continue;
			}


			// struct / enum / union
			if ( tokens.size() > 3				and
				 tokens[0] == "typedef"			and
				 (tokens[1] == "struct" or tokens[1] == "enum" or tokens[1] == "union") and
				 StartsWith( tokens[2], "Vk" ) )
			{
				if ( tokens[1] == "enum" )
				{
					curr_enum.name			= tokens[2];
					curr_enum.fileIndex		= fileIndex;
					mode					= EMode::Enum;
				}
				else
				{
					curr_struct.name		= tokens[2];
					curr_struct.fileIndex	= fileIndex;
					mode					= EMode::Struct;
				}
				continue;
			}


			// function
			if ( tokens.size() > 1		and
				 tokens[0] == "typedef" )
			{
				StringView	prefix		= "PFN_";
				size_t		ret_pos		= 0;
				size_t		name_pos	= 0;

				for (size_t j = 1; j < tokens.size(); ++j) {
					if ( tokens[j-1] == "(" and tokens[j] == "VKAPI_PTR" ) {
						ret_pos = j-1;
						break;
					}
				}

				for (size_t j = ret_pos; j < tokens.size(); ++j) {
					if ( StartsWithIC( tokens[j], prefix ) ) {
						name_pos = j;
						break;
					}
				}

				if ( name_pos > 0 )
				{
					mode = EMode::Func;

					StringView	func_name = tokens[name_pos].substr( prefix.length() );

					is_voidfunc = false;

					for (auto& item : skip_funcs)
					{
						if ( func_name == item )
						{
							is_voidfunc = true;
							break;
						}
					}

					if ( not is_voidfunc )
					{
						curr_func.fileIndex	= fileIndex;
						curr_func.name		= func_name;
				
						ASSERT( _IsWord( curr_func.name ) );

						for (size_t k = 1; k < ret_pos; ++k) {
							curr_func.result.type.push_back( tokens[k] );
						}
					}

					size_t	j = name_pos;

					// move to args
					for (; j < tokens.size(); ++j) {
						if ( tokens[j] == "(" )
							break;
					}

					ParseArgs( tokens, ++j );
					continue;
				}
			}
		

			// bitfield
			if ( tokens.size() == 4	and
				 tokens[0] == "typedef" and
				 tokens[1] == "VkFlags" and
				 tokens[3] == ";" )
			{
				String	enum_name { tokens[2] };

				if ( enum_name.back() == 's' )
				{
					enum_name.pop_back();
					enum_name << "Bits";
				}

				auto	iter = outEnums.find( SearchableEnum{enum_name} );

				VkBitfieldInfo	bitfield;
				bitfield.name		= tokens[2];
				bitfield.enumName	= iter != outEnums.end() ? iter->data.name : "";
				bitfield.fileIndex	= fileIndex;

				outBitfields.insert( bitfield );
				continue;
			}


			// define
			if ( tokens.size() > 1		and
				 tokens[0] == "#"		and
				 tokens[1] != "include" )
			{
				mode = ( tokens.back() == "\\" ? EMode::Define : EMode::None );
				continue;
			}
		}

		return true;
	}

/*
=================================================
	ParseVkHeaders
=================================================
*/
	bool Generator::ParseVkHeaders (const fs::path &folder)
	{
		struct VkHeaderFile
		{
			StringView				filename;
			ArrayView<StringView>	enableIfdef;
			ArrayView<StringView>	disableIfdef;
			bool					defaultSkip;
		};

		const VkHeaderFile  file_names[] = {
			{ "vulkan_core.h",			{ "VK_NO_PROTOTYPES" },		{ "VULKAN_CORE_H_",			"__cplusplus" },	false },
			{ "vulkan_win32.h",			{ "VK_NO_PROTOTYPES" },		{ "VULKAN_WIN32_H_",		"__cplusplus" },	true },
			{ "vulkan_android.h",		{ "VK_NO_PROTOTYPES" },		{ "VULKAN_ANDROID_H_",		"__cplusplus" },	true },
			{ "vulkan_xlib.h",			{ "VK_NO_PROTOTYPES" },		{ "VULKAN_XLIB_H_",			"__cplusplus" },	true },
			{ "vulkan_xlib_xrandr.h",	{ "VK_NO_PROTOTYPES" },		{ "VULKAN_XLIB_XRANDR_H_",	"__cplusplus" },	true },
			{ "vulkan_xcb.h",			{ "VK_NO_PROTOTYPES" },		{ "VULKAN_XCB_H_",			"__cplusplus" },	true },
			//{ "vulkan_mir.h",			{ "VK_NO_PROTOTYPES" },		{ "VULKAN_MIR_H_",			"__cplusplus" },	true },
			{ "vulkan_wayland.h",		{ "VK_NO_PROTOTYPES" },		{ "VULKAN_WAYLAND_H_",		"__cplusplus" },	true }
		};

		_funcs.clear();
		_enums.clear();
		_bitfields.clear();
		_structs.clear();

		for (auto& info : file_names)
		{
			const fs::path	path = folder / info.filename;
			FileRStream		file{ path };
			CHECK_ERR( file.IsOpen() );

			_fileData.push_back({ "", info.disableIfdef.front() });

			String&		buf = _fileData.back().data;
			CHECK( file.Read( size_t(file.Size()), OUT buf ));

			CHECK_ERR( _GenerateVK1( buf, uint(_fileData.size()-1), info.enableIfdef, info.disableIfdef, info.defaultSkip,
									 INOUT _funcs, INOUT _enums, INOUT _structs, INOUT _bitfields ));
		}
		return true;
	}

/*
=================================================
	SetFunctionsScope
=================================================
*/
	bool Generator::SetFunctionsScope ()
	{
		CHECK_ERR( not _resourceTypes.empty() );

		for (auto& fn : _funcs)
		{
			CHECK_ERR( not fn.data.args.empty() );
			
			ResourceTypes_t::const_iterator		res_info;

			for (auto& type : fn.data.args.front().type)
			{
				res_info = _resourceTypes.find( type );
				if ( res_info != _resourceTypes.end() )
					break;
			}

			if ( res_info == _resourceTypes.end() or
				 fn.data.name == "vkGetInstanceProcAddr" )
			{
				fn.data.scope = EFuncScope::Library;
			}
			else
			if ( res_info->second.type == VK_OBJECT_TYPE_INSTANCE or
				 res_info->second.type == VK_OBJECT_TYPE_PHYSICAL_DEVICE or
				 fn.data.name == "vkGetDeviceProcAddr" )
			{
				fn.data.scope = EFuncScope::Instance;
			}
			else
			{
				fn.data.scope = EFuncScope::Device;
			}
		}
		return true;
	}

/*
=================================================
	ParsePacketIDs
=================================================
*/
	bool Generator::ParsePacketIDs (const fs::path &filename)
	{
		CHECK_ERR( fs::exists( filename ));

		FileRStream	file{ filename };
		CHECK_ERR( file.IsOpen() );

		String	buf;
		CHECK_ERR( file.Read( size_t(file.Size()), OUT buf ));
		
		_packetIDs.clear();
		
		const StringView	prefix_any	= "VKTRACE_TPI_";
		const StringView	prefix_vk	= "VKTRACE_TPI_VK_";

		const size_t		first		= buf.find( "_VKTRACE_TRACE_PACKET_ID_VK", 0 );
		const size_t		second		= buf.find( "_VKTRACE_TRACE_PACKET_ID_VK", first+1 );
		
		const HashSet<StringView>	ignore_packets = {
			"VKTRACE_TPI_VK_vkApiVersion",
			"VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX",
			"VKTRACE_TPI_VK_vkCmdSetDeviceMaskKHX",
			"VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHX",
			"VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHX",
			"VKTRACE_TPI_VK_vkAcquireNextImage2KHX",
			"VKTRACE_TPI_VK_vkCmdDispatchBaseKHX",
			"VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroupsKHX",
			"VKTRACE_TPI_VK_vkEnumerateInstanceVersion",
			"VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHX"
		};

		for (size_t	pos = buf.find( prefix_any, first );
			 pos < second;
			 pos = buf.find( prefix_any, pos+1 ))
		{
			size_t	enum_end	= buf.find( ' ', pos );
			auto	name		= StringView(buf).substr( pos, enum_end-pos );

			if ( StartsWith( name, prefix_vk ) and
				 ignore_packets.find( name ) == ignore_packets.end() )
			{
				String	origin	{ name.substr( prefix_vk.length() )};
				String	vk_func = origin;

				// rename some functions
				if ( _funcs.find( SearchableFunc{vk_func} ) == _funcs.end() )
				{
					if ( EndsWith( vk_func, "KHX" ) )
					{
						vk_func.erase( vk_func.length()-3, 3 );
						vk_func << "KHR";
					}

					CHECK_ERR( _funcs.find( SearchableFunc{vk_func} ) != _funcs.end() );
				}

				_packetIDs.push_back(PacketInfo{ String(name), origin, std::move(vk_func) });
			}
			else
			{
				_packetIDs.push_back(PacketInfo{ String(name), "", "" });
			}
		}

		return true;
	}

/*
=================================================
	BuildBasicTypeMap
=================================================
*/
	bool Generator::BuildBasicTypeMap ()
	{
		_basicTypes.clear();
		_basicTypes.insert({ "void",			EBasicType::Void });
		_basicTypes.insert({ "VkBool32",		EBasicType::Bool });
		_basicTypes.insert({ "char",			EBasicType::Char });
		_basicTypes.insert({ "int",				EBasicType::Int });
		_basicTypes.insert({ "int32_t",			EBasicType::Int });
		_basicTypes.insert({ "uint32_t",		EBasicType::UInt });
		_basicTypes.insert({ "uint8_t",			EBasicType::UInt });
		_basicTypes.insert({ "uint16_t",		EBasicType::UInt });
		_basicTypes.insert({ "uint64_t",		EBasicType::ULong });
		_basicTypes.insert({ "size_t",			EBasicType::USize });
		_basicTypes.insert({ "VkDeviceSize",	EBasicType::ULong });
		//_basicTypes.insert({ "VkFlags",		EBasicType::UInt });
		_basicTypes.insert({ "VkSampleMask",	EBasicType::UInt });
		_basicTypes.insert({ "float",			EBasicType::Float });
		//_basicTypes.insert({ "PFN_vkDebugUtilsMessengerCallbackEXT",	EBasicType::Handle });
		_basicTypes.insert({ "VkDebugReportCallbackEXT",				EBasicType::Handle });
		_basicTypes.insert({ "PFN_vkDebugReportCallbackEXT",			EBasicType::Handle });
		_basicTypes.insert({ "PFN_vkAllocationFunction",				EBasicType::Handle });
		_basicTypes.insert({ "PFN_vkReallocationFunction",				EBasicType::Handle });
		_basicTypes.insert({ "PFN_vkFreeFunction",						EBasicType::Handle });
		_basicTypes.insert({ "PFN_vkInternalAllocationNotification",	EBasicType::Handle });
		_basicTypes.insert({ "PFN_vkInternalFreeNotification",			EBasicType::Handle });

		// vulkan_android
		_basicTypes.insert({ "ANativeWindow",		EBasicType::Struct });
		_basicTypes.insert({ "AHardwareBuffer",		EBasicType::Struct });

		// vulkan_mir
		_basicTypes.insert({ "MirConnection",		EBasicType::Struct });
		_basicTypes.insert({ "MirSurface",			EBasicType::Struct });

		// vulkan_wayland
		_basicTypes.insert({ "wl_display",			EBasicType::Struct });
		_basicTypes.insert({ "wl_surface",			EBasicType::Struct });

		// vulkan_win32
		_basicTypes.insert({ "HINSTANCE",			EBasicType::Handle });
		_basicTypes.insert({ "HWND",				EBasicType::Handle });
		_basicTypes.insert({ "HANDLE",				EBasicType::Handle });
		_basicTypes.insert({ "LPCWSTR",				EBasicType::WCharString });
		_basicTypes.insert({ "SECURITY_ATTRIBUTES",	EBasicType::Struct });
		_basicTypes.insert({ "DWORD",				EBasicType::UInt });

		// vulkan_xcb
		_basicTypes.insert({ "xcb_connection_t",	EBasicType::Struct });
		_basicTypes.insert({ "xcb_window_t",		EBasicType::Handle });
		_basicTypes.insert({ "xcb_visualid_t",		EBasicType::Handle });	// TODO: check

		// vulkan_xlib
		_basicTypes.insert({ "Display",				EBasicType::Struct });
		_basicTypes.insert({ "Window",				EBasicType::Handle });
		_basicTypes.insert({ "VisualID",			EBasicType::Handle });	// TODO: check

		// vulkan_xlib_xrandr
		_basicTypes.insert({ "RROutput",			EBasicType::Handle });	// TODO: check

		return true;
	}

/*
=================================================
	BuildResourceTypeMap
=================================================
*/
	bool Generator::BuildResourceTypeMap ()
	{
		_resourceTypes.clear();
		_resourceTypes.insert({ "VkInstance",					{ VK_OBJECT_TYPE_INSTANCE,						"VK_OBJECT_TYPE_INSTANCE" }});
		_resourceTypes.insert({ "VkPhysicalDevice",				{ VK_OBJECT_TYPE_PHYSICAL_DEVICE,				"VK_OBJECT_TYPE_PHYSICAL_DEVICE" }});
		_resourceTypes.insert({ "VkDevice",						{ VK_OBJECT_TYPE_DEVICE,						"VK_OBJECT_TYPE_DEVICE" }});
		_resourceTypes.insert({ "VkQueue",						{ VK_OBJECT_TYPE_QUEUE,							"VK_OBJECT_TYPE_QUEUE" }});
		_resourceTypes.insert({ "VkSemaphore",					{ VK_OBJECT_TYPE_SEMAPHORE,						"VK_OBJECT_TYPE_SEMAPHORE" }});
		_resourceTypes.insert({ "VkCommandBuffer",				{ VK_OBJECT_TYPE_COMMAND_BUFFER,				"VK_OBJECT_TYPE_COMMAND_BUFFER" }});
		_resourceTypes.insert({ "VkFence",						{ VK_OBJECT_TYPE_FENCE,							"VK_OBJECT_TYPE_FENCE" }});
		_resourceTypes.insert({ "VkDeviceMemory",				{ VK_OBJECT_TYPE_DEVICE_MEMORY,					"VK_OBJECT_TYPE_DEVICE_MEMORY" }});
		_resourceTypes.insert({ "VkBuffer",						{ VK_OBJECT_TYPE_BUFFER,						"VK_OBJECT_TYPE_BUFFER" }});
		_resourceTypes.insert({ "VkImage",						{ VK_OBJECT_TYPE_IMAGE,							"VK_OBJECT_TYPE_IMAGE" }});
		_resourceTypes.insert({ "VkEvent",						{ VK_OBJECT_TYPE_EVENT,							"VK_OBJECT_TYPE_EVENT" }});
		_resourceTypes.insert({ "VkQueryPool",					{ VK_OBJECT_TYPE_QUERY_POOL,					"VK_OBJECT_TYPE_QUERY_POOL" }});
		_resourceTypes.insert({ "VkBufferView",					{ VK_OBJECT_TYPE_BUFFER_VIEW,					"VK_OBJECT_TYPE_BUFFER_VIEW" }});
		_resourceTypes.insert({ "VkImageView",					{ VK_OBJECT_TYPE_IMAGE_VIEW,					"VK_OBJECT_TYPE_IMAGE_VIEW" }});
		_resourceTypes.insert({ "VkShaderModule",				{ VK_OBJECT_TYPE_SHADER_MODULE,					"VK_OBJECT_TYPE_SHADER_MODULE" }});
		_resourceTypes.insert({ "VkPipelineCache",				{ VK_OBJECT_TYPE_PIPELINE_CACHE,				"VK_OBJECT_TYPE_PIPELINE_CACHE" }});
		_resourceTypes.insert({ "VkPipelineLayout",				{ VK_OBJECT_TYPE_PIPELINE_LAYOUT,				"VK_OBJECT_TYPE_PIPELINE_LAYOUT" }});
		_resourceTypes.insert({ "VkRenderPass",					{ VK_OBJECT_TYPE_RENDER_PASS,					"VK_OBJECT_TYPE_RENDER_PASS" }});
		_resourceTypes.insert({ "VkPipeline",					{ VK_OBJECT_TYPE_PIPELINE,						"VK_OBJECT_TYPE_PIPELINE" }});
		_resourceTypes.insert({ "VkDescriptorSetLayout",		{ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,			"VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT" }});
		_resourceTypes.insert({ "VkSampler",					{ VK_OBJECT_TYPE_SAMPLER,						"VK_OBJECT_TYPE_SAMPLER" }});
		_resourceTypes.insert({ "VkDescriptorPool",				{ VK_OBJECT_TYPE_DESCRIPTOR_POOL,				"VK_OBJECT_TYPE_DESCRIPTOR_POOL" }});
		_resourceTypes.insert({ "VkDescriptorSet",				{ VK_OBJECT_TYPE_DESCRIPTOR_SET,				"VK_OBJECT_TYPE_DESCRIPTOR_SET" }});
		_resourceTypes.insert({ "VkFramebuffer",				{ VK_OBJECT_TYPE_FRAMEBUFFER,					"VK_OBJECT_TYPE_FRAMEBUFFER" }});
		_resourceTypes.insert({ "VkCommandPool",				{ VK_OBJECT_TYPE_COMMAND_POOL,					"VK_OBJECT_TYPE_COMMAND_POOL" }});
		_resourceTypes.insert({ "VkSurfaceKHR",					{ VK_OBJECT_TYPE_SURFACE_KHR,					"VK_OBJECT_TYPE_SURFACE_KHR" }});
		_resourceTypes.insert({ "VkSwapchainKHR",				{ VK_OBJECT_TYPE_SWAPCHAIN_KHR,					"VK_OBJECT_TYPE_SWAPCHAIN_KHR" }});
		_resourceTypes.insert({ "VkDisplayKHR",					{ VK_OBJECT_TYPE_DISPLAY_KHR,					"VK_OBJECT_TYPE_DISPLAY_KHR" }});
		_resourceTypes.insert({ "VkDisplayModeKHR",				{ VK_OBJECT_TYPE_DISPLAY_MODE_KHR,				"VK_OBJECT_TYPE_DISPLAY_MODE_KHR" }});
		_resourceTypes.insert({ "VkObjectTableNVX",				{ VK_OBJECT_TYPE_OBJECT_TABLE_NVX,				"VK_OBJECT_TYPE_OBJECT_TABLE_NVX" }});
		_resourceTypes.insert({ "VkIndirectCommandsLayoutNVX",	{ VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX,	"VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX" }});
		_resourceTypes.insert({ "VkValidationCacheEXT",			{ VK_OBJECT_TYPE_VALIDATION_CACHE_EXT,			"VK_OBJECT_TYPE_VALIDATION_CACHE_EXT" }});
		_resourceTypes.insert({ "VkSamplerYcbcrConversion",		{ VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION,		"VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION" }});
		_resourceTypes.insert({ "VkDescriptorUpdateTemplate",	{ VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE,	"VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE" }});
		_resourceTypes.insert({ "VkAccelerationStructureNV",	{ VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV,		"VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV" }});


		// TODO: validation
		return true;
	}

/*
=================================================
	BuildFuncArgCountOfMap
=================================================
*/
	bool Generator::BuildFuncArgCountOfMap ()
	{
		const auto	AddCounter = [this] (StringView funcName, StringView arrayName, StringView counterName)
		{
			_funcArgCounter.insert({ {funcName, counterName}, arrayName });
			_funcArgCountOf.insert({ {funcName, arrayName}, counterName });
		};

		_funcArgCountOf.clear();
		_funcArgCounter.clear();

		AddCounter( "vkUpdateDescriptorSets",		"pDescriptorCopies",		"descriptorCopyCount" );
		AddCounter( "vkCmdBindVertexBuffers",		"pBuffers",					"bindingCount" );
		AddCounter( "vkCmdBindVertexBuffers",		"pOffsets",					"bindingCount" );
		AddCounter( "vkCreateSharedSwapchainsKHR",	"pCreateInfos",				"swapchainCount" );
		AddCounter( "vkRegisterObjectsNVX",			"ppObjectTableEntries",		"objectCount" );
		AddCounter( "vkRegisterObjectsNVX",			"pObjectIndices",			"objectCount" );
		AddCounter( "vkUnregisterObjectsNVX",		"ppObjectTableEntries",		"objectCount" );
		AddCounter( "vkUnregisterObjectsNVX",		"pObjectIndices",			"objectCount" );
		AddCounter( "vkSetHdrMetadataEXT",			"pSwapchains",				"swapchainCount" );
		AddCounter( "vkSetHdrMetadataEXT",			"pMetadata",				"swapchainCount" );
		AddCounter( "vkAllocateCommandBuffers",		"pCommandBuffers",			"pAllocateInfo->commandBufferCount" );
		AddCounter( "vkAllocateDescriptorSets",		"pDescriptorSets",			"pAllocateInfo->descriptorSetCount" );
		AddCounter( "vkCmdUpdateBuffer",			"pData",					"dataSize" );
		AddCounter( "vkCmdPushConstants",			"pValues",					"size" );
		AddCounter( "vkGetSwapchainImagesKHR",		"pSwapchainImages",			"pSwapchainImageCount[0]" );
		AddCounter( "vkCreateSharedSwapchainsKHR",	"pSwapchains",				"swapchainCount" );
		AddCounter( "vkEnumeratePhysicalDevices",	"pPhysicalDevices",			"pPhysicalDeviceCount[0]" );
		AddCounter( "vkCreateGraphicsPipelines",	"pPipelines",				"createInfoCount" );
		AddCounter( "vkCreateComputePipelines",		"pPipelines",				"createInfoCount" );
		AddCounter( "vkCmdPushDescriptorSetKHR",	"pDescriptorWrites",		"descriptorWriteCount" );
		AddCounter( "vkCmdBuildAccelerationStructureNV",	"pGeometries",		"geometryCount" );
		AddCounter( "vkCmdBindTransformFeedbackBuffersEXT",	"pBuffers",			"bindingCount" );
		AddCounter( "vkCmdBindTransformFeedbackBuffersEXT",	"pOffsets",			"bindingCount" );
		AddCounter( "vkCmdBindTransformFeedbackBuffersEXT",	"pSizes",			"bindingCount" );

		HashSet<Pair<StringView, StringView>>	skip_args;
		skip_args.insert({ "vkCmdSetViewportShadingRatePaletteNV", "pShadingRatePalettes" });


		for (const auto& func : _funcs)
		{
			for (size_t i = 0; i < func.data.args.size(); ++i)
			{
				auto&	arg = func.data.args[i];

				if ( not (arg.type.front() == "const" and arg.type.back() == "*") or i == 0 )
					continue;

				// search countof argument for array
				auto&		other	= func.data.args[i-1];
				StringView	suffix	= "Count";

				if ( not EndsWith( other.name, suffix ) )
					continue;

				StringView	name = other.name.substr( 0, other.name.length() - suffix.length() );

				if ( HasSubStringIC( arg.name, name ) )
				{
					AddCounter( func.data.name, arg.name, other.name );
				}
				else
				if ( skip_args.count({ func.data.name, arg.name }) == 0 )
				{
					ASSERT( _funcArgCountOf.find({ func.data.name, arg.name }) != _funcArgCountOf.end() );
					//ASSERT(false);	// previous arg ends with 'size' but not match with array name
				}
			}
		}
	
		// TODO: validation
		return true;
	}

/*
=================================================
	_GetFuncArgCounterName
=================================================
*/
	StringView  Generator::_GetFuncArgCounterName (StringView func, StringView argName) const
	{
		auto	iter = _funcArgCountOf.find( {func, argName} );

		if ( iter != _funcArgCountOf.end() )
			return iter->second;

		return {};
	}
	
/*
=================================================
	_IsFuncArgCounter
=================================================
*/
	bool  Generator::_IsFuncArgCounter (StringView func, StringView counterName) const
	{
		return _funcArgCounter.find( {func, counterName} ) != _funcArgCounter.end();
	}

/*
=================================================
	BuildStructFieldCountOfMap
=================================================
*/
	bool Generator::BuildStructFieldCountOfMap ()
	{
		const auto	AddCounter = [this] (StringView structName, StringView arrayName, StringView counterName)
		{
			_structFieldCounter.insert({ {structName, counterName}, arrayName });
			_structFieldCountOf.insert({ {structName, arrayName}, counterName });
		};

		_structFieldCounter.clear();
		_structFieldCountOf.clear();

		AddCounter( "VkDeviceQueueCreateInfo",				"pQueuePriorities",				"queueCount" );
		AddCounter( "VkSubmitInfo",							"pWaitDstStageMask",			"waitSemaphoreCount" );
		AddCounter( "VkBufferCreateInfo",					"pQueueFamilyIndices",			"queueFamilyIndexCount" );
		AddCounter( "VkImageCreateInfo",					"pQueueFamilyIndices",			"queueFamilyIndexCount" );
		AddCounter( "VkDescriptorSetLayoutBinding",			"pImmutableSamplers",			"descriptorCount" );
		AddCounter( "VkDescriptorSetAllocateInfo",			"pSetLayouts",					"descriptorSetCount" );
		AddCounter( "VkWriteDescriptorSet",					"pImageInfo",					"descriptorCount" );
		AddCounter( "VkWriteDescriptorSet",					"pBufferInfo",					"descriptorCount" );
		AddCounter( "VkWriteDescriptorSet",					"pTexelBufferView",				"descriptorCount" );
		AddCounter( "VkSubpassDescription",					"pResolveAttachments",			"colorAttachmentCount" );
		AddCounter( "VkRenderPassCreateInfo",				"pDependencies",				"dependencyCount" );
		AddCounter( "VkBindBufferMemoryDeviceGroupInfo",	"pDeviceIndices",				"deviceIndexCount" );
		AddCounter( "VkBindImageMemoryDeviceGroupInfo",		"pDeviceIndices",				"deviceIndexCount" );
		AddCounter( "VkRenderPassMultiviewCreateInfo",		"pViewMasks",					"subpassCount" );
		AddCounter( "VkRenderPassMultiviewCreateInfo",		"pViewOffsets",					"dependencyCount" );
		AddCounter( "VkRenderPassMultiviewCreateInfo",		"pCorrelationMasks",			"correlationMaskCount" );
		AddCounter( "VkDescriptorUpdateTemplateCreateInfo",	"pDescriptorUpdateEntries",		"descriptorUpdateEntryCount" );
		AddCounter( "VkPresentInfoKHR",						"pImageIndices",				"swapchainCount" );
		AddCounter( "VkPresentInfoKHR",						"pResults",						"swapchainCount" );
		AddCounter( "VkDeviceGroupPresentInfoKHR",			"pDeviceMasks",					"swapchainCount" );
		AddCounter( "VkPresentRegionsKHR",					"pRegions",						"swapchainCount" );
		AddCounter( "VkSubpassDescription2KHR",				"pResolveAttachments",			"colorAttachmentCount" );
		AddCounter( "VkRenderPassCreateInfo2KHR",			"pDependencies",				"dependencyCount" );
		AddCounter( "VkObjectTableCreateInfoNVX",			"pObjectEntryTypes",			"objectCount" );
		AddCounter( "VkObjectTableCreateInfoNVX",			"pObjectEntryCounts",			"objectCount" );
		AddCounter( "VkObjectTableCreateInfoNVX",			"pObjectEntryUsageFlags",		"objectCount" );
		AddCounter( "VkPresentTimesInfoGOOGLE",				"pTimes",						"swapchainCount" );
		AddCounter( "VkSpecializationInfo",					"pMapEntries",					"mapEntryCount" );
		AddCounter( "VkSpecializationInfo",					"pData",						"dataSize" );
		AddCounter( "VkSwapchainCreateInfoKHR",				"pQueueFamilyIndices",			"queueFamilyIndexCount" );
		AddCounter( "VkDebugMarkerObjectTagInfoEXT",		"pTag",							"tagSize" );
		AddCounter( "VkPipelineCacheCreateInfo",			"pInitialData",					"initialDataSize" );
		//AddCounter( "VkValidationCacheCreateInfoEXT",		"pInitialData",					"initialDataSize" );
		AddCounter( "VkShaderModuleCreateInfo",				"pCode",						"codeSize" );
		AddCounter( "VkPipelineMultisampleStateCreateInfo",						"pSampleMask",					"((uint(obj->rasterizationSamples) + 31) / 32)" );
		AddCounter( "VkDescriptorSetVariableDescriptorCountAllocateInfoEXT",	"pDescriptorCounts",			"descriptorSetCount" );
		AddCounter( "VkWriteDescriptorSetInlineUniformBlockEXT",				"pData",						"dataSize" );
		AddCounter( "VkAccelerationStructureInfoNV",							"pGeometries",					"geometryCount" );
		AddCounter( "VkShadingRatePaletteNV",									"pShadingRatePaletteEntries",	"shadingRatePaletteEntryCount" );
		AddCounter( "VkBindAccelerationStructureMemoryInfoNV",					"pDeviceIndices",				"deviceIndexCount" );
		AddCounter( "VkRaytracingPipelineCreateInfoNV",							"pGroupNumbers",				"stageCount" );
		AddCounter( "VkImageDrmFormatModifierExplicitCreateInfoEXT",			"pPlaneLayouts",				"drmFormatModifierPlaneCount" );
		AddCounter( "VkPhysicalDeviceImageDrmFormatModifierInfoEXT",			"pQueueFamilyIndices",			"queueFamilyIndexCount" );
		
		HashSet<Pair<StringView, StringView>>	skip_fields;
		skip_fields.insert({ "VkPipelineViewportShadingRateImageStateCreateInfoNV", "pShadingRatePalettes" });


		for (const auto& info : _structs)
		{
			for (size_t i = 0; i < info.data.fields.size(); ++i)
			{
				auto&	field = info.data.fields[i];

				if ( field.type.back() != "*" or i == 0 )
					continue;

				// search countof field for array
				auto&		other	= info.data.fields[i-1];
				StringView	suffix	= "Count";

				if ( not EndsWith( other.name, suffix ) )
					continue;

				StringView	name = other.name.substr( 0, other.name.length() - suffix.length() );

				if ( HasSubStringIC( field.name, name ) )
				{
					AddCounter( info.data.name, field.name, other.name );
				}
				else
				if ( skip_fields.count({ info.data.name, field.name }) == 0 )
				{
					ASSERT( _structFieldCountOf.find({ info.data.name, field.name }) != _structFieldCountOf.end() );
					//ASSERT(false);	// previous field ends with 'size' but not match with array name
				}
			}
		}

		// TODO: validation
		return true;
	}

/*
=================================================
	_GetStructFieldCounterName
=================================================
*/
	StringView  Generator::_GetStructFieldCounterName (StringView structType, StringView fieldName) const
	{
		auto	iter = _structFieldCountOf.find( {structType, fieldName} );

		if ( iter != _structFieldCountOf.end() )
			return iter->second;

		return {};
	}
	
/*
=================================================
	_IsStructFieldCounter
=================================================
*/
	bool  Generator::_IsStructFieldCounter (StringView structType, StringView counterName) const
	{
		return _structFieldCounter.find( {structType, counterName} ) != _structFieldCounter.end();
	}

/*
=================================================
	BuildSkipPacketsMap
=================================================
*/
	bool Generator::BuildSkipPacketsMap ()
	{
		_skipPackets = {
				"VKTRACE_TPI_VK_vkCreateShaderModule"sv,
				"VKTRACE_TPI_VK_vkCreateInstance"sv,
				"VKTRACE_TPI_VK_vkDestroyInstance"sv,
				"VKTRACE_TPI_VK_vkCreateDevice"sv,
				"VKTRACE_TPI_VK_vkDestroyDevice"sv,
				"VKTRACE_TPI_VK_vkMapMemory"sv,
				"VKTRACE_TPI_VK_vkUnmapMemory"sv,
				//"VKTRACE_TPI_VK_vkFlushMappedMemoryRanges"sv,
				//"VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges"sv,
				"VKTRACE_TPI_VK_vkEnumeratePhysicalDevices"sv,
				"VKTRACE_TPI_VK_vkEnumerateInstanceExtensionProperties"sv,
				"VKTRACE_TPI_VK_vkEnumerateDeviceExtensionProperties"sv,
				"VKTRACE_TPI_VK_vkEnumerateInstanceLayerProperties"sv,
				"VKTRACE_TPI_VK_vkEnumerateDeviceLayerProperties"sv,
				"VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT"sv,
				"VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT"sv,
				"VKTRACE_TPI_VK_vkDebugReportMessageEXT"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalImageFormatPropertiesNV"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties"sv,
				"VKTRACE_TPI_VK_vkGetInstanceProcAddr"sv,
				"VKTRACE_TPI_VK_vkGetDeviceProcAddr"sv,
				"VKTRACE_TPI_VK_vkGetDeviceQueue"sv,
				"VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment"sv,
				"VKTRACE_TPI_VK_vkGetBufferMemoryRequirements"sv,
				"VKTRACE_TPI_VK_vkGetImageMemoryRequirements"sv,
				"VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties"sv,
				"VKTRACE_TPI_VK_vkGetFenceStatus"sv,
				"VKTRACE_TPI_VK_vkGetEventStatus"sv,
				"VKTRACE_TPI_VK_vkGetImageSubresourceLayout"sv,
				"VKTRACE_TPI_VK_vkGetPipelineCacheData"sv,
				"VKTRACE_TPI_VK_vkGetRenderAreaGranularity"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR"sv,
				"VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceWaylandPresentationSupportKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR"sv,
				"VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR"sv,
				"VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormats2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlanePropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetDisplayModePropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetMemoryFdKHR"sv,
				"VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetSemaphoreFdKHR"sv,
				"VKTRACE_TPI_VK_vkGetSwapchainStatusKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX"sv,
				"VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHX"sv,
				"VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHX"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHX"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT"sv,
				"VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE"sv,
				"VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE"sv,
				"VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT"sv,
				"VKTRACE_TPI_VK_vkGetSwapchainCounterEXT"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT"sv,
				"VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR"sv,
				"VKTRACE_TPI_VK_vkGetFenceFdKHR"sv,
				"VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR"sv,
				"VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR"sv,
				"VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR"sv,
				"VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT"sv,
				"VKTRACE_TPI_VK_vkGetValidationCacheDataEXT"sv,
				"VKTRACE_TPI_VK_vkGetShaderInfoAMD"sv,
				"VKTRACE_TPI_VK_vkGetDeviceQueue2"sv,
				"VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport"sv,
				"VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR"sv,
				"VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR"sv,
				"VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures"sv,
				"VKTRACE_TPI_VK_vkGetImageMemoryRequirements2"sv,
				"VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2"sv,
				"VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFenceProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphoreProperties"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlaneProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetDisplayModeProperties2KHR"sv,
				"VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilities2KHR"sv,
				"VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroupsKHX"sv,
				"VKTRACE_TPI_VK_vkEnumerateInstanceVersion"sv,
				"VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroups"sv,
				"VKTRACE_TPI_VK_vkAcquireNextImageKHR"sv,
				"VKTRACE_TPI_VK_vkAcquireNextImage2KHX"sv,
				"VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT"sv,
				"VKTRACE_TPI_VK_vkAcquireNextImage2KHR"sv,
				"VKTRACE_TPI_VK_vkQueuePresentKHR"sv,
				"VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR"sv,
				"VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR"sv,
				"VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate"sv,
				//"VKTRACE_TPI_VK_vkCreatePipelineCache"sv,
				"VKTRACE_TPI_VK_vkDestroyPipelineCache"sv,
				//"VKTRACE_TPI_VK_vkCreateValidationCacheEXT"sv,
				"VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkDestroySurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkCreateWaylandSurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkCreateDisplayModeKHR"sv,
				"VKTRACE_TPI_VK_vkReleaseDisplayEXT"sv,
				"VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR"sv,
				"VKTRACE_TPI_VK_vkDestroySwapchainKHR"sv,
				"VKTRACE_TPI_VK_vkGetSwapchainImagesKHR"sv,
				"VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT"sv,
				"VKTRACE_TPI_VK_vkGetQueryPoolResults"sv
			};
	
		_alwaysSerialize = {
				"VkQueueFlags"sv,
				"VkShaderModuleCreateFlags"sv,
				"VkMemoryMapFlags"sv,
				"VkMemoryPropertyFlags"sv
			};

		_neverSerialize = {
				"VkShaderModuleCreateInfo"sv,
				//"VkAllocationCallbacks"sv,
				"VkDebugReportCallbackCreateInfoEXT"sv,
				"VkDebugUtilsMessengerCreateInfoEXT"sv,
				"VkDebugMarkerObjectTagInfoEXT"sv,
				//"VkPipelineCacheCreateInfo"sv,
				//"VkValidationCacheCreateInfoEXT"sv,
				"VkInstanceCreateInfo"sv,
				"VkApplicationInfo"sv,
				"VkDeviceCreateInfo"sv,
				"VkImportMemoryHostPointerInfoEXT"sv,
				"VkMemoryHostPointerPropertiesEXT"sv,
				"VkWin32KeyedMutexAcquireReleaseInfoKHR"sv,
				"VkWin32KeyedMutexAcquireReleaseInfoNV"sv,
				"VkDebugUtilsObjectTagInfoEXT"sv,
				"VkWriteDescriptorSetInlineUniformBlockEXT"sv,
				"VkCheckpointDataNV"sv
			};

		return true;
	}

/*
=================================================
	BuildFuncArgDestructorMap
=================================================
*/
	bool Generator::BuildFuncArgDestructorMap ()
	{
		_funcArgDestructors.clear();
		_funcArgDestructors.insert({ "vkFreeMemory",						"memory"				});
		_funcArgDestructors.insert({ "vkFreeDescriptorSets",				"pDescriptorSets"		});
		_funcArgDestructors.insert({ "vkFreeCommandBuffers",				"pCommandBuffers"		});
		_funcArgDestructors.insert({ "vkDestroyInstance",					"instance"				});
		_funcArgDestructors.insert({ "vkDestroyDevice",						"device"				});
		_funcArgDestructors.insert({ "vkDestroyFence",						"fence"					});
		_funcArgDestructors.insert({ "vkDestroySemaphore",					"semaphore"				});
		_funcArgDestructors.insert({ "vkDestroyEvent",						"event"					});
		_funcArgDestructors.insert({ "vkDestroyQueryPool",					"queryPool"				});
		_funcArgDestructors.insert({ "vkDestroyBuffer",						"buffer"				});
		_funcArgDestructors.insert({ "vkDestroyBufferView",					"bufferView"			});
		_funcArgDestructors.insert({ "vkDestroyImage",						"image"					});
		_funcArgDestructors.insert({ "vkDestroyImageView",					"imageView"				});
		_funcArgDestructors.insert({ "vkDestroyShaderModule",				"shaderModule"			});
		_funcArgDestructors.insert({ "vkDestroyPipelineCache",				"pipelineCache"			});
		_funcArgDestructors.insert({ "vkDestroyPipeline",					"pipeline"				});
		_funcArgDestructors.insert({ "vkDestroyPipelineLayout",				"pipelineLayout"		});
		_funcArgDestructors.insert({ "vkDestroySampler",					"sampler"				});
		_funcArgDestructors.insert({ "vkDestroyDescriptorSetLayout",		"descriptorSetLayout"	});
		_funcArgDestructors.insert({ "vkDestroyDescriptorPool",				"descriptorPool"		});
		_funcArgDestructors.insert({ "vkDestroyFramebuffer",				"framebuffer"			});
		_funcArgDestructors.insert({ "vkDestroyRenderPass",					"renderPass"			});
		_funcArgDestructors.insert({ "vkDestroyCommandPool",				"commandPool"			});
		_funcArgDestructors.insert({ "vkDestroySamplerYcbcrConversion",		"ycbcrConversion"		});
		_funcArgDestructors.insert({ "vkDestroyDescriptorUpdateTemplate",	"descriptorUpdateTemplate"	});
		_funcArgDestructors.insert({ "vkDestroySurfaceKHR",					"surface"					});
		_funcArgDestructors.insert({ "vkDestroySwapchainKHR",				"swapchain"					});
		_funcArgDestructors.insert({ "vkDestroyDescriptorUpdateTemplateKHR","descriptorUpdateTemplate"	});
		_funcArgDestructors.insert({ "vkDestroySamplerYcbcrConversionKHR",	"ycbcrConversion"			});
		_funcArgDestructors.insert({ "vkDestroyDebugReportCallbackEXT",		"callback"					});
		_funcArgDestructors.insert({ "vkDestroyIndirectCommandsLayoutNVX",	"indirectCommandsLayout"	});
		_funcArgDestructors.insert({ "vkDestroyObjectTableNVX",				"objectTable"				});
		_funcArgDestructors.insert({ "vkDestroyDebugUtilsMessengerEXT",		"messenger"					});
		_funcArgDestructors.insert({ "vkDestroyValidationCacheEXT",			"validationCache"			});
		_funcArgDestructors.insert({ "vkDestroyValidationCacheEXT",			"validationCache"			});

		return true;
	}

/*
=================================================
	_IsFuncArgWillBeDestroyed
=================================================
*/
	bool  Generator::_IsFuncArgWillBeDestroyed (StringView func, StringView argName) const
	{
		return _funcArgDestructors.find({ func, argName }) != _funcArgDestructors.end();
	}

}	// VTC
