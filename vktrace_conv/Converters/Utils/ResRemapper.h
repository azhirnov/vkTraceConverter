// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

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


	// methods
	public:
		explicit ResRemapper (const AllResourcesBookmarks *rbm) : _resBookmarks{rbm}
		{}

		void SetCurrentPos (const TraceRange::Bookmark &pos)
		{
			_currentPos = pos;
		}


		template <typename T>
		ND_ String  operator () (EResourceType type, const T &resourceId) const
		{
			STATIC_ASSERT( std::is_pointer_v<T> or std::is_same_v<T, uint64_t> );

			return GetResource( type, ResourceID(resourceId) );
		}


		ND_ String  GetResource (EResourceType type, ResourceID id) const;
	};


}	// VTC
