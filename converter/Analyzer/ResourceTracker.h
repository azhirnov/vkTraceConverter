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

	template <typename ItemType, typename BookmarkType = DefaultBookmark, bool UseBookmarkArray = false>
	struct ResourceTracker
	{
	// types
	private:
		struct Bookmark : BookmarkType
		{
			TraceRange::Bookmark	pos;
			PacketID				packetId;

			ND_ bool operator == (const Bookmark &rhs) const {
				return	BookmarkType::operator == (rhs)	and
						pos			== rhs.pos			and
						packetId	== rhs.packetId;
			}
		};


		struct ItemWithBookmarkArray : ItemType
		{
		// variables
			Deque<Bookmark>		bookmarks;
			bool				destroyed	= false;

		// methods
			ItemWithBookmarkArray () {}
			
			void AddBookmark (Bookmark &&bm);

			ND_ Bookmark const&		FirstBookmark ()	const	{ return bookmarks.front(); }
			ND_ Bookmark const&		LastBookmark ()		const	{ return bookmarks.back(); }
		};


		struct ItemWithBookmarkRange : ItemType
		{
		// variables
			Bookmark			firstBookmark;
			Bookmark			lastBookmark;
			bool				destroyed	= false;

		// methods
			ItemWithBookmarkRange () {}

			void AddBookmark (Bookmark &&bm);

			ND_ Bookmark const&		FirstBookmark ()	const	{ return firstBookmark; }
			ND_ Bookmark const&		LastBookmark ()		const	{ return lastBookmark; }
		};

		using Item				= Conditional< UseBookmarkArray, ItemWithBookmarkArray, ItemWithBookmarkRange >;
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

		ND_ bool	empty ()				const	{ return _items.empty(); }

		ND_ auto	find (ResourceID id)	const	{ return _items.find( id ); }
		ND_ auto	find (ResourceID id)			{ return _items.find( id ); }

			void	clear ()						{ _items.clear(); }

		
		ND_ Item_t const*	FindIn (const_iterator item, TraceRange::Bookmark pos, bool strict = true) const;
		ND_ Item_t *		FindIn (iterator item, TraceRange::Bookmark pos, bool strict = true);
		
		ND_ Item_t const*	FindIn (const_iterator item, const TraceRange::Iterator &pos, bool strict = true) const;
		ND_ Item_t *		FindIn (iterator item, const TraceRange::Iterator &pos, bool strict = true);

		ND_ Item_t const*	FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict = true) const;
		ND_ Item_t *		FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict = true);
		
		ND_ Item_t const*	FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict = true) const;
		ND_ Item_t *		FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict = true);

		
		bool	AddResourceUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
		{
			iterator	iter;
			return AddResourceUsage( OUT iter, pos, id, op );
		}

		bool	AddResourceUsage (OUT iterator &iter, const TraceRange::Iterator &pos, ResourceID id, EResOp op);
	};


	
	
/*
=================================================
	AddBookmark
=================================================
*/
	template <typename IT, typename BT, bool A>
	inline void ResourceTracker<IT,BT,A>::ItemWithBookmarkArray::AddBookmark (Bookmark &&bm)
	{
		if ( bookmarks.empty() or not (bookmarks.back() == bm) )
		{
			ASSERT( bookmarks.empty() or bookmarks.back().pos <= bm.pos );

			bookmarks.push_back( std::move(bm) );
		}
	}
	
/*
=================================================
	AddBookmark
=================================================
*/
	template <typename IT, typename BT, bool A>
	inline void ResourceTracker<IT,BT,A>::ItemWithBookmarkRange::AddBookmark (Bookmark &&bm)
	{
		if ( firstBookmark.pos != TraceRange::Bookmark() )
		{
			ASSERT( bm.pos >= lastBookmark.pos );

			lastBookmark = std::move(bm);
		}
		else
		{
			firstBookmark = (lastBookmark = std::move(bm));
		}
	}
//-----------------------------------------------------------------------------



/*
=================================================
	AddResourceUsage
=================================================
*/
	template <typename IT, typename BT, bool A>
	inline bool  ResourceTracker<IT,BT,A>::AddResourceUsage (OUT iterator &iter, const TraceRange::Iterator &pos, ResourceID id, EResOp op)
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
		bm.pos		= pos.GetBookmark();

		iter->second.back().AddBookmark( std::move(bm) );
		return true;
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t const*
		ResourceTracker<IT,BT,A>::FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict) const
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
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t const*
		ResourceTracker<IT,BT,A>::FindIn (const_iterator iter, TraceRange::Bookmark pos, bool strict) const
	{
		for (auto& res : iter->second)
		{
			if ( strict							and
				 pos >= res.FirstBookmark().pos	and
				 pos <= res.LastBookmark().pos )
			{
				return &res;
			}
			
			if ( not strict and pos <= res.LastBookmark().pos )
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
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t *
		ResourceTracker<IT,BT,A>::FindIn (ResourceID id, TraceRange::Bookmark pos, bool strict)
	{
		return const_cast<Item_t *>( static_cast< ResourceTracker<IT,BT,A> const *>(this)->FindIn( id, pos, strict ));
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t *
		ResourceTracker<IT,BT,A>::FindIn (iterator item, TraceRange::Bookmark pos, bool strict)
	{
		return const_cast<Item_t *>( static_cast< ResourceTracker<IT,BT,A> const *>(this)->FindIn( item, pos, strict ));
	}
	
/*
=================================================
	FindIn
=================================================
*/
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t const*
		ResourceTracker<IT,BT,A>::FindIn (const_iterator item, const TraceRange::Iterator &pos, bool strict) const
	{
		return FindIn( item, pos.GetBookmark(), strict );
	}
	
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t *
		ResourceTracker<IT,BT,A>::FindIn (iterator item, const TraceRange::Iterator &pos, bool strict)
	{
		return FindIn( item, pos.GetBookmark(), strict );
	}
	
/*
=================================================
	FindIn
=================================================
*/	
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t const*
		ResourceTracker<IT,BT,A>::FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict) const
	{
		return FindIn( id, pos.GetBookmark(), strict );
	}
	
	template <typename IT, typename BT, bool A>
	inline typename ResourceTracker<IT,BT,A>::Item_t *
		ResourceTracker<IT,BT,A>::FindIn (ResourceID id, const TraceRange::Iterator &pos, bool strict)
	{
		return FindIn( id, pos.GetBookmark(), strict );
	}

}	// VTC
