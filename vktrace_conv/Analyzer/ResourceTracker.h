// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "VkTraceCommon.h"

namespace VTC
{

	//
	// Default Bookmark Type
	//
	struct DefaultBookmark
	{
		bool operator == (const DefaultBookmark &) const  { return true; }
	};



	//
	// Resource Tracker
	//

	template <typename ItemType, typename BookmarkType = DefaultBookmark>
	struct ResourceTracker
	{
	// types
	private:
		struct Bookmark : BookmarkType
		{
			TraceRange::Bookmark	pos;
			FrameID					frameId;
			PacketID				packetId;

			ND_ bool operator == (const Bookmark &rhs) const {
				return	BookmarkType::operator == (rhs)	and
						pos			== rhs.pos			and
						frameId		== rhs.frameId		and
						packetId	== rhs.packetId;
			}
		};

		struct Item : ItemType
		{
			Deque<Bookmark>		bookmarks;
			bool				destroyed	= false;
		};


		using ItemArray_t		= Deque< Item >;
		using ItemMap_t			= HashMap< ResourceID, ItemArray_t >;

	public:
		using BaseItem_t		= ItemType;
		using BaseBookmark_t	= BookmarkType;
		
		using Item_t			= Item;
		using Bookmark_t		= Bookmark;

		using iterator			= typename ItemMap_t::iterator;
		using const_iterator	= typename ItemMap_t::const_iterator;


	// variables
	private:
		ItemMap_t	_items;


	// methods
	public:
		ResourceTracker () {}

		ND_ auto	begin ()				const	{ return _items.begin(); }
		ND_ auto	begin ()						{ return _items.begin(); }

		ND_ auto	end ()					const	{ return _items.end(); }
		ND_ auto	end ()							{ return _items.end(); }

		//ND_ size_t	size ()				const	{ return _items.size(); }
		ND_ bool	empty ()				const	{ return _items.empty(); }

		ND_ auto	find (ResourceID id)	const	{ return _items.find( id ); }
		ND_ auto	find (ResourceID id)			{ return _items.find( id ); }

		
		ND_ Item_t const*	FindIn (const_iterator item, TraceRange::Bookmark pos, bool strict = true) const;
		ND_ Item_t *		FindIn (iterator item, TraceRange::Bookmark pos, bool strict = true);
		
		ND_ Item_t const*	FindIn (const_iterator item, const TraceRange::Iterator &pos, bool strict = true) const;
		ND_ Item_t *		FindIn (iterator item, const TraceRange::Iterator &pos, bool strict = true);

		ND_ Item_t const*	FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict = true) const;
		ND_ Item_t *		FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict = true);
		
		ND_ Item_t const*	FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict = true) const;
		ND_ Item_t *		FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict = true);

		
		bool	AddResourceUsage (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId, EResOp op)
		{
			iterator	iter;
			return AddResourceUsage( OUT iter, pos, id, frameId, op );
		}

		bool	AddResourceUsage (OUT iterator &iter, const TraceRange::Iterator &pos, ResourceID id, FrameID frameId, EResOp op);
	};


	
/*
=================================================
	AddResourceUsage
=================================================
*/
	template <typename IT, typename BT>
	inline bool  ResourceTracker<IT,BT>::AddResourceUsage (OUT iterator &iter, const TraceRange::Iterator &pos, ResourceID id, FrameID frameId, EResOp op)
	{
		CHECK_ERR( id != 0 );

		iter = _items.find( id );

		if ( iter == _items.end() )
		{
			CHECK_ERR( op == EResOp::Construct );
			iter = _items.insert({ id, ItemArray_t{} }).first;
		}

		CHECK_ERR( op == EResOp::Construct or not iter->second.empty() );

		if ( op == EResOp::Construct )
		{
			CHECK_ERR( iter->second.empty() or iter->second.back().destroyed );

			iter->second.push_back( Item{} );
		}
		else
		if ( op == EResOp::Destruct )
		{
			iter->second.back().destroyed = true;
		}
		else
		{
			CHECK_ERR( not iter->second.back().destroyed );
		}
			
		Bookmark	bm;
		bm.packetId	= PacketID(pos->packet_id);
		bm.frameId	= frameId;
		bm.pos		= pos.GetBookmark();

		auto&	bookmarks = iter->second.back().bookmarks;

		if ( bookmarks.empty() or not (bookmarks.back() == bm) )
		{
			ASSERT( bookmarks.empty() or bookmarks.back().pos <= bm.pos );

			bookmarks.push_back( std::move(bm) );
		}
		return true;
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t const*
		ResourceTracker<IT,BT>::FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict) const
	{
		auto	iter = _items.find( id );

		if ( iter == _items.end() )
			return null;

		return FindIn( iter, pos, strict );
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t const*
		ResourceTracker<IT,BT>::FindIn (const_iterator iter, TraceRange::Bookmark pos, bool strict) const
	{
		for (auto& res : iter->second)
		{
			ASSERT( not res.bookmarks.empty() );

			if ( strict								and
				 pos >= res.bookmarks.front().pos	and
				 pos <= res.bookmarks.back().pos )
			{
				return &res;
			}
			
			if ( not strict and pos <= res.bookmarks.back().pos )
				return &res;
		}
		
		if ( not iter->second.empty() and not iter->second.back().destroyed )
		{
			return &iter->second.back();
		}

		ASSERT(false);	// out of range
		return null;
	}

/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t *
		ResourceTracker<IT,BT>::FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict)
	{
		return const_cast<Item_t *>( static_cast< ResourceTracker<IT,BT> const *>(this)->FindIn( id, pos, strict ));
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t *
		ResourceTracker<IT,BT>::FindIn (iterator item, TraceRange::Bookmark pos, bool strict)
	{
		return const_cast<Item_t *>( static_cast< ResourceTracker<IT,BT> const *>(this)->FindIn( item, pos, strict ));
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t const*
		ResourceTracker<IT,BT>::FindIn (const_iterator item, const TraceRange::Iterator &pos, bool strict) const
	{
		return FindIn( item, pos.GetBookmark(), strict );
	}
	
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t *
		ResourceTracker<IT,BT>::FindIn (iterator item, const TraceRange::Iterator &pos, bool strict)
	{
		return FindIn( item, pos.GetBookmark(), strict );
	}
	
/*
=================================================
	FindIn
=================================================
*/	
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t const*
		ResourceTracker<IT,BT>::FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict) const
	{
		return FindIn( id, pos.GetBookmark(), strict );
	}
	
	template <typename IT, typename BT>
	inline typename ResourceTracker<IT,BT>::Item_t *
		ResourceTracker<IT,BT>::FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict)
	{
		return FindIn( id, pos.GetBookmark(), strict );
	}

}	// VTC
