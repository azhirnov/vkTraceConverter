// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// All Resources Bookmarks
	//

	class AllResourcesBookmarks final : public IAnalyzer
	{
	// types
	public:
		struct Bookmark
		{
			TraceRange::Bookmark	pos;
			FrameID					frameId;
			PacketID				packetId;
		};

		struct ResourceInfo
		{
		// variables
			Deque<Bookmark>		bookmarks;
			String				name;			// TODO
			EResourceType		type		= VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT;
			ResourceID			id			= 0;
			uint				localIndex	= ~0u;
			
		// methods
			ResourceInfo () {}
			ResourceInfo (EResourceType type, ResourceID id) : type{type}, id{id} {}
		};

		using ResourceMap_t			= HashMap< ResourceID, ResourceInfo >;
		using ResourceTypeMap_t		= HashMap< EResourceType, ResourceMap_t >;
		using Resource_t			= std::tuple< EResourceType, ResourceID, ResourceInfo const* >;


	// variables
	private:
		ResourceTypeMap_t	_resources;


	// methods
	public:
		AllResourcesBookmarks ();

		//ND_ ResourceTypeMap_t const&	GetResourceGroups () const		{ return _resources; }

		ND_ ResourceMap_t const *	GetResourcesByType (EResourceType type) const;
		ND_ ResourceInfo const *	GetResource (EResourceType type, ResourceID id) const;
		ND_ ResourceInfo const *	GetResource (ResourceID id) const;

		bool GetResourcesInPos (TraceRange::Bookmark pos, OUT Array<Resource_t> &outResources) const;
		bool GetResourcesInPos (TraceRange::Bookmark pos, EResourceType type, OUT Array<Resource_t> &outResources) const;


	// IAnalyzer implementation
	public:
		void Process (const TraceRange::Iterator &) override {}

		void PostProcess () override;

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID) override;

		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }
	};


}	// VTC
