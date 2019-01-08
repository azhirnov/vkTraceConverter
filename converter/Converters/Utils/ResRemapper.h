// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/Default/AllResourcesBookmarks.h"

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
		TraceRange::Bookmark			_currentPos;
		const bool						_useUniqueIndices;


	// methods
	public:
		ResRemapper (const AllResourcesBookmarks *rbm, bool uniqueIndices) :
			_resBookmarks{rbm}, _useUniqueIndices{uniqueIndices}
		{}

		void SetCurrentPos (const TraceRange::Bookmark &pos)
		{
			_currentPos = pos;
		}


		template <typename T>
		ND_ String  operator () (EResourceType type, const T &resourceId) const
		{
			STATIC_ASSERT( IsPointer<T> or IsSameTypes<T, uint64_t> );

			return GetResource( type, ResourceID(resourceId) );
		}


		ND_ String  GetResource (EResourceType type, ResourceID id) const;
	};


}	// VTC
