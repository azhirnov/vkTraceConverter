// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "VkTraceCommon.h"

namespace VkHelpers {
#	include "Generated/VkStructTypes.h"
}

namespace VTC
{

/*
=================================================
	ForEachNextStruct
=================================================
*/
	template <typename FN>
	inline void ForEachNextStruct (const void *pNext, FN &&callback)
	{
		for (auto ptr = BitCast<VkBaseInStructure const*>( pNext );
			 ptr != null;
			 ptr = BitCast<VkBaseInStructure const*>( ptr->pNext ))
		{
			callback( ptr );
		}
	}
	
/*
=================================================
	FindVkStruct
=================================================
*/
	template <typename T>
	ND_ inline T const*  FindVkStruct (const void *pNext)
	{
		const VkStructureType	type = VkHelpers::TypeToEnum<T>::value;

		for (auto ptr = BitCast<VkBaseInStructure const*>( pNext );
			 ptr != null;
			 ptr = BitCast<VkBaseInStructure const*>( ptr->pNext ))
		{
			if ( ptr->sType == type )
				return BitCast<T const*>( ptr );
		}
		return null;
	}

}	// VTC
