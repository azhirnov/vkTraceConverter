// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	GenFuncErrorChecks
=================================================
*/
	bool Generator::GenFuncErrorChecks (const fs::path &output) const
	{
		String	str = "// auto-generated file\n\n";
		
		str << "ENABLE_ENUM_CHECKS();\n"
			<< "switch ( iter->packet_id )\n"
			<< "{\n";

		for (auto& packet : _packetIDs)
		{
			auto	func = _funcs.find( SearchableFunc{packet.vkFunc} );

			if ( func == _funcs.end() )
				continue;

			if ( func->data.result.type.size() == 1 and
				 func->data.result.type[0] == "VkResult" )
			{
				str << "\tcase " << packet.id << " : {\n"
					<< "\t	auto&  packet = iter.Cast< packet_" << packet.suffix << " >();\n"
					<< "\t	result = (packet.result == VK_SUCCESS);\n"
					<< "\t	break;\n"
					<< "\t}\n";
			}
			else
			{
				str << "\tcase " << packet.id << " : break;\n";
			}
		}
		
		str << "}\n"
			<< "DISABLE_ENUM_CHECKS();\n";


		// store to file
		FileWStream		file{ output };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

}	// VTC
