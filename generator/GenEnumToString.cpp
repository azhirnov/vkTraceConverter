// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	_SkipSpecialCases
=================================================
*/
	ND_ static bool  _SkipSpecialCases (StringView enumName, StringView fieldName)
	{
		return	(enumName == "VkDescriptorUpdateTemplateType"		and fieldName == "VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_RANGE_SIZE")		or
				(enumName == "VkShaderStageFlagBits"				and fieldName == "VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM")					or
				(enumName == "VkValidationCacheHeaderVersionEXT"	and fieldName == "VK_VALIDATION_CACHE_HEADER_VERSION_RANGE_SIZE_EXT")	or
				(enumName == "VkSamplerAddressMode"					and fieldName == "VK_SAMPLER_ADDRESS_MODE_RANGE_SIZE")					or
				(enumName == "VkPipelineCacheHeaderVersion"			and fieldName == "VK_PIPELINE_CACHE_HEADER_VERSION_RANGE_SIZE");
	}

/*
=================================================
	GenEnumToString
=================================================
*/
	bool Generator::GenEnumToString (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\n";

		for (auto& info : _enums)
		{
			if ( not info.data.required )
				continue;

			//if ( info.data.name.HasSubString( "FlagBits" ) )
			//	continue;

			str << "ND_ inline String  Serialize_" << info.data.name << " (" << info.data.name << " value)\n{\n"
				<< "\tENABLE_ENUM_CHECKS();\n"
				<< "\tswitch ( value )\n\t{\n";

			for (auto& field : info.data.fields)
			{
				if ( _SkipSpecialCases( info.data.name, field.name ) )
					continue;

				if ( HasSubString( field.name, "_MAX_ENUM" ) or HasSubString( field.name, "_RANGE_SIZE" ) )
				{
					str << "\t\tcase " << field.name << " : break;\n";
				}
				else
				{
					if ( not _IsNumber( field.value ) )
						continue;	// skip aliases

					str << "\t\tcase " << field.name << " : return \"" << field.name << "\";\n";
				}
			}

			str << "\t}\n\tDISABLE_ENUM_CHECKS();\n"
				<< "\tRETURN_ERR( \"unsupported value: \"s << EnumToString( value ), \"<unknown>\" );\n}\n\n";
		}

		for (auto& info : _bitfields)
		{
			if ( not info.data.required )
				continue;

			auto	iter = _enums.find( SearchableEnum{info.data.enumName} );

			if ( iter == _enums.end() )
			{
				str << "ND_ inline String  Serialize_" << info.data.name << " (" << info.data.name << " bits)\n{\n"
					<< "\tASSERT( bits == 0 );\n"
					<< "\treturn \"0\";\n"
					<< "}\n\n";
				continue;
			}


			// find _MAX_ENUM or _END_RANGE
			StringView	max_enum;

			for (auto& field : iter->data.fields)
			{
				if ( HasSubString( field.name, "_MAX_ENUM" ) or HasSubString( field.name, "_END_RANGE" ) )
				{
					max_enum = field.name;
					break;
				}
			}
			CHECK_ERR( not max_enum.empty() );


			str << "ND_ inline String  Serialize_" << info.data.name << " (" << info.data.name << " bits)\n{\n"
				<< "\tif ( bits == 0 )\n"
				<< "\t	return \"0\";\n"
				<< "\tString  result;\n"
				<< "\tfor (" << info.data.name << " t = 1; t < " << max_enum << "; t <<= 1)\n"
				<< "\t{\n"
				<< "\t	if ( not EnumEq( bits, t ) )\n"
				<< "\t		continue;\n\n"
				<< "\t	if ( not result.empty() )\n"
				<< "\t		result << \" | \";\n\n"
				<< "\t	result << Serialize_" << info.data.enumName << "( " << info.data.enumName << "(t) );\n"
				<< "\t}\n"
				<< "\treturn result;\n"
				<< "}\n\n";
		}

	
		// store to file
		WFile	file{ output };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

}	// VTC
