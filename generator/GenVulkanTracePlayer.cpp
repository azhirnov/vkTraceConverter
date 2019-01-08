// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{
	
/*
=================================================
	_VulkanTracePlayer_UnpackType
=================================================
*/
	bool Generator::_VulkanTracePlayer_UnpackType (StringView parentName, StringView fieldName, ArrayView<StringView> typeParts,
												   StringView counterName, StringView indent, OUT String &str) const
	{
		// count pointers
		StructMap_t::const_iterator			st_info		= _structs.end();
		ResourceTypes_t::const_iterator		res_info	= _resourceTypes.end();
		bool								has_stype	= false;

		uint	num_pointers	= 0;
		bool	is_array		= false;
		bool	is_const		= false;

		for (auto& type : typeParts)
		{
			if ( not (st_info  != _structs.end() or
					  res_info != _resourceTypes.end()) )
			{
				st_info		= _structs.find( SearchableStruct{type} );
				res_info	= _resourceTypes.find( type );
			}

			num_pointers += uint( type == "*" );

			is_array     |= ( type == "[" or type == "]" );
			is_const	 |= (type == "const");
		}

		if ( st_info != _structs.end() )
		{
			has_stype = _HasSType( st_info->data );
		}

		if ( st_info != _structs.end() and
			 st_info->data.name == "VkAllocationCallbacks" )
		{
			str << indent << parentName << "->" << fieldName << " = null;\n";
			return true;
		}

		
		// unpack struct
		if ( num_pointers == 0 and not is_array )
		{
			if ( st_info != _structs.end() )
			{
				if ( has_stype )
					str << indent << "VUnpackStruct( BitCast<VkBaseOutStructure*>(&" << parentName << "->" << fieldName << "), unpacker );\n";
				else
					str << indent << "VUnpack_" << st_info->data.name << "( &" << parentName << "->" << fieldName << ", unpacker );\n";
			}

			if ( res_info != _resourceTypes.end() )
			{
				str << indent << "unpacker.RemapVkResources( INOUT &" << parentName << "->" << fieldName << ", 1 );\n";
			}
		}

		// unpack first pointer
		if ( num_pointers == 1 )
		{
			str << indent << "unpacker.UnpackPtr( INOUT " << parentName << "->" << fieldName << " );\n";
		
			if ( st_info != _structs.end() )
			{
				if ( counterName.empty() )
				{
					if ( has_stype )
						str << indent << "VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<" << st_info->data.name << "*>(" << parentName << "->" << fieldName << ")), unpacker );\n";
					else
						str << indent << "VUnpack_" << st_info->data.name << "( const_cast<" << st_info->data.name << "*>(" << parentName << "->" << fieldName << "), unpacker );\n";
				}
				else
				{
					str << indent << "for (uint i = 0; (" << parentName << "->" << fieldName << " != null) and (i < " << parentName << "->" << counterName << "); ++i) {\n";
				
					if ( has_stype )
						str << indent << "	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<" << st_info->data.name << "*>(" << parentName << "->" << fieldName << " + i)), unpacker );\n";
					else
						str << indent << "	VUnpack_" << st_info->data.name << "( const_cast<" << st_info->data.name << "*>(" << parentName << "->" << fieldName << " + i), unpacker );\n";
				
					str	<< indent << "}\n";
				}
			}
			
			if ( res_info != _resourceTypes.end() )
			{
				str << indent << "unpacker.RemapVkResources( INOUT " << parentName << "->" << fieldName << ", "
					<< (counterName.empty() ? "1"s : String(parentName) << "->" << counterName) << " );\n";
			}
		}

		// unpack second pointer
		if ( num_pointers == 2 )
		{
			str << indent << "unpacker.UnpackPtr( INOUT " << parentName << "->" << fieldName << " );\n";

			if ( counterName.empty() )
			{
				str << indent << "if ( " << parentName << "->" << fieldName << " != null ) {\n"
					<< indent << "	unpacker.UnpackPtr( INOUT *" << parentName << "->" << fieldName << " );\n";
			}
			else
			{
				str << indent << "for (uint i = 0; (" << parentName << "->" << fieldName << " != null) and (i < " << parentName << "->" << counterName << "); ++i) {\n"
					<< indent << "	unpacker.UnpackPtr( INOUT " << parentName << "->" << fieldName << "[i] );\n";
			}
			
			if ( st_info != _structs.end() )
			{
				if ( has_stype )
					str << indent << "\t\tVUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<" << st_info->data.name << "*>(" << parentName << "->" << fieldName
								<< (counterName.empty() ? "" : "[i]") << ")), unpacker );\n";
				else
					str << indent << "\t\tVUnpack_" << st_info->data.name << "( const_cast<" << st_info->data.name << "*>(" << parentName << "->" << fieldName
								<< (counterName.empty() ? "" : "[i]") << "), unpacker );\n";
			}				
			
			if ( res_info != _resourceTypes.end() )
				ASSERT(false);

			str << indent << "}\n";
		}

		CHECK_ERR( num_pointers <= 2 );
		return true;
	}
	
/*
=================================================
	_VulkanTracePlayer_ProcessStruct
=================================================
*/
	bool Generator::_VulkanTracePlayer_ProcessStruct (const VkStructInfo &info, StringView stype, OUT String &str) const
	{
		str.clear();
		str << "void VUnpack_" << info.name << " (" << info.name << " *ptr, const VUnpacker &unpacker)\n"
			<< "{\n"
			<< "	if ( ptr == null ) return;\n";

		for (auto& field : info.fields)
		{
			CHECK_ERR( _VulkanTracePlayer_UnpackType( "ptr", field.name, field.type,
													  _GetStructFieldCounterName( info.name, field.name ), "\t",
													  INOUT str ));
		}

		if ( _HasSType( info ) )
			str << "\tVUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );\n";

		str << "}\n\n";
		return true;
	}

/*
=================================================
	_VulkanTracePlayer_GenStructUnpacker
=================================================
*/
	bool Generator::_VulkanTracePlayer_GenStructUnpacker (const fs::path &headerFile, const fs::path &sourceFile) const
	{
		String	header = "// auto-generated file\n\n";
		String	header2 = "\n\n";
		String	str1, str2;
	
		header << "void VUnpackStruct (VkBaseOutStructure*, const VUnpacker&);\n";

		str1 << "// auto-generated file\n\n"
			<< "void VUnpackStruct (VkBaseOutStructure *ptr, const VUnpacker &unpacker)\n"
			<< "{\n"
			<< "	if ( ptr == null ) return;\n"
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
		
			header << "void VUnpack_" << info.data.name << " (" << info.data.name << "*, const VUnpacker&);\n";

			header2 << "template <> inline " << info.data.name << "*  VUnpacker::_GetPtr<> (" << info.data.name << " *ptr, uint count) "
					<< "{ for (uint i = 0; i < count; ++i) VUnpack_" << info.data.name << "( &ptr[i], *this );  return ptr; }\n";


			if ( not has_stype )
			{
				CHECK_ERR( _VulkanTracePlayer_ProcessStruct( info.data, "", OUT temp ));
			
				str2 << temp << "\n";
				continue;
			}
		

			StringView	enum_name = _FindStructTypeEnum( info.data.name, INOUT enum_fields );
		
			CHECK_ERR( _VulkanTracePlayer_ProcessStruct( info.data, enum_name, OUT temp ));
		
			str2 << temp << "\n";

			str1 << "\t\tcase " << enum_name << " : {\n"
				<< "\t\t\t" << info.data.name << "*  obj = BitCast<" << info.data.name << "*>( ptr );\n"
				<< "\t\t\tVUnpack_" << info.data.name << "( obj, unpacker );\n"
				<< "\t\t\tbreak;\n"
				<< "\t\t}\n\n";
		}

		str1 << "	}\n"
			<< "}\n\n";

		
		// store header to file
		{
			FileWStream		file{ headerFile };
			CHECK_ERR( file.IsOpen() );
			CHECK_ERR( file.Write( StringView(header) ));
			CHECK_ERR( file.Write( StringView(header2) ));
		}
		// store source to file
		{
			FileWStream		file{ sourceFile };
			CHECK_ERR( file.IsOpen() );
			CHECK_ERR( file.Write( StringView(str1) ));
			CHECK_ERR( file.Write( StringView(str2) ));
		}
		return true;
	}
	
/*
=================================================
	_VulkanTracePlayer_GenFuncPacker
=================================================
*/
	bool Generator::_VulkanTracePlayer_GenFuncUnpacker (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\n";
		String	temp1;
		String	temp2;

		for (auto& vk_func : _GetRequiredForPackingFunctionsV1())
		{
			auto	func = _funcs.find( SearchableFunc{vk_func} );
			CHECK_ERR( func != _funcs.end() );
			
			const bool	returns_vkresult = (func->data.result.type.size() == 1 and func->data.result.type[0] == "VkResult");

			str << "case EPacketID::" << _GenPacketIDName( func->data.name ) << " : {\n";
			temp1.clear();
			temp2.clear();

			temp2 << (returns_vkresult ? "\tVK_CALL( " : "\t") << func->data.name << "( ";

			for (auto& arg : func->data.args)
			{
				String	counter { _GetFuncArgCounterName( func->data.name, arg.name )};
				String	arg_type;
				
				for (auto& type : arg.type) {
					arg_type << (&type == arg.type.data() ?  "" : " ") << type;
				}

				temp1 << "\tauto const&  " << arg.name << " = unpacker.Get<" << arg_type << ">(";

				if ( not counter.empty() )
					temp1 << counter;

				temp1 << ");\n";

				temp2 << (&arg == &func->data.args.front() ? "" : ", ") << arg.name;
			}

			temp2 << " )" << (returns_vkresult ? ")" : "") << ";\n";

			str << temp1 << temp2
				<< "\tbreak;\n"
				<< "}\n\n";
		}


		FileWStream		file{ output };
		CHECK_ERR( file.IsOpen() );	
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

/*
=================================================
	GenVulkanTracePlayer
=================================================
*/
	bool Generator::GenVulkanTracePlayer (const fs::path &structHeaderFile, const fs::path &structSourceFile,
										  const fs::path &funcFile) const
	{
		CHECK_ERR( _VulkanTracePlayer_GenStructUnpacker( structHeaderFile, structSourceFile ));
		CHECK_ERR( _VulkanTracePlayer_GenFuncUnpacker( funcFile ));
		return true;
	}

}	// VTC
