// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

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
		uint	num_pointers	= 0;
		bool	is_array		= false;
		bool	is_const		= false;

		for (auto& type : typeParts)
		{
			num_pointers += uint( type == "*" );

			is_array     |= ( type == "[" or type == "]" );
			is_const	 |= (type == "const");
		}

		// search structure type
		StructMap_t::const_iterator		st_info		= _structs.end();
		bool							has_stype	= false;

		for (auto& type : typeParts)
		{
			st_info = _structs.find( SearchableStruct{type} );

			if ( st_info != _structs.end() )
			{
				has_stype = _HasSType( st_info->data );
				break;
			}
		}

		if ( st_info != _structs.end() and
			 st_info->data.name == "VkAllocationCallbacks" )
		{
			str << indent << parentName << "->" << fieldName << " = null;\n";
			return true;
		}

		// unpack first pointer
		if ( num_pointers > 0 )
		{
			str << indent << "VUnpackPointer( INOUT " << parentName << "->" << fieldName << ", start );\n";
		
			if ( st_info != _structs.end() )
			{
				if ( counterName.empty() )
				{
					if ( has_stype )
						str << indent << "VUnpackStruct( PtrCast<VkBaseOutStructure>(" << parentName << "->" << fieldName << "), start );\n";
					else
						str << indent << "VUnpack_" << st_info->data.name << "( PtrCast<" << st_info->data.name << ">(" << parentName << "->" << fieldName << "), start );\n";
				}
				else
				{
					str << indent << "for (uint i = 0; (" << parentName << "->" << fieldName << " != null) and (i < " << parentName << "->" << counterName << "); ++i) {\n";
				
					if ( has_stype )
						str << indent << "	VUnpackStruct( PtrCast<VkBaseOutStructure>(" << parentName << "->" << fieldName << " + i), start );\n";
					else
						str << indent << "	VUnpack_" << st_info->data.name << "( PtrCast<" << st_info->data.name << ">(" << parentName << "->" << fieldName << " + i), start );\n";
				
					str	<< indent << "}\n";
				}
			}
		}

		// unpack second pointer
		if ( num_pointers > 1 )
		{
			if ( counterName.empty() )
			{
				str << indent << "if ( " << parentName << "->" << fieldName << " != null ) {\n"
					<< indent << "	VUnpackPointer( INOUT *" << parentName << "->" << fieldName << ", start );\n"
					<< indent << "}\n";
			}
			else
			{
				str << indent << "for (uint i = 0; (" << parentName << "->" << fieldName << " != null) and (i < " << parentName << "->" << counterName << "); ++i) {\n"
					<< indent << "	VUnpackPointer( INOUT " << parentName << "->" << fieldName << "[i], start );\n"
					<< indent << "}\n";
			}
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
		str << "void VUnpack_" << info.name << " (" << info.name << " *ptr, void *start)\n"
			<< "{\n"
			<< "	if ( ptr == null ) return;\n";

		for (auto& field : info.fields)
		{
			CHECK_ERR( _VulkanTracePlayer_UnpackType( "ptr", field.name, field.type,
													  _GetStructFieldCounterName( info.name, field.name ), "\t",
													  INOUT str ));
		}
		
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
	
		header << "void VUnpackStruct (VkBaseOutStructure*, void*);\n";

		str1 << "// auto-generated file\n\n"
			<< "void VUnpackStruct (VkBaseOutStructure *ptr, void *start)\n"
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
		
			header << "void VUnpack_" << info.data.name << " (" << info.data.name << "*, void*);\n";

			header2 << "template <> inline VUnpacker::Get<" << info.data.name << "> () { VUnpack_" << info.data.name << "(...); }\n";
			header2 << "template <> inline VUnpacker::Get<" << info.data.name << "*> () { VUnpack_" << info.data.name << "(...); }\n";
			header2 << "template <> inline VUnpacker::Get<" << info.data.name << " const*> () { VUnpack_" << info.data.name << "(...); }\n\n";

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
				<< "\t\t\tVUnpack_" << info.data.name << "( obj, start );\n"
				<< "\t\t\tbreak;\n"
				<< "\t\t}\n\n";
		}

		str1 << "	}\n"
			<< "}\n\n";

		
		// store header to file
		{
			HddWFile	file{ headerFile };
			CHECK_ERR( file.IsOpen() );
			CHECK_ERR( file.Write( StringView(header) ));
			CHECK_ERR( file.Write( StringView(header2) ));
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
	_VulkanTracePlayer_GenFuncPacker
=================================================
*/
	bool Generator::_VulkanTracePlayer_GenFuncUnpacker (const fs::path &output) const
	{
		const auto	TypeToString = [] (ArrayView<StringView> types)
		{
			String	result;
			for (auto& type : types) {
				result << type << ' ';
			}
			return result;
		};


		String	str = "// auto-generated file\n\n";
		String	temp;

		for (auto& vk_func : _GetRequiredForPackingFunctionsV1())
		{
			auto	func = _funcs.find( SearchableFunc{vk_func} );
			CHECK_ERR( func != _funcs.end() );
			
			const bool	returns_vkresult = (func->data.result.type.size() == 1 and func->data.result.type[0] == "VkResult");

			str << "case EPacketID::" << _GenPacketIDName( func->data.name ) << " : {\n";
			temp.clear();

			temp << (returns_vkresult ? "\tVK_CALL( " : "\t") << "app." << func->data.name << "( ";

			for (auto& arg : func->data.args)
			{
				temp << (&arg == &func->data.args.front() ? "\n" : ",\n") << "\t\t\t\t"
					<< "/*" << arg.name << "*/ unpacker.Get<" << TypeToString( arg.type ) << ">()";
			}

			temp << " )" << (returns_vkresult ? ")" : "") << ";\n";

			str << temp
				<< "\tbreak;\n"
				<< "}\n\n";
		}


		HddWFile	file{ output };
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
