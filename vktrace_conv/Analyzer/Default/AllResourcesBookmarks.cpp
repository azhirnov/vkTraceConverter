// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/AllResourcesBookmarks.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	AllResourcesBookmarks::AllResourcesBookmarks ()
	{
	}
		
/*
=================================================
	PostProcess
=================================================
*/
	void AllResourcesBookmarks::PostProcess ()
	{
		// set local indices
		for (auto& res_type : _resources)
		{
			uint64_t	unique_index	= 0;
			uint64_t	local_index		= 0;

			for (auto& res : res_type.second)
			{
			#if 0
				// unique indices
				for (auto& inst : res.second) {
					inst.uniqueIndex = unique_index++;
					inst.localIndex  = local_index++;
				}
			#else
				// minimize memory usage
				for (auto& inst : res.second) {
					inst.uniqueIndex = unique_index++;
					inst.localIndex  = local_index;
				}
				++local_index;
			#endif
			}
		}
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void AllResourcesBookmarks::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		if ( id == 0 )
			return;

		auto&	res_type = _resources[type];

		ResourceMap_t::iterator		res_iter;
		CHECK_ERR( res_type.AddResourceUsage( OUT res_iter, pos, id, op ), void());

		auto&	info = res_iter->second.back();

		info.type	= type;
		info.id		= id;

		if ( pos->packet_id == VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT )
		{
			info.name = pos.Cast< packet_vkDebugMarkerSetObjectNameEXT >().pNameInfo->pObjectName;
		}
	}
	
/*
=================================================
	GetResourcesByType
=================================================
*/
	AllResourcesBookmarks::ResourceMap_t const*  AllResourcesBookmarks::GetResourcesByType (EResourceType type) const
	{
		auto	res_type = _resources.find( type );

		if ( res_type != _resources.end() )
		{
			return &res_type->second;
		}
		return null;
	}
	
/*
=================================================
	GetResourceCountByType
=================================================
*/
	uint64_t  AllResourcesBookmarks::GetResourceCountByType (EResourceType type) const
	{
		auto	res_type = _resources.find( type );

		if ( res_type != _resources.end() )
		{
			auto&	arr = (--res_type->second.end())->second;

			if ( arr.empty() )
				return 0;

			return arr.back().localIndex+1;
		}
		return 0;
	}
	
/*
=================================================
	GetUniqueResourceCountByType
=================================================
*/
	uint64_t  AllResourcesBookmarks::GetUniqueResourceCountByType (EResourceType type) const
	{
		auto	res_type = _resources.find( type );

		if ( res_type != _resources.end() )
		{
			auto&	arr = (--res_type->second.end())->second;

			if ( arr.empty() )
				return 0;

			return arr.back().uniqueIndex+1;
		}
		return 0;
	}

/*
=================================================
	GetResource
=================================================
*/
	AllResourcesBookmarks::ResourceInfo_t const*  AllResourcesBookmarks::GetResource (EResourceType type, ResourceID id, TraceRange::Bookmark pos) const
	{
		auto	res_type = _resources.find( type );

		if ( res_type != _resources.end() )
		{
			return res_type->second.FindIn( id, pos );	// returns 'null' if not found
		}
		return null;
	}
	
/*
=================================================
	GetResource
=================================================
*/
	AllResourcesBookmarks::ResourceInfo_t const*  AllResourcesBookmarks::GetResource (ResourceID id, TraceRange::Bookmark pos) const
	{
		for (auto& res_type : _resources)
		{
			auto	iter = res_type.second.find( id );
			
			if ( iter == res_type.second.end() )
				continue;

			return res_type.second.FindIn( iter, pos );
		}
		return null;
	}
	
/*
=================================================
	GetResourcesInPos
=================================================
*
	bool AllResourcesBookmarks::GetResourcesInPos (TraceRange::Bookmark pos, OUT Array<Resource_t> &outResources) const
	{
		outResources.clear();

		PacketID	packet_id = 0;

		for (auto& res_type : _resources)
		{
			for (auto& res : res_type.second)
			{
				auto	found = std::lower_bound( res.second.bookmarks.begin(), res.second.bookmarks.end(), pos,
													[pos] (auto& lhs, auto& rhs) { return lhs.pos < rhs.pos; } );

				if ( found != res.second.bookmarks.end() )
				{
					ASSERT( found->pos == pos );

					outResources.push_back({ res_type.first, res.first, &res.second });

					if ( packet_id != 0 )
					{
						ASSERT( packet_id == found->packetId );
					}
					else
						packet_id = found->packetId;
				}
			}
		}
		return true;
	}
	
/*
=================================================
	GetResourcesInPos
=================================================
*
	bool AllResourcesBookmarks::GetResourcesInPos (TraceRange::Bookmark pos, EResourceType type, OUT Array<Resource_t> &outResources) const
	{
		outResources.clear();

		PacketID	packet_id	= 0;
		auto		res_type	= _resources.find( type );

		if ( res_type == _resources.end() )
			return false;

		for (auto& res : res_type->second)
		{
			auto	found = std::lower_bound( res.second.bookmarks.begin(), res.second.bookmarks.end(), pos,
												[pos] (auto& lhs, auto& rhs) { return lhs.pos < rhs.pos; } );

			if ( found != res.second.bookmarks.end() )
			{
				ASSERT( found->pos == pos );

				outResources.push_back({ res_type->first, res.first, &res.second });

				if ( packet_id != 0 )
				{
					ASSERT( packet_id == found->packetId );
				}
				else
					packet_id = found->packetId;
			}
		}
		return true;
	}
	*/

}	// VTC
