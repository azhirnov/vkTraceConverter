// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	_GenRawVulkanCalls_ProcessPacket
=================================================
*/
	bool Generator::_GenRawVulkanCalls_ProcessPacket (const PacketInfo &packet, OUT String &str) const
	{
		str.clear();

		auto	func_info = _funcs.find( SearchableFunc{packet.vkFunc} );
		CHECK_ERR( func_info != _funcs.end() );

		str	<< "\t\tauto const*  obj = iter.Cast< packet_" << packet.suffix << " *>();\n";
	
		String		call, after;

		const bool	returns_vkresult = (func_info->data.result.type.size() == 1 and func_info->data.result.type[0] == "VkResult");

		call
			<< (returns_vkresult ? "\t\tVK_CALL( obj->result );\n" : "")
			<< "\t\tresult << indent << \""
			<< (returns_vkresult ? "VK_CALL( " : "")
			<< (func_info->data.scope == EFuncScope::Device ? "app." : "") << packet.vkFunc << "( \\n\";\n";
		
		for (auto& arg : func_info->data.args)
		{
			CHECK_ERR( _GenStructToString_ProcessVar( arg.name, arg.type, "\t\t",
													  _GetFuncArgCounterName( packet.vkFunc, arg.name ), false,
													  INOUT call, INOUT str, INOUT after ));
			
			if ( &arg != &func_info->data.args.back() )
				call << "\t\tresult << \",\\n\";\n";
			else
				call << "\t\tresult << \" " << (returns_vkresult ? ")" : "") << ");\\n\";\n";
		}

		str << call << after;
		return true;
	}

/*
=================================================
	GenRawVulkanCalls
=================================================
*/
	bool Generator::GenRawVulkanCalls (const fs::path &output) const
	{
		String	str =	"// auto-generated file\n\n"
						"ENABLE_ENUM_CHECKS();\n"
						"switch ( iter->packet_id )\n"
						"{\n";
		String	temp;

		for (auto& packet : _packetIDs)
		{
			if ( packet.vkFunc.empty() or _skipPackets.find( packet.id ) != _skipPackets.end() )
			{
				str << "\tcase " << packet.id << " : break;\n";
			}
			else
			{
				str << "\tcase " << packet.id << " : {\n";

				CHECK_ERR( _GenRawVulkanCalls_ProcessPacket( packet, OUT temp ));

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

}	// VTC
