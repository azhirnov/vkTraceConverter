// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Analyzer/AllResourcesBookmarks.h"

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
			uint	counter = 0;

			for (auto& res : res_type.second)
			{
				res.second.localIndex = counter++;
			}
		}
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void AllResourcesBookmarks::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID frameId)
	{
		if ( id == 0 )
			return;

		auto&	res_type = _resources[type];
		auto	iter	 = res_type.find( id );

		if ( iter == res_type.end() )
		{
			iter = res_type.insert({ id, {type, id} }).first;
		}

		if ( type != VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT and
			 pos->packet_id == VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT )
		{
			iter->second.name = pos.Cast< packet_vkDebugMarkerSetObjectNameEXT >().pNameInfo->pObjectName;
		}

		iter->second.bookmarks.push_back({ pos.GetBookmark(), frameId, PacketID(pos->packet_id) });
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
	GetResource
=================================================
*/
	AllResourcesBookmarks::ResourceInfo const*  AllResourcesBookmarks::GetResource (EResourceType type, ResourceID id) const
	{
		auto	res_type = _resources.find( type );

		if ( res_type != _resources.end() )
		{
			auto	iter = res_type->second.find( id );

			if ( iter != res_type->second.end() )
				return &iter->second;
		}
		return null;
	}
	
/*
=================================================
	GetResource
=================================================
*/
	AllResourcesBookmarks::ResourceInfo const*  AllResourcesBookmarks::GetResource (ResourceID id) const
	{
		for (auto& res_type : _resources)
		{
			auto	iter = res_type.second.find( id );

			if ( iter != res_type.second.end() )
				return &iter->second;
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
