// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Analyzer/AllResourcesBookmarks.h"
#include "Converters/Utils/BasicTypesConverter.h"

namespace VTC
{

	//
	// Resource Remapper
	//

	struct ResRemapper
	{
	// variables
	private:
		AllResourcesBookmarks const*	_resBookmarks;


	// methods
	public:
		explicit ResRemapper (const AllResourcesBookmarks *rbm) : _resBookmarks{rbm}
		{}

		template <typename T>
		ND_ String  operator () (const T &resourceId) const
		{
			STATIC_ASSERT( std::is_pointer_v<T> or std::is_same_v<T, uint64_t> );

			if ( resourceId == 0 )
				return "~0u";

			auto*	res_info = _resBookmarks->GetResource( ResourceID(resourceId) );

			CHECK_ERR( res_info, "<error>" );
			CHECK_ERR( res_info->localIndex != ~0u, "<error>" );

			return IntToString( res_info->localIndex );
		}
	};


}	// VTC
