// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/GraphViz/GraphVizConverter.h"
#include "Converters/Utils/BasicTypesConverter.h"
#include "stl/include/Color.h"

namespace VTC
{
	using QueueExecutionStart			= SynchronizationsAnalyzer::QueueExecutionStart;
	using QueueExecutionFinish			= SynchronizationsAnalyzer::QueueExecutionFinish;
	using QueueFenceSignal				= SynchronizationsAnalyzer::QueueFenceSignal;
	using QueueWaitIdle					= SynchronizationsAnalyzer::QueueWaitIdle;
	using QueueBookmark					= SynchronizationsAnalyzer::QueueBookmark_t;
	using HostWaitForFences				= SynchronizationsAnalyzer::HostWaitForFences;
	using HostResetFences				= SynchronizationsAnalyzer::HostResetFences;
	using HostQueueSubmit				= SynchronizationsAnalyzer::HostQueueSubmit;
	using HostWaitForQueueIdle			= SynchronizationsAnalyzer::HostWaitForQueueIdle;
	using HostAcquireNextImage			= SynchronizationsAnalyzer::HostAcquireNextImage;
	using HostWaitForDeviceIdle			= SynchronizationsAnalyzer::HostWaitForDeviceIdle;
	using SwapchainAcquireImage			= SynchronizationsAnalyzer::SwapchainAcquireImage;
	using SwapchainPresent				= SynchronizationsAnalyzer::SwapchainPresent;
	using UID							= SynchronizationsAnalyzer::UID;	
	

	//
	// GraphData
	//

	struct GraphData
	{
	// types
		enum class EScope {
			ApiCallArg,			// one of argument in function call
			ApiCall,			// vkCmdPipelineBarrier, vkCmdWaitEvents, ...
			RenderPass,
			CommandBuffer,
			CommandBufferBatch,
			QueueCmd,
			Queue,
			HostCmd,
			HostThread,
			Frame,
			Unknown,
			_Count
		};

		enum class EFlags {
			None		= 0,
			Sync		= 1 << 0,	// connection of 2 sync nodes marked with red color
			PartOfGroup	= 1 << 1,	// connection will be to group boundaries instead of node
			Filled		= 1 << 2,
		};

		struct NodeStyle {
			String		label;
			uint		fontSize	= 0;
			RGBA8u		bgColor		= HtmlColor::White;
			RGBA8u		labelColor	= HtmlColor::Black;
			EFlags		flags		= EFlags::Filled;
		};

		struct NodeInfo {
			String		name;
			NodeStyle	style;
			EScope		scope		= EScope::Unknown;
			UID			graphUID	= 0;
		};

		using NodeMap_t		= HashMap< UID, NodeInfo >;
		using Connections_t	= HashSet<Pair< UID, UID >>;


	// variables
		NodeMap_t		_nodeMap;
		Connections_t	_connections;


	// methods
		void AddNode (UID uid, const String &name, EScope scope, UID graphUID, const NodeStyle &style);
		void AddConnection (UID from, UID to);

		ND_ String  ToString ();

	private:
		ND_ String  _NodeStyleToString (const NodeStyle &style) const;
		ND_ String  _GraphStyleToString (StringView indent, const NodeStyle &style) const;
	};
	

	FG_BIT_OPERATORS( GraphData::EFlags );

/*
=================================================
	AddNode
=================================================
*/
	void GraphData::AddNode (UID uid, const String &name, EScope scope, UID graphUID, const NodeStyle &style)
	{
		CHECK( _nodeMap.insert({ uid, NodeInfo{name, style, scope, graphUID} }).second );
	}
		
/*
=================================================
	AddConnection
=================================================
*/
	void GraphData::AddConnection (UID from, UID to)
	{
		_connections.insert({ from, to });
	}
	
/*
=================================================
	ColToStr
=================================================
*/
	ND_ inline String  ColToStr (RGBA8u col)
	{
		uint	val = (uint(col.b) << 16) | (uint(col.g) << 8) | uint(col.r);
		String	str = ToString<16>( val );

		for (; str.length() < 6;) {
			str.insert( str.begin(), '0' );
		}
		return str;
	}
	
/*
=================================================
	ToString
=================================================
*/
	String  GraphData::ToString ()
	{
		HashMap<UID, String>	subgraphs[2];
		NodeStyle				graph_style;

		graph_style.bgColor		= HtmlColor::DarkGray;
		graph_style.label		= "queue";
		graph_style.labelColor	= HtmlColor::Yellow;

		String	src;
		String	deps;

		src	<< "digraph SynchGraph {\n"
			<< "	rankdir = LR;\n"
			<< "	bgcolor = black;\n"
			<< "	node [shape=rectangle, fontname=\"helvetica\", layer=all, penwidth=0.0];\n"
			<< "	edge [fontname=\"helvetica\", fontsize=8, fontcolor=white, layer=all];\n"	//, samehead=true, sametail=true]\n"
			//<< "	concentrate=true;\n"
			<< "	compound=true;\n\n";
		
		// add unknown nodes
		for (auto& con : _connections)
		{
			auto	from	= _nodeMap.find( con.first );
			auto	to		= _nodeMap.find( con.second );

			// TODO: remove
			if ( from == _nodeMap.end() ) {
				AddNode( con.first, "unk"s << FG::ToString<16>( con.first ), EScope::HostCmd, 0, {} );
			}
			if ( to == _nodeMap.end() ) {
				AddNode( con.second, "unk"s << FG::ToString<16>( con.second ), EScope::HostCmd, 0, {} );
			}
		}

		for (auto scope = EScope::ApiCallArg; scope < EScope::_Count; scope = EScope(uint(scope) + 1))
		{
			auto&	src_graph = subgraphs[uint(scope)&1];
			auto&	dst_graph = subgraphs[(uint(scope)+1)&1];
			String	indent;

			for (uint i = uint(scope); i < uint(EScope::_Count); ++i) {
				indent << '\t';
			}

			// add node declaration and style
			for (auto& node : _nodeMap)
			{
				if ( node.second.scope != scope )
					continue;

				auto&	graph_src = dst_graph.insert({ node.second.graphUID, "" }).first->second;


				auto	subgraph = src_graph.find( node.first );
				if ( subgraph != src_graph.end() )
				{
					graph_src << indent << "subgraph cluster_" << node.second.name << " {\n"
							  << _GraphStyleToString( indent, node.second.style ) << subgraph->second
							  << indent << "}\n";
					src_graph.erase( node.first );
				}
				else
					graph_src << indent << node.second.name << _NodeStyleToString( node.second.style ) << ";\n";
			}

			// add node connections
			for (auto& con : _connections)
			{
				auto	from	= _nodeMap.find( con.first );
				auto	to		= _nodeMap.find( con.second );

				if ( from == _nodeMap.end() or to == _nodeMap.end() )
					continue;	// TODO: add warning

				if ( std::max( from->second.scope, to->second.scope ) != scope )
					continue;

				String	from_node	= from->second.name;
				String	to_node		= to->second.name;
				String	edge_style	= "color=white";

				//if ( scope < EScope::CommandBuffer )
				{
					from_node << ":e";
					to_node << ":w";
				}

				//if ( scope >= EScope::CommandBufferBatch )
				//	edge_style << ", style=bold";	// , minlen=2

				if ( EnumEq( from->second.style.flags, EFlags::Sync ) and EnumEq( to->second.style.flags, EFlags::Sync ) )
					edge_style = "color=\"#"s << ColToStr( HtmlColor::OrangeRed ) << "\", style=bold, weight=10"; // 

				if ( from->second.graphUID == to->second.graphUID )
				{
					// inside subgraph
					auto	graph = dst_graph.find( from->second.graphUID );
					CHECK_ERR( graph != dst_graph.end() );

					graph->second << indent << from_node << " -> " << to_node << " [" << edge_style << "];\n";
				}
				else
				{
					deps << "\t" << from_node << " -> " << to_node << " [" << edge_style << "];\n";
				}
			}

			for (auto& gr : src_graph) {
				dst_graph.insert({ gr.first, "" }).first->second << std::move(gr.second);
			}
			src_graph.clear();
		}

		for (auto& subgraph : subgraphs)
		{
			for (auto& graph : subgraph)
			{
				src << graph.second << '\n';
			}
		}

		src << deps << "}\n";
		return src;
	}
	
/*
=================================================
	_NodeStyleToString
=================================================
*/
	String  GraphData::_NodeStyleToString (const NodeStyle &style) const
	{
		String			src = " [";
		const size_t	len	= src.length();
		
		if ( not style.label.empty() )
		{
			src << "label=\"" << style.label << '"'
				<< ", fontcolor=\"#" << ColToStr( style.labelColor ) << '"';

			if ( style.fontSize > 0 )
				src << ", fontsize=" << FG::ToString( style.fontSize );
		}
		
		src << (src.size() > len ? ", " : "");

		if ( EnumEq( style.flags, EFlags::Filled ) )
			src << "style=filled, fillcolor=\"#" << ColToStr( style.bgColor ) << "\"";
		else
			src << "color=\"#" << ColToStr( style.bgColor ) << "\"";

		src << ']';
		return src;
	}
	
/*
=================================================
	_GraphStyleToString
=================================================
*/
	String  GraphData::_GraphStyleToString (StringView indent, const NodeStyle &style) const
	{
		String	src;
		
		if ( EnumEq( style.flags, EFlags::Filled ) )
			src << indent << "\tstyle=filled;\n";

		src	<< indent << "\tcolor=\"#" << ColToStr( style.bgColor ) << "\";\n";

		if ( not style.label.empty() )
		{
			src << indent << "\tfontcolor=\"#" << ColToStr( style.labelColor ) << "\";\n"
				<< indent << "\tlabel=\"" << style.label << "\";\n";

			if ( style.fontSize )
				src << indent << "\tfontsize=" << FG::ToString( style.fontSize ) << ";\n";
		}
		return src;
	}
//-----------------------------------------------------------------------------



/*
=================================================
	ProcessQueueCommands
=================================================
*/
	static void ProcessQueueCommands (const QueueBookmark &bm, const QueueExecutionStart &cmd, const UID queueUID, INOUT GraphData &graph)
	{
		GraphData::NodeStyle	image_style;
		GraphData::NodeStyle	buffer_style;
		GraphData::NodeStyle	global_style;
		GraphData::NodeStyle	func_style;
		GraphData::NodeStyle	pass_style;
		GraphData::NodeStyle	cmd_style;
		GraphData::NodeStyle	batch_style;

		image_style.label		= "img";
		image_style.bgColor		= HtmlColor::DodgerBlue;
		image_style.labelColor	= HtmlColor::Black;

		buffer_style.label		= "buf";
		buffer_style.bgColor	= HtmlColor::Lime;
		buffer_style.labelColor	= HtmlColor::Black;

		global_style.bgColor	= HtmlColor::Coral;
		global_style.labelColor	= HtmlColor::Black;
		
		func_style.bgColor		= HtmlColor::DarkGreen;
		func_style.labelColor	= HtmlColor::Aquamarine;
		
		pass_style.label		= "render pass";
		pass_style.bgColor		= HtmlColor::DarkKhaki;
		pass_style.labelColor	= HtmlColor::LightYellow;

		cmd_style.label			= "command buffer";
		cmd_style.bgColor		= HtmlColor::RoyalBlue;
		cmd_style.labelColor	= HtmlColor::Aqua;
		
		batch_style.label		= "submit";
		batch_style.bgColor		= HtmlColor::DarkSlateGray;
		batch_style.labelColor	= HtmlColor::Gainsboro;
		batch_style.fontSize	= 16;

		HashSet<UID>	func_uids;
		HashSet<UID>	renderpass_uids;
		HashSet<UID>	cmdbuf_uids;
		HashSet<UID>	batch_uids;

		const auto	AddFunc = [&] (const auto &sync)
		{
			const UID	batch_uid	= (UID(1) << 63) | UID(bm.pos.Value());

			if ( func_uids.insert( sync.funcUID ).second )
			{
				switch ( sync.packetId ) {
					case VKTRACE_TPI_VK_vkCmdPipelineBarrier :	func_style.label = "barrier";	break;
					case VKTRACE_TPI_VK_vkCmdWaitEvents :		func_style.label = "events";	break;
					case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
					case VKTRACE_TPI_VK_vkCmdNextSubpass :		func_style.label = "subpass";	break;
					default :									ASSERT(false);					break;
				}
				graph.AddNode( sync.funcUID, "fn"s << ToString<16>( sync.funcUID ), GraphData::EScope::ApiCall,
							   sync.renderPassUID ? sync.renderPassUID : sync.cmdBufferUID, func_style );
			}

			if ( sync.renderPassUID and renderpass_uids.insert( sync.renderPassUID ).second ) {
				graph.AddNode( sync.renderPassUID, "rp"s << ToString<16>( sync.renderPassUID ), GraphData::EScope::RenderPass, sync.cmdBufferUID, pass_style );
			}

			if ( cmdbuf_uids.insert( sync.cmdBufferUID ).second ) {
				graph.AddNode( sync.cmdBufferUID, "cmd"s << ToString<16>( sync.cmdBufferUID ), GraphData::EScope::CommandBuffer, batch_uid, cmd_style );
			}

			if ( batch_uids.insert( batch_uid ).second ) {
				graph.AddNode( batch_uid, "cbb"s << ToString<16>( batch_uid ), GraphData::EScope::CommandBufferBatch, queueUID, batch_style );
			}
		};


		for (auto& q : cmd.syncQueues)
		{
			for (auto& img : q.imageSync)
			{
				for (auto& sync : img.second)
				{
					//if ( sync.input.empty() and sync.output.empty() )
					//	continue;

					graph.AddNode( sync.uid, "img"s << ToString<16>( sync.uid ), GraphData::EScope::ApiCallArg, sync.funcUID, image_style );
					AddFunc( sync );

					for (auto& in : sync.input) {
						graph.AddConnection( in, sync.uid );
					}
					for (auto& out : sync.output) {
						graph.AddConnection( sync.uid, out );
					}
				}
			}

			for (auto& buf : q.bufferSync)
			{
				for (auto& sync : buf.second)
				{
					//if ( sync.input.empty() and sync.output.empty() )
					//	continue;

					graph.AddNode( sync.uid, "buf"s << ToString<16>( sync.uid ), GraphData::EScope::ApiCallArg, sync.funcUID, buffer_style );
					AddFunc( sync );

					for (auto& in : sync.input) {
						graph.AddConnection( in, sync.uid );
					}
					for (auto& out : sync.output) {
						graph.AddConnection( sync.uid, out );
					}
				}
			}

			for (auto& sync : q.globalSync)
			{
				if ( sync.input.empty() and sync.output.empty() )
					continue;

				Visit( sync.data,
					  [&global_style] (const SynchronizationsAnalyzer::MemorySync &)	{ global_style.label = "mem"; },
					  [&global_style] (const SynchronizationsAnalyzer::ExecutionSync &)	{ global_style.label = "exe"; },
					  [&global_style] (const auto &)									{ global_style.label = "unknown"; }
				);

				graph.AddNode( sync.uid, "glob"s << ToString<16>( sync.uid ), GraphData::EScope::ApiCallArg, sync.funcUID, global_style );
				AddFunc( sync );
				
				for (auto& in : sync.input) {
					graph.AddConnection( in, sync.uid );
				}
				for (auto& out : sync.output) {
					graph.AddConnection( sync.uid, out );
				}
			}
		}
	}

/*
=================================================
	ConvertSyncQueue
=================================================
*/
	bool ConvertSyncQueue (const FrameID firstFrameId, const FrameID lastFrameId, const SynchronizationsAnalyzer::QueueInfo_t &queue,
						   const HashMap<FrameID, UID> &frameUIDs, INOUT GraphData &graph)
	{
		const UID	queue_uid = (UID(1) << 63) | UID(queue.bookmarks.front().pos.Value());

		for (auto& bm : queue.bookmarks)
		{
			if ( bm.frameId == ~FrameID(0) or bm.frameId < firstFrameId)
				continue;

			if ( bm.frameId >= lastFrameId )
				break;

			GraphData::EScope	scope		= GraphData::EScope::QueueCmd;
			UID					graph_uid	= frameUIDs.find(bm.frameId)->second;
			
			GraphData::NodeStyle	style;
			style.bgColor		= HtmlColor::MidnightBlue;
			style.labelColor	= HtmlColor::White;

			Visit( bm.data,
				[&] (const QueueExecutionStart &cmd) {
					ProcessQueueCommands( bm, cmd, graph_uid, INOUT graph );
					if ( cmd.waitSemaphores.size() ) {
						style.bgColor	 = HtmlColor::Red;
						style.label		 = "Wait";
						style.flags		|= GraphData::EFlags::Sync;
					}else{
						style.label		 = " ";
						style.flags		|= GraphData::EFlags::PartOfGroup;
					}
					scope		= GraphData::EScope::CommandBuffer;
					graph_uid	= (UID(1) << 63) | UID(bm.pos.Value());
				},

				[&] (const QueueExecutionFinish &cmd) {
					if ( cmd.signalSemaphores.size() ) {
						style.bgColor	 = HtmlColor::Gold;
						style.label		 = "Signal";
						style.flags		|= GraphData::EFlags::Sync;
					}else{
						style.label		 = "|";
						style.flags		|= GraphData::EFlags::PartOfGroup;
					}
					scope		= GraphData::EScope::CommandBuffer;
					graph_uid	= (UID(1) << 63) | UID(bm.pos.Value());
				},

				[&style] (const QueueFenceSignal &) {
					style.label		 = "Fence";
					style.bgColor	 = HtmlColor::Gold;
					style.flags		|= GraphData::EFlags::Sync;
				},

				[&style] (const QueueWaitIdle &) {
					style.label		 = "Wait";
					style.bgColor	 = HtmlColor::Red;
					style.flags		|= GraphData::EFlags::Sync;
				},

				[&style] (std::nullptr_t) {
					style.label.clear();
				},
				[] (const auto &)	{ ASSERT(false); }	// add support for new type
			);

			if ( style.label.empty() )
				continue;

			graph.AddNode( bm.uid, "q"s << ToString<16>( bm.uid ), scope, graph_uid, style );

			for (auto& in : bm.input)	{ graph.AddConnection( in, bm.uid ); }
			for (auto& out : bm.output)	{ graph.AddConnection( bm.uid, out ); }
		}
		
		GraphData::NodeStyle	style;
		style.label			= "queue";
		style.bgColor		= HtmlColor::WhiteSmoke;
		style.labelColor	= HtmlColor::Black;

		//graph.AddNode( queue_uid, "queue"s << ToString<16>( queue_uid ), GraphData::EScope::Queue, 1, style );
		return true;
	}
	
/*
=================================================
	ConvertSwapchain
=================================================
*/
	static bool ConvertSwapchain (const FrameID firstFrameId, const FrameID lastFrameId, const SynchronizationsAnalyzer::SwapchainInfo_t &swapchain,
								  const HashMap<FrameID, UID> &frameUIDs, INOUT GraphData &graph)
	{
		const UID				swapchain_uid	= (UID(1) << 63) | UID(swapchain.bookmarks.back().pos.Value());
		UID						last_uid		= 0;

		for (auto& bm : swapchain.bookmarks)
		{
			if ( bm.frameId == ~FrameID(0) or bm.frameId < firstFrameId)
				continue;

			if ( bm.frameId >= lastFrameId )
				break;
			
			GraphData::NodeStyle	style;
			style.bgColor		= HtmlColor::Indigo;
			style.labelColor	= HtmlColor::Black;

			Visit( bm.data,
				[&style] (const SwapchainAcquireImage &cmd) {
					style.label = "Acquire";
					if ( cmd.hasSemaphore ) {
						style.bgColor	 = HtmlColor::Gold;
						style.flags		|= GraphData::EFlags::Sync;
					}
				},

				[&style] (const SwapchainPresent &cmd) {
					style.label = "Present";
					if ( cmd.waitSemaphores.size() ) {
						style.bgColor	 = HtmlColor::Red;
						style.flags		|= GraphData::EFlags::Sync;
					}
				},

				[&style] (std::nullptr_t)	{ style.label.clear(); },
				[]		 (const auto &)		{ ASSERT(false); }
			);

			if ( style.label.empty() )
				continue;
			
			graph.AddNode( bm.uid, "sw"s << ToString<16>( bm.uid ), GraphData::EScope::QueueCmd, frameUIDs.find(bm.frameId)->second + 1, style );

			for (auto& in : bm.input)	{ graph.AddConnection( in, bm.uid ); }
			for (auto& out : bm.output)	{ graph.AddConnection( bm.uid, out ); }

			if ( last_uid )
				graph.AddConnection( last_uid, bm.uid );

			last_uid = bm.uid;
		}
		
		GraphData::NodeStyle	style;
		style.label			= "swapchain";
		style.bgColor		= HtmlColor::Indigo;
		style.labelColor	= HtmlColor::Orchid;
		style.fontSize		= 18;

		for (auto& frame : frameUIDs) {
			graph.AddNode( frame.second+1, "swapchain"s << ToString<16>( frame.second+1 ), GraphData::EScope::Queue, frame.second, style );
		}
		return true;
	}

/*
=================================================
	ConvertHostSync
=================================================
*/
	static bool ConvertHostSync (const FrameID firstFrameId, const FrameID lastFrameId, const SynchronizationsAnalyzer::DeviceInfo_t &dev,
								 const HashMap<FrameID, UID> &frameUIDs, INOUT GraphData &graph)
	{
		struct ThreadInfo {
			UID		uid		= 0;
			UID		lastUID	= 0;
		};
		HashMap<ThreadID,ThreadInfo>	thread_uids;

		for (auto& bm : dev.bookmarks)
		{
			if ( bm.frameId == ~FrameID(0) or bm.frameId < firstFrameId)
				continue;

			if ( bm.frameId >= lastFrameId )
				break;
			
			GraphData::NodeStyle	style;			
			style.bgColor		= HtmlColor::Purple;
			style.labelColor	= HtmlColor::White;

			Visit( bm.data,
				[&style] (const HostAcquireNextImage &cmd) {
					style.label = "Acquire";
					if ( cmd.fence ) {
						style.bgColor	 = HtmlColor::Gold;
						style.flags		|= GraphData::EFlags::Sync;
					}
				},
				[&style] (const HostWaitForFences &) {
					style.label		 = "Wait";
					style.bgColor	 = HtmlColor::FireBrick;
					style.flags		|= GraphData::EFlags::Sync;
				},
				[&style] (const HostWaitForQueueIdle &) {
					style.label		 = "Wait";
					style.bgColor	 = HtmlColor::FireBrick;
					style.flags		|= GraphData::EFlags::Sync;
				},
				[&style] (const HostWaitForDeviceIdle &) {
					style.label		 = "Wait";
					style.bgColor	 = HtmlColor::FireBrick;
					style.flags		|= GraphData::EFlags::Sync;
				},
				[&style] (const HostQueueSubmit &)	{ style.label = "Submit"; },
				[&style] (const HostResetFences &)	{ style.label.clear(); },
				[&style] (std::nullptr_t)			{ style.label.clear(); },
				[] (const auto &)					{ ASSERT(false); }
			);
			
			if ( style.label.empty() )
				continue;

			auto&	thread_info = thread_uids.insert({ bm.threadId, ThreadInfo{ (UID(1) << 63) | (UID(bm.pos.Value())+1), 0 } }).first->second;

			graph.AddNode( bm.uid, "dev"s << ToString<16>( bm.uid ), GraphData::EScope::HostCmd, frameUIDs.find(bm.frameId)->second+2, style );

			for (auto& in : bm.input)	{ graph.AddConnection( in, bm.uid ); }
			for (auto& out : bm.output)	{ graph.AddConnection( bm.uid, out ); }

			if ( thread_info.lastUID )
				graph.AddConnection( thread_info.lastUID, bm.uid );

			thread_info.lastUID = bm.uid;
		}
		
		GraphData::NodeStyle	style;
		style.label			= "host thread";
		style.bgColor		= HtmlColor::Indigo;
		style.labelColor	= HtmlColor::DeepSkyBlue;
		style.fontSize		= 18;

		for (auto& frame : frameUIDs) {
			graph.AddNode( frame.second+2, "thrd"s << ToString<16>( frame.second+2 ), GraphData::EScope::HostThread, frame.second, style );
		}
		return true;
	}

/*
=================================================
	_ConvertSyncGraph
=================================================
*/
	bool GraphVizConverter::_ConvertSyncGraph (FrameID first, FrameID last, const AppTrace &appTrace) const
	{
		CHECK_ERR( _syncAnalyzer );

		GraphData				graph;
		HashMap<FrameID, UID>	frame_uids;

		// create frame uids
		for (FrameID i = first; i < last; ++i)
		{
			const UID	uid = (UID(1) << 63) | UID(appTrace.GetFrameTrace(i).FirstBookmark().Value());

			frame_uids.insert({ i, uid });

			GraphData::NodeStyle	style;
			style.label			= "frame "s << ToString( i );
			style.bgColor		= HtmlColor::DimGray;
			style.labelColor	= HtmlColor::LimeGreen;
			style.fontSize		= 20;

			graph.AddNode( uid, "frame_"s << ToString( i ), GraphData::EScope::Frame, 0, style );
		}

		for (auto& dev : _syncAnalyzer->GetDevices())
		{
			for (auto& inst : dev.second) {
				CHECK_ERR( ConvertHostSync( first, last, inst, frame_uids, INOUT graph ));
			}
		}

		for (auto& swapchain : _syncAnalyzer->GetSwapchains())
		{
			for (auto& inst : swapchain.second) {
				CHECK_ERR( ConvertSwapchain( first, last, inst, frame_uids, INOUT graph ));
			}
		}

		for (auto& queue : _syncAnalyzer->GetQueues())
		{
			for (auto& inst : queue.second) {
				CHECK_ERR( ConvertSyncQueue( first, last, inst, frame_uids, INOUT graph ));
			}
		}

		// store to file and visualize
		{
			const fs::path	fname = fs::path{_directory}.append( "sync-graph-"s << ToString(first)<<'-'<<ToString(last) << ".dot" );
		
			CHECK_ERR( _StoreFile( fname, graph.ToString() ));
			CHECK_ERR( _Visualize( fname ));
		}
		return true;
	}


}	// VTC
