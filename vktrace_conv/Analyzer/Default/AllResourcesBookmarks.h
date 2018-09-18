// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// All Resources Bookmarks
	//

	class AllResourcesBookmarks final : public IAnalyzer
	{
	// types
	private:
		struct ResourceInfo
		{
			String				name;
			EResourceType		type		= VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT;
			ResourceID			id			= 0;
			uint64_t			localIndex	= ~0ull;
			uint64_t			uniqueIndex	= ~0ull;
		};

	public:
		using ResourceMap_t			= ResourceTracker< ResourceInfo >;
		using ResourceTypeMap_t		= HashMap< EResourceType, ResourceMap_t >;
		using ResourceInfo_t		= typename ResourceMap_t::Item_t;
		using Resource_t			= std::tuple< EResourceType, ResourceID, ResourceInfo_t const* >;


	// variables
	private:
		ResourceTypeMap_t	_resources;


	// methods
	public:
		AllResourcesBookmarks ();

		//ND_ ResourceTypeMap_t const&	GetResourceGroups () const		{ return _resources; }
		
		ND_ uint64_t  GetResourceCountByType (EResourceType type) const;
		ND_ uint64_t  GetUniqueResourceCountByType (EResourceType type) const;
		//ND_ uint64_t  GetResourceCountByType (EResourceType type, ResourceID device) const;	// TODO

		ND_ ResourceMap_t const *	GetResourcesByType (EResourceType type) const;
		ND_ ResourceInfo_t const *	GetResource (EResourceType type, ResourceID id, TraceRange::Bookmark pos) const;
		ND_ ResourceInfo_t const *	GetResource (ResourceID id, TraceRange::Bookmark pos) const;

		bool GetResourcesInPos (TraceRange::Bookmark pos, OUT Array<Resource_t> &outResources) const;
		bool GetResourcesInPos (TraceRange::Bookmark pos, EResourceType type, OUT Array<Resource_t> &outResources) const;


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override {}

		void Process (const TraceRange::Iterator &) override {}

		void PostProcess () override;

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;

		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }
	};


}	// VTC
