// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Utils/ResRemapper.h"
#include "Converters/Utils/BasicTypesConverter.h"

namespace VTC
{
	
/*
=================================================
	GetResource
=================================================
*/
	String  ResRemapper::GetResource (EResourceType type, ResourceID id) const
	{
		if ( id == 0 )
			return "~0u";

		auto*	res_info = _resBookmarks->GetResource( type, id, _currentPos );
		CHECK_ERR( res_info, "<error>" );

		if ( _useUniqueIndices )
		{
			CHECK_ERR( res_info->uniqueIndex != UMax, "<error>" );
			return IntToString( res_info->uniqueIndex );
		}
		else
		{
			CHECK_ERR( res_info->localIndex != UMax, "<error>" );
			return IntToString( res_info->localIndex );
		}
	}


}	// VTC
