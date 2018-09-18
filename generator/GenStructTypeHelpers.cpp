// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	GenStructTypeHelpers
=================================================
*/
	bool Generator::GenStructTypeHelpers (const fs::path &output) const
	{
		String		str;
		String		str1, str2;

		str << "// auto-generated file\n\n"
			<< "template <typename T> struct TypeToEnum;\n"
			<< "template <VkStructureType E> struct EnumToType;\n\n";

		auto	st_types = _enums.find( SearchableEnum{"VkStructureType"} );
		CHECK_ERR( st_types != _enums.end() );
	
		Array<EnumField>	enum_fields = st_types->data.fields;

		for (auto& info : _structs)
		{
			bool	has_stype = false;

			for (auto& field : info.data.fields)
			{
				if ( field.name == "sType" ) {
					has_stype = true;
					break;
				}
			}

			if ( not has_stype							or
				 info.data.name == "VkBaseInStructure"	or
				 info.data.name == "VkBaseOutStructure" )
				continue;
		
			StringView	enum_name = _FindStructTypeEnum( info.data.name, INOUT enum_fields );
		
			if ( info.data.fileIndex > 0 )
			{
				str1 << "#ifdef "s << _fileData[info.data.fileIndex].macro << "\n";
				str2 << "#ifdef "s << _fileData[info.data.fileIndex].macro << "\n";
			}

			str1 << "template <> struct TypeToEnum< " << info.data.name << " > { static constexpr VkStructureType  value = " << enum_name << "; };\n";
			str2 << "template <> struct EnumToType< " << enum_name << " > { using type = " << info.data.name << "; };\n";
		
			if ( info.data.fileIndex > 0 )
			{
				str1 << "#endif // "s << _fileData[info.data.fileIndex].macro << "\n";
				str2 << "#endif // "s << _fileData[info.data.fileIndex].macro << "\n";
			}
		}
	
		str << str1 << "\n\n" << str2;


		// store to file
		HddWFile	file{ output };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

}	// VTC
