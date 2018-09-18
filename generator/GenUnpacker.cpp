// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	_GenUnpacker_ProcessPacket
=================================================
*/
	bool Generator::_GenUnpacker_UnpackType (StringView parentName, StringView fieldName, ArrayView<StringView> typeParts,
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
				for (auto& field : st_info->data.fields) {
					if ( field.name == "sType" ) {
						has_stype = true;
						break;
					}
				}
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
			str << indent << "UnpackPointer( INOUT " << parentName << "->" << fieldName << ", header );\n";
		
			if ( st_info != _structs.end() )
			{
				if ( counterName.empty() )
				{
					if ( has_stype )
						str << indent << "UnpackStruct( PtrCast<VkBaseOutStructure>(" << parentName << "->" << fieldName << "), header );\n";
					else
						str << indent << "Unpack_" << st_info->data.name << "( PtrCast<" << st_info->data.name << ">(" << parentName << "->" << fieldName << "), header );\n";
				}
				else
				{
					str << indent << "for (uint i = 0; (" << parentName << "->" << fieldName << " != null) and (i < " << parentName << "->" << counterName << "); ++i) {\n";
				
					if ( has_stype )
						str << indent << "	UnpackStruct( PtrCast<VkBaseOutStructure>(" << parentName << "->" << fieldName << " + i), header );\n";
					else
						str << indent << "	Unpack_" << st_info->data.name << "( PtrCast<" << st_info->data.name << ">(" << parentName << "->" << fieldName << " + i), header );\n";
				
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
					<< indent << "	UnpackPointer( INOUT *" << parentName << "->" << fieldName << ", header );\n"
					<< indent << "}\n";
			}
			else
			{
				str << indent << "for (uint i = 0; (" << parentName << "->" << fieldName << " != null) and (i < " << parentName << "->" << counterName << "); ++i) {\n"
					<< indent << "	UnpackPointer( INOUT " << parentName << "->" << fieldName << "[i], header );\n"
					<< indent << "}\n";
			}
		}

		CHECK_ERR( num_pointers <= 2 );
		return true;
	}

/*
=================================================
	_GenUnpacker_ProcessPacket
=================================================
*/
	bool Generator::_GenUnpacker_ProcessPacket (const PacketInfo &packet, OUT String &str) const
	{
		str.clear();

		auto	func_info = _funcs.find( SearchableFunc{packet.vkFunc} );
		CHECK_ERR( func_info != _funcs.end() );

		str	<< "\t\t	packet_" << packet.suffix << "*  packet = BitCast<packet_" << packet.suffix << "*>(header->pBody);\n"
			<< "\t\t	packet->header = header;\n";


		// special cases
		if ( packet.vkFunc == "vkMapMemory" )
		{
			str << "\t\t	UnpackPointer( INOUT packet->ppData, header );\n";
		}
		else
		if ( packet.vkFunc == "vkUnmapMemory" )
		{
			str << "\t\t	UnpackPointer( INOUT packet->pData, header );\n";
		}
		else
		if ( packet.vkFunc == "vkFlushMappedMemoryRanges" or
			 packet.vkFunc == "vkInvalidateMappedMemoryRanges" )
		{
			str << "\t\t	UnpackPointer( INOUT packet->pMemoryRanges, header );\n";
			str << "\t\t	UnpackPointer( INOUT packet->ppData, header );\n";
			str << "\t\t	for (uint i = 0; (packet->ppData != null) and (i < packet->memoryRangeCount); ++i) {\n"
				<< "\t\t		UnpackPointer( INOUT packet->ppData[i], header );\n"
				<< "\t\t	}\n";
		}
		else

		// unpack arguments
		for (auto& arg : func_info->data.args)
		{
			CHECK_ERR( _GenUnpacker_UnpackType( "packet", arg.name, arg.type,
												_GetFuncArgCounterName( packet.vkFunc, arg.name ), "\t\t\t",
												INOUT str ));
		}

		return true;
	}

/*
=================================================
	_GenUnpacker_ForFunc
=================================================
*/
	bool Generator::_GenUnpacker_ForFunc (OUT String &str) const
	{
		String	temp;

		str << "static void UnpackPacket (vktrace_trace_packet_header *header)\n"
			<< "{\n"
			<< "	if ( not header ) return;\n"
			<< "	ENABLE_ENUM_CHECKS();\n"
			<< "	switch ( header->packet_id )\n"
			<< "	{\n";
	
		for (auto& packet : _packetIDs)
		{
			if ( packet.id == "VKTRACE_TPI_VK_vkApiVersion" )
			{
				str << "\t\tcase " << packet.id << " : {\n"
					<< "\t\t	packet_vkApiVersion* packet = BitCast<packet_vkApiVersion*>(header->pBody);\n"
					<< "\t\t	packet->header = header;\n"
					<< "\t\t	break;\n"
					<< "\t\t}\n";
			}
			else
			if ( packet.vkFunc.empty() )
			{
				str << "\t\tcase " << packet.id << " : break;\n";
			}
			else
			{
				str << "\t\tcase " << packet.id << " : {\n";

				CHECK_ERR( _GenUnpacker_ProcessPacket( packet, OUT temp ));

				str << temp
					<< "\t\t	break;\n"
					<< "\t\t}\n\n";
			}
		}

		str << "	}\n"
			<< "	DISABLE_ENUM_CHECKS();\n"
			<< "}\n\n";

		return true;
	}

/*
=================================================
	_GenUnpacker_ProcessStruct
=================================================
*/
	bool Generator::_GenUnpacker_ProcessStruct (const VkStructInfo &info, OUT String &str) const
	{
		str.clear();
		for (auto& field : info.fields)
		{
			if ( field.name == "pNext" )
				continue;

			CHECK_ERR( _GenUnpacker_UnpackType( "value", field.name, field.type,
												_GetStructFieldCounterName( info.name, field.name ), "\t\t\t",
												INOUT str ));
		}

		return true;
	}

/*
=================================================
	_GenUnpacker_ProcessStruct2
=================================================
*/
	bool Generator::_GenUnpacker_ProcessStruct2 (const VkStructInfo &info, OUT String &str) const
	{
		str.clear();
		str << "static void Unpack_" << info.name << " (" << info.name << " *ptr, vktrace_trace_packet_header *header)\n"
			<< "{\n"
			<< "	if ( ptr == null ) return;\n";

		for (auto& field : info.fields)
		{
			CHECK_ERR( _GenUnpacker_UnpackType( "ptr", field.name, field.type,
												_GetStructFieldCounterName( info.name, field.name ), "\t",
												INOUT str ));
		}
		
		str << "}\n\n";

		return true;
	}

/*
=================================================
	_GenUnpacker_ForStruct
=================================================
*/
	bool Generator::_GenUnpacker_ForStruct (OUT String &str) const
	{
		String	str0, str1, str2;

		str0 << "static void UnpackStruct (VkBaseOutStructure *, vktrace_trace_packet_header *);\n";

		str1 << "static void UnpackStruct (VkBaseOutStructure *ptr, vktrace_trace_packet_header *header)\n"
			<< "{\n"
			<< "	if ( ptr == null ) return;\n"
			<< "	UnpackPointer( INOUT ptr->pNext, header );\n"
			<< "	UnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pNext), header );\n\n"
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

			bool	has_stype = false;

			for (auto& field : info.data.fields)
			{
				if ( field.name == "sType" ) {
					has_stype = true;
					break;
				}
			}

			if ( info.data.name == "VkBaseInStructure" or
				 info.data.name == "VkBaseOutStructure" )
				continue;

			if ( not has_stype )
			{
				str0 << "static void Unpack_" << info.data.name << " (" << info.data.name << " *, vktrace_trace_packet_header *);\n";

				CHECK_ERR( _GenUnpacker_ProcessStruct2( info.data, OUT temp ));
			
				if ( not temp.empty() and info.data.fileIndex > 0 )
				{
					str2 << "#ifdef "s << _fileData[info.data.fileIndex].macro << "\n" << temp << "#endif\n";
				}else
					str2 << temp;

				continue;
			}


			StringView	enum_name = _FindStructTypeEnum( info.data.name, INOUT enum_fields );

			CHECK_ERR( _GenUnpacker_ProcessStruct( info.data, OUT temp ));
		
			if ( temp.empty() )
			{
				enum_fields.push_back({ enum_name, "1" });
				continue;
			}
		
			str1 << "\t\tcase " << enum_name << " : {\n";

			if ( info.data.fileIndex > 0 )
			{
				str1 << "\t\t\t#ifdef "s << _fileData[info.data.fileIndex].macro << "\n";
				temp << "\t\t\t#endif\n";
			}

			str1 << "\t\t\t" << info.data.name << "*  value = BitCast<" << info.data.name << "*>( ptr );\n"
				<< temp
				<< "\t\t	break;\n"
				<< "\t\t}\n\n";
		}


		for (auto& field : enum_fields)
		{
			if ( not _IsNumber( field.value ) and field.name != "VK_STRUCTURE_TYPE_RANGE_SIZE" )
				continue;	// skip aliases

			str1 << "\tcase " << field.name << " : break;\n";
		}

		str1 << "	}\n"
			<< "	DISABLE_ENUM_CHECKS();\n"
			<< "}\n";


		str << str0 << "//-----------------------------------------------------------------------------\n\n"
			<< str1 << "//-----------------------------------------------------------------------------\n\n"
			<< str2 << "//-----------------------------------------------------------------------------\n\n";

		return true;
	}

/*
=================================================
	GenUnpacker
=================================================
*/
	bool Generator::GenUnpacker (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\n";
		String	str1, str2;

		CHECK_ERR( _GenUnpacker_ForStruct( OUT str1 ));
		CHECK_ERR( _GenUnpacker_ForFunc( OUT str2 ));


		// store to file
		HddWFile	file{ output };
		CHECK_ERR( file.IsOpen() );
	
		CHECK_ERR( file.Write( StringView(str) ));
		CHECK_ERR( file.Write( StringView(str1) ));
		CHECK_ERR( file.Write( StringView(str2) ));

		return true;
	}

}	// VTC
