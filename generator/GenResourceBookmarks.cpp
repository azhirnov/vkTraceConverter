// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	_GetResourceType
=================================================
*/
	Generator::ResourceTypeInfo const*  Generator::_GetResourceType (StringView typeName) const
	{
		auto	iter = _resourceTypes.find( typeName );

		if ( iter != _resourceTypes.end() )
			return &iter->second;

		return null;
	}

/*
=================================================
	LevelToIndex
=================================================
*/
	ND_ static char  LevelToIndex (uint level)
	{
		ASSERT( level < ('z'-'a') );

		return char('a' + level);
	}

/*
=================================================
	CreateIndent
=================================================
*/
	ND_ static String  CreateIndent (uint level)
	{
		String	result;
		result.reserve( level+1 );

		for (uint i = 0; i < level; ++i) {
			result << '\t';
		}
		return result;
	}

/*
=================================================
	_GenBookmarks_AddResource
=================================================
*/
	bool Generator::_GenBookmarks_AddResource (StringView vkFunc, const FuncArg &arg, INOUT String &str) const
	{
		uint							num_pointers	= 0;
		bool							is_const		= false;
		bool							is_array		= false;
		ResourceTypeInfo const*			res_type		= null;
		StructMap_t::const_iterator		stuct_info		= _structs.end();

		const String	arg_name	= "packet."s << arg.name;
		const String	indent		= "\t\t";

		for (auto& type : arg.type)
		{
			if ( not (res_type or stuct_info != _structs.end()) )
			{
				res_type = _GetResourceType( type );
				stuct_info = _structs.find( SearchableStruct{type} );
			}

			num_pointers += (type == "*");
			is_const	 |= (type == "const");
			is_array	 |= (type == "[" or type == "]");
		}
	
		const String	op_type	= (num_pointers and not is_const) ? "EResOp::Construct" :
									_IsFuncArgWillBeDestroyed( vkFunc, arg.name ) ? "EResOp::Destruct" : "EResOp::Access";


		if ( res_type )
		{
			CHECK_ERR( not is_array );

			StringView	counter = _GetFuncArgCounterName( vkFunc, arg.name );

			if ( num_pointers and not counter.empty() )
			{
				const char	idx = LevelToIndex( 0 );

				str << indent << "for (uint " << idx << " = 0; " << arg_name << " and &packet." << counter << " and " << idx << " < packet." << counter
					<< "; ++" << idx << ") {\n"
					<< indent << "	_AddResourceBookmark( " << res_type->typeName  << ", ResourceID(" << arg_name << "[" << idx << "]), iter, frame_id, " << op_type << " );\n"
					<< indent << "}\n";
			}
			else
			if ( num_pointers )
			{
				str << indent << "if ( " << arg_name << " ) {\n"
					<< indent << "	_AddResourceBookmark( " << res_type->typeName  << ", ResourceID(*" << arg_name << "), iter, frame_id, " << op_type << " );\n"
					<< indent << "}\n";
			}
			else
			{
				CHECK_ERR( counter.empty() );

				str << indent << "_AddResourceBookmark( " << res_type->typeName  << ", ResourceID(" << arg_name << "), iter, frame_id, " << op_type << " );\n";
			}
		}
		else
		if ( num_pointers and is_const and stuct_info != _structs.end() )
		{
			StringView	counter = _GetFuncArgCounterName( vkFunc, arg.name );

			if ( counter.empty() )
			{
				String	str2;
				CHECK_ERR( _GenBookmarks_AddStructResources( stuct_info->data, 1, 0, "*"s << arg_name, INOUT str2 ));

				if ( not str2.empty() )
					str << indent << "if ( " << arg_name << " ) {\n" << str2 << indent << "}\n";
			}
			else
			{
				if ( is_array )
				{
					ASSERT( arg.type.size() > 3 );
					counter = *(arg.type.end()-2);
				}
						
				ASSERT( _IsNumber( counter ) or _IsWord( counter ) );

				const char	idx = LevelToIndex( 0 );
				String		str2;

				CHECK_ERR( _GenBookmarks_AddStructResources( stuct_info->data, 1, 0, String(arg_name) << '['<<idx<<']', INOUT str2 ));

				if ( not str2.empty() ) {
					str << indent << "for (uint " << idx << " = 0; " << arg_name << " and " << idx << " < packet." << counter
						<< "; ++" << idx << ") {\n" << str2 << indent << "}\n";
				}
			}
		}
		return true;
	}

/*
=================================================
	_GenBookmarks_AddStructResources
=================================================
*/
	bool Generator::_GenBookmarks_AddStructResources (const VkStructInfo &info, const uint level, const uint mode,
																	StringView fieldName, OUT String &str) const
	{
		const String	st_access	= "("s << fieldName << ").";
		const String	indent		= CreateIndent( level ) << "\t\t";
		const char		idx			= LevelToIndex( level );

		str.clear();

		for (auto& field : info.fields)
		{
			if ( /*field.name == "sType" or*/ field.name == "pNext" )
			{
				if ( mode == 0 )
				{
					str << indent << "_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(" << fieldName << ")), iter, frame_id );\n";
					return true;
				}

				if ( mode == 1 )
				{
					str << indent << "if ( " << st_access << "pNext )\n"
						<< indent << "	_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(" << st_access << "pNext), iter, frame_id );\n";
				}
			}
		
			uint							num_pointers	= 0;
			bool							is_const		= false;
			bool							is_array		= false;
			ResourceTypeInfo const*			res_type		= null;
			StructMap_t::const_iterator		stuct_info		= _structs.end();
		
			for (auto& type : field.type)
			{
				if ( not (res_type or stuct_info != _structs.end()) )
				{
					res_type = _GetResourceType( type );
					stuct_info = _structs.find( SearchableStruct{type} );
				}

				num_pointers += (type == "*");
				is_const	 |= (type == "const");
				is_array	 |= (type == "[" or type == "]");
			}
		
			const String	op_type	= (num_pointers and not is_const) ? "EResOp::Construct" : "EResOp::Access";

			if ( res_type )
			{
				String	counter{ _GetStructFieldCounterName( info.name, field.name )};
			
				if ( not counter.empty() )
					counter = st_access + counter;

				if ( is_array )
				{
					ASSERT( field.type.size() > 3 );
					counter = *(field.type.end()-2);
				}

				if ( (num_pointers or is_array) and not counter.empty() )
				{
					str << indent << "for (uint " << idx << " = 0; " << st_access << field.name << " and " << idx << " < " << counter
						<< "; ++" << idx << ") {\n"
						<< indent << "	_AddResourceBookmark( " << res_type->typeName  << ", ResourceID(" << st_access << field.name << "[" << idx << "]), iter, frame_id, " << op_type << " );\n"
						<< indent << "}\n";
				}
				else
				if ( num_pointers )
				{
					str << indent << "if ( " << st_access << field.name << " ) {\n"
						<< indent << "	_AddResourceBookmark( " << res_type->typeName  << ", ResourceID(*" << st_access << field.name << "), iter, frame_id, " << op_type << " );\n"
						<< indent << "}\n";
				}
				else
				{
					CHECK_ERR( counter.empty() );

					str << indent << "_AddResourceBookmark( " << res_type->typeName  << ", ResourceID(" << st_access << field.name << "), iter, frame_id, " << op_type << " );\n";
				}
			}
			else
			if ( num_pointers and is_const and stuct_info != _structs.end() )
			{
				String	counter{ _GetStructFieldCounterName( info.name, field.name )};
			
				if ( not counter.empty() )
					counter = st_access + counter;

				if ( counter.empty() and num_pointers )
				{
					String	str2;
					CHECK_ERR( _GenBookmarks_AddStructResources( stuct_info->data, level+1, 1, "*"s << st_access << field.name, INOUT str2 ));

					if ( not str2.empty() )
						str << indent << "if ( " << st_access << field.name << " ) {\n" << str2 << indent << "}\n";
				}
				else
				if ( counter.empty() )
				{
					String	str2;
					CHECK_ERR( _GenBookmarks_AddStructResources( stuct_info->data, level+1, 1, String(st_access) << field.name, INOUT str2 ));

					if ( not str2.empty() )
						str << indent << "if ( true ) {\n" << str2 << indent << "}\n";
				}
				else
				{
					if ( is_array )
					{
						ASSERT( field.type.size() > 3 );
						counter = *(field.type.end()-2);
					}
				
					String		str2;
					CHECK_ERR( _GenBookmarks_AddStructResources( stuct_info->data, level+1, 1, String(st_access) << field.name << '['<<idx<<']', INOUT str2 ));

					if ( not str2.empty() ) {
						str << indent << "for (uint " << idx << " = 0; " << st_access << field.name << " and " << idx << " < " << counter
							<< "; ++" << idx << ") {\n" << str2 << indent << "}\n";
					}
				}
			}
		}
		return true;
	}

/*
=================================================
	_GenBookmarks_ProcessPacket
=================================================
*/
	bool Generator::_GenBookmarks_ProcessPacket (const PacketInfo &packet, OUT String &str) const
	{
		str.clear();

		auto	func_info = _funcs.find( SearchableFunc{packet.vkFunc} );
		CHECK_ERR( func_info != _funcs.end() );

		str	<< "\t\tpacket_" << packet.suffix << " const&  packet = iter.Cast<packet_" << packet.suffix << ">();\n";

		const size_t	str_len = str.length();

		for (auto& arg : func_info->data.args)
		{
			CHECK_ERR( _GenBookmarks_AddResource( packet.vkFunc, arg, INOUT str ));
		}

		if ( str_len == str.length() )
			str.clear();

		return true;
	}

/*
=================================================
	GenResourceBookmarks
=================================================
*/
	bool Generator::GenBookmarksForFunc (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\nENABLE_ENUM_CHECKS();\nswitch ( iter->packet_id )\n{\n";
		String	temp;

		for (auto& packet : _packetIDs)
		{
			if ( packet.vkFunc.empty() )
			{
				str << "\tcase " << packet.id << " : break;\n";
			}
			else
			{
				str << "\tcase " << packet.id << " : {\n";

				CHECK_ERR( _GenBookmarks_ProcessPacket( packet, OUT temp ));

				str	<< temp
					<< "\t	break;\n"
					<< "\t}\n\n";
			}
		}

		str << "}\nDISABLE_ENUM_CHECKS();\n";


		// store to file
		FileWStream		file{ output };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

/*
=================================================
	_FindStructTypeEnum
=================================================
*/
	StringView  Generator::_FindStructTypeEnum (StringView structType, INOUT Array<Generator::EnumField> &values)
	{
		const auto	IsNumber	= [] (const char c) { return (c >= '0' and c <= '9'); };

		String		type_name	= "VK_STRUCTURE_TYPE_";

		if ( StartsWith( structType, "Vk" ) )
			structType = structType.substr( 2 );

		bool	req_space	= false;
		uint	mode		= 0;

		for (size_t i = 0; i < structType.size(); ++i)
		{
			const char	c			= structType[i];
			const char	next		= i+1 < structType.length() ? structType[i+1] : c;
			const uint	last_mode	= mode;

			mode = 0;

			if ( i > 0 )
			{
				if ( IsUpperCase( c ) )
					mode = 1;
			
				if ( IsNumber( c ) )
					mode = 2;

				if ( last_mode == 1 and IsUpperCase( c ) and IsLowerCase( next ) )
					req_space = true;
			}

			if ( mode and i > 0 )
			{
				if ( req_space or last_mode != mode )
				{
					type_name << '_';
					req_space = false;
				}
			}
			else
				req_space = true;

			type_name << ToUpperCase( c );
		}

		// validate
		{
			FindAndReplace( INOUT type_name, "WIN_32", "WIN32" );
			FindAndReplace( INOUT type_name, "16_BIT", "16BIT" );
			FindAndReplace( INOUT type_name, "8_BIT", "8BIT" );
			FindAndReplace( INOUT type_name, "D_3_D_12", "D3D12" );
			FindAndReplace( INOUT type_name, "AABBNV", "AABB_NV" );
			FindAndReplace( INOUT type_name, "_INT_64_", "_INT64_" );
		}

		for (auto field = values.begin(); field != values.end(); ++field)
		{
			if ( HasSubStringIC( field->name, type_name ) )
			{
				StringView	result = field->name;
				values.erase( field );
				return result;
			}
		}

		RETURN_ERR( "struct type enum is not found!" );
	}

/*
=================================================
	GenBookmarksForStruct
=================================================
*/
	bool Generator::GenBookmarksForStruct (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\nENABLE_ENUM_CHECKS();\nswitch ( header->sType )\n{\n";
		String	temp;

		auto	st_types = _enums.find( SearchableEnum{"VkStructureType"} );
		CHECK_ERR( st_types != _enums.end() );

		Array<EnumField>	enum_fields = st_types->data.fields;


		for (auto& info : _structs)
		{
			const bool	has_stype = _HasSType( info.data );

			if ( not has_stype or
				 info.data.name == "VkBaseInStructure" or
				 info.data.name == "VkBaseOutStructure" )
				continue;

			StringView	enum_name = _FindStructTypeEnum( info.data.name, INOUT enum_fields );

			CHECK_ERR( _GenBookmarks_AddStructResources( info.data, 0, 1, "value", OUT temp ));
		
			if ( temp.empty() )
			{
				enum_fields.push_back({ enum_name, "" });
				continue;
			}
		
			str << "\tcase " << enum_name << " : {\n";

			if ( info.data.fileIndex > 0 )
			{
				str  << "\t\t#ifdef "s << _fileData[info.data.fileIndex].macro << "\n";
				temp << "\t\t#endif\n";
			}

			str << "\t	" << info.data.name << " const&  value = *BitCast<" << info.data.name << " const *>( header );\n"
				<< temp
				<< "\t	break;\n"
				<< "\t}\n\n";
		}


		for (auto& field : enum_fields)
		{
			if ( not _IsNumber( field.value ) and field.name != "VK_STRUCTURE_TYPE_RANGE_SIZE" )
				continue;	// skip aliases

			str << "\tcase " << field.name << " : break;\n";
		}
	
		str << "}\nDISABLE_ENUM_CHECKS();\n";


		// store to file
		FileWStream		file{ output };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

}	// VTC
