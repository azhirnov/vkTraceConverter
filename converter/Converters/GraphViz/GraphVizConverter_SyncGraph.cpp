// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/GraphViz/GraphVizConverter.h"
#include "Converters/Utils/BasicTypesConverter.h"
#include "stl/Math/Color.h"

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
	using EConnectionFlags				= SynchronizationsAnalyzer::EConnectionFlags;
	


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
			PartOfGroup	= 1 << 0,	// connection will be to group boundaries instead of node
			Filled		= 1 << 1,
			Hidden		= 1 << 2,
			SmallSize	= 1 << 3,
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

		struct ConnectionStyle {
			RGBA8u		color		= HtmlColor::White;
			int			weight		= 0;
			int			minlen		= 0;
			bool		bold		= false;
			bool		dotted		= false;
		};

		using NodeMap_t		= HashMap< UID, NodeInfo >;
		using Connections_t	= HashMap< Pair<UID, UID>, ConnectionStyle >;


	// variables
		NodeMap_t		_nodeMap;
		Connections_t	_connections;


	// methods
		void AddNode (UID uid, const String &name, EScope scope, UID graphUID, const NodeStyle &style);
		void AddConnection (UID from, UID to, const ConnectionStyle &style);

		ND_ String  ToString ();

	private:
		ND_ String  _NodeStyleToString (const NodeStyle &style) const;
		ND_ String  _GraphStyleToString (StringView indent, const NodeStyle &style) const;
		ND_ String  _ConnectionStyleToString (const ConnectionStyle &style) const;
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
	void GraphData::AddConnection (UID from, UID to, const ConnectionStyle &style)
	{
		_connections.insert({ {from, to}, style });
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
				auto	from	= _nodeMap.find( con.first.first );
				auto	to		= _nodeMap.find( con.first.second );

				if ( from == _nodeMap.end() or to == _nodeMap.end() )
					continue;

				if ( std::max( from->second.scope, to->second.scope ) != scope )
					continue;

				String	from_node	= from->second.name + ":e";
				String	to_node		= to->second.name + ":w";
				String	edge_style	= _ConnectionStyleToString( con.second );
				
				if ( EnumEq( from->second.style.flags | to->second.style.flags, EFlags::Hidden ) )
					edge_style = "style=invis";

				if ( from->second.graphUID == to->second.graphUID )
				{
					// inside subgraph
					auto	graph = dst_graph.find( from->second.graphUID );
					CHECK_ERR( graph != dst_graph.end() );

					graph->second << indent << from_node << " -> " << to_node << " [" << edge_style << "];\n";
				}
				else
				{
					//if ( EnumEq( from->second.style.flags, EFlags::PartOfGroup ) )
					//	edge_style << ", lhead=cluster_" << _nodeMap.find( from->second.graphUID )->second.name;
				
					//if ( EnumEq( to->second.style.flags, EFlags::PartOfGroup ) )
					//	edge_style << ", ltail=cluster_" << _nodeMap.find( to->second.graphUID )->second.name;

					deps << "\t" << from_node << " -> " << to_node << " [" << edge_style << "];\n";
				}
			}

			for (auto& gr : src_graph) {
				dst_graph.insert({ gr.first, "" }).first->second << std::move(gr.second);
			}
			src_graph.clear();
		}

		for (auto& subgraph : subgraphs) {
			for (auto& graph : subgraph) {
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
		
		if ( EnumEq( style.flags, EFlags::SmallSize ) )
			src = " [label=\"\", fontsize=1, fixedsize=true, height=0, width=0";

		if ( EnumEq( style.flags, EFlags::Hidden ) )
			src = " [label=\"\", fixedsize=true, height=0, width=0, style=invis";

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
		
/*
=================================================
	_ConnectionStyleToString
=================================================
*/
	String  GraphData::_ConnectionStyleToString (const ConnectionStyle &style) const
	{
		String	src;
		
		src << "color=\"#" << ColToStr( style.color ) << '"';

		if ( style.bold )
			src << ", style=bold";
		else
		if ( style.dotted )
			src << ", style=dotted";

		if ( style.weight > 0 )
			src << ", weight=" << FG::ToString( style.weight );

		if ( style.minlen > 0 )
			src << ", minlen=" << FG::ToString( style.minlen );

		return src;
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	SetupStyle
=================================================
*/
	static void SetupStyle (EConnectionFlags flags, OUT GraphData::ConnectionStyle &style)
	{
		style = {};

		if ( EnumEq( flags, EConnectionFlags::HostWait ) )
		{
			style.color		= HtmlColor::Red;
			style.bold		= true;
			style.weight	= 2;
			return;
		}

		if ( EnumEq( flags, EConnectionFlags::Wait ) )
		{
			style.color		= HtmlColor::Coral;
			style.bold		= true;
			style.weight	= 4;
			return;
		}

		if ( EnumEq( flags, EConnectionFlags::Strong ) )
		{
			style.color		= HtmlColor::DeepSkyBlue;
			style.bold		= true;
			style.weight	= 2;
			return;
		}

		style.color		= HtmlColor::LightGray;
		style.dotted	= EnumEq( flags, EConnectionFlags::Execution );
	}

/*
=================================================
	ProcessQueueCommands
=================================================
*/
	inline void ProcessQueueCommands (const QueueBookmark &, const QueueExecutionStart &cmd, const UID submitionUID, INOUT GraphData &graph)
	{
		GraphData::NodeStyle		image_style;
		GraphData::NodeStyle		buffer_style;
		GraphData::NodeStyle		global_style;
		GraphData::NodeStyle		pass_style;
		GraphData::NodeStyle		cmd_style;
		GraphData::ConnectionStyle	con_style;

		image_style.label		= "img";
		image_style.bgColor		= HtmlColor::DodgerBlue;
		image_style.labelColor	= HtmlColor::Black;

		buffer_style.label		= "buf";
		buffer_style.bgColor	= HtmlColor::LightSeaGreen;
		buffer_style.labelColor	= HtmlColor::Black;

		global_style.bgColor	= HtmlColor::LightGoldenRodYellow;
		global_style.labelColor	= HtmlColor::Black;
		
		pass_style.label		= "render pass";
		pass_style.bgColor		= HtmlColor::DarkKhaki;
		pass_style.labelColor	= HtmlColor::Black;

		cmd_style.label			= "command buffer";
		cmd_style.bgColor		= HtmlColor::Indigo;
		cmd_style.labelColor	= HtmlColor::Aqua;

		con_style.color			= HtmlColor::White;

		HashSet<UID>	func_uids;
		HashSet<UID>	renderpass_uids;
		HashSet<UID>	cmdbuf_uids;

		const auto	AddFunc = [&] (const auto &sync)
		{
			GraphData::NodeStyle	func_style;
			func_style.bgColor		= HtmlColor::DarkGreen;
			func_style.labelColor	= HtmlColor::Aquamarine;

			if ( func_uids.insert( sync.funcUID ).second )
			{
				switch ( sync.packetId ) {
					case VKTRACE_TPI_VK_vkCmdPipelineBarrier :
						func_style.label = "barrier";
						break;
					case VKTRACE_TPI_VK_vkCmdWaitEvents :
						func_style.label = "events";
						break;
					case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
					case VKTRACE_TPI_VK_vkCmdNextSubpass :
						func_style.label		= "subpass";
						func_style.bgColor		= HtmlColor::Peru;
						func_style.labelColor	= HtmlColor::Yellow;
						break;
					default :
						ASSERT(false);
						break;
				}
				graph.AddNode( sync.funcUID, "fn"s << ToString<16>( sync.funcUID ), GraphData::EScope::ApiCall,
							   sync.renderPassUID ? sync.renderPassUID : sync.cmdBufferUID, func_style );
			}

			if ( sync.renderPassUID and renderpass_uids.insert( sync.renderPassUID ).second ) {
				graph.AddNode( sync.renderPassUID, "rp"s << ToString<16>( sync.renderPassUID ), GraphData::EScope::RenderPass, sync.cmdBufferUID, pass_style );
			}

			if ( cmdbuf_uids.insert( sync.cmdBufferUID ).second ) {
				graph.AddNode( sync.cmdBufferUID, "cmd"s << ToString<16>( sync.cmdBufferUID ), GraphData::EScope::CommandBuffer, submitionUID, cmd_style );
			}
		};


		for (auto& q : cmd.syncQueues)
		{
			for (auto& img : q.imageSync)
			{
				for (auto& sync : img.second)
				{
					if ( sync.input.empty() and sync.output.empty() )
						continue;

					graph.AddNode( sync.uid, "img"s << ToString<16>( sync.uid ), GraphData::EScope::ApiCallArg, sync.funcUID, image_style );
					AddFunc( sync );

					for (auto& in : sync.input) {
						graph.AddConnection( in.uid, sync.uid, con_style );
					}
					for (auto& out : sync.output) {
						graph.AddConnection( sync.uid, out.uid, con_style );
					}
				}
			}

			for (auto& buf : q.bufferSync)
			{
				for (auto& sync : buf.second)
				{
					if ( sync.input.empty() and sync.output.empty() )
						continue;

					graph.AddNode( sync.uid, "buf"s << ToString<16>( sync.uid ), GraphData::EScope::ApiCallArg, sync.funcUID, buffer_style );
					AddFunc( sync );

					for (auto& in : sync.input) {
						graph.AddConnection( in.uid, sync.uid, con_style );
					}
					for (auto& out : sync.output) {
						graph.AddConnection( sync.uid, out.uid, con_style );
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
					graph.AddConnection( in.uid, sync.uid, con_style );
				}
				for (auto& out : sync.output) {
					graph.AddConnection( sync.uid, out.uid, con_style );
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
		
		GraphData::NodeStyle	submition_style;
		submition_style.label		= "submit";
		submition_style.bgColor		= HtmlColor::DarkSlateGray;
		submition_style.labelColor	= HtmlColor::Gainsboro;
		//batch_style.fontSize	= 16;

		for (auto& bm : queue.bookmarks)
		{
			if ( bm.frameId == UMax or bm.frameId < firstFrameId)
				continue;

			if ( bm.frameId >= lastFrameId )
				break;

			GraphData::EScope	scope		= GraphData::EScope::QueueCmd;
			const UID			frame_uid	= frameUIDs.find(bm.frameId)->second;
			UID					graph_uid	= frame_uid;

			GraphData::NodeStyle	style;
			style.bgColor		= HtmlColor::MidnightBlue;
			style.labelColor	= HtmlColor::Black;

			GraphData::ConnectionStyle	con_style;

			Visit( bm.data,
				[&] (const QueueExecutionStart &cmd)
				{
					graph_uid = (UID(1) << 63) | UID(bm.pos.Value());
					graph.AddNode( graph_uid, "submit"s << ToString<16>( graph_uid ), scope, frame_uid, submition_style );

					ProcessQueueCommands( bm, cmd, graph_uid, INOUT graph );

					if ( cmd.waitSemaphores.size() ) {
						style.bgColor	= HtmlColor::Red;
						style.label		= "Wait";
					}else{
						style.label		= " ";
						style.flags		= GraphData::EFlags::SmallSize;
					}
					scope = GraphData::EScope::CommandBuffer;
				},

				[&] (const QueueExecutionFinish &cmd) {
					if ( cmd.signalSemaphores.size() ) {
						style.bgColor	= HtmlColor::Gold;
						style.label		= "Signal";
					}else{
						style.label		= " ";
						style.flags		= GraphData::EFlags::SmallSize;
					}
					scope		= GraphData::EScope::CommandBuffer;
					graph_uid	= (UID(1) << 63) | UID(bm.pos.Value());
				},

				[&] (const QueueFenceSignal &) {
					style.label		= "Fence";
					style.bgColor	= HtmlColor::Gold;
					scope			= GraphData::EScope::CommandBuffer;
					graph_uid		= (UID(1) << 63) | UID(bm.pos.Value());
				},

				[&style] (const QueueWaitIdle &) {
					style.label		= "WaitIdle";
					style.bgColor	= HtmlColor::Red;
				},

				[&style] (std::nullptr_t)	{},
				[] (const auto &)			{ ASSERT(false); }	// add support for new type
			);

			if ( style.label.empty() )
				continue;

			graph.AddNode( bm.uid, "q"s << ToString<16>( bm.uid ), scope, graph_uid, style );

			for (auto& in : bm.input) {
				SetupStyle( in.flags, OUT con_style );
				graph.AddConnection( in.uid, bm.uid, con_style );
			}

			for (auto& out : bm.output) {
				SetupStyle( out.flags, OUT con_style );
				graph.AddConnection( bm.uid, out.uid, con_style );
			}
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
		const UID	swapchain_uid	= (UID(1) << 63) | UID(swapchain.bookmarks.back().pos.Value());

		for (auto& bm : swapchain.bookmarks)
		{
			if ( bm.frameId == UMax or bm.frameId < firstFrameId)
				continue;

			if ( bm.frameId >= lastFrameId )
				break;

			const UID	frame_uid = frameUIDs.find(bm.frameId)->second;
			
			GraphData::NodeStyle	style;
			style.bgColor		= HtmlColor::Indigo;
			style.labelColor	= HtmlColor::Black;
			style.fontSize		= 24;

			GraphData::ConnectionStyle	con_style;

			Visit( bm.data,
				[&style] (const SwapchainAcquireImage &cmd) {
					style.label = "Acquire";
					if ( cmd.hasSemaphore )
						style.bgColor = HtmlColor::Gold;
				},

				[&style] (const SwapchainPresent &cmd) {
					style.label = "Present";
					if ( cmd.waitSemaphores.size() )
						style.bgColor = HtmlColor::Red;
				},

				[&style] (std::nullptr_t)	{},
				[]		 (const auto &)		{ ASSERT(false); }
			);

			if ( style.label.empty() )
				continue;
			
			graph.AddNode( bm.uid, "sw"s << ToString<16>( bm.uid ), GraphData::EScope::QueueCmd, frame_uid, style );

			for (auto& in : bm.input) {
				SetupStyle( in.flags, OUT con_style );
				graph.AddConnection( in.uid, bm.uid, con_style );
			}

			for (auto& out : bm.output) {
				SetupStyle( out.flags, OUT con_style );
				graph.AddConnection( bm.uid, out.uid, con_style );
			}
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
			UID					lastUID	= 0;
			size_t				index	= 0;
			HashSet<FrameID>	frames;
		};
		HashMap<ThreadID,ThreadInfo>	thread_uids;

		for (auto& bm : dev.bookmarks)
		{
			if ( bm.frameId == UMax or bm.frameId < firstFrameId)
				continue;

			if ( bm.frameId >= lastFrameId )
				break;
			
			GraphData::NodeStyle	style;
			style.labelColor	= HtmlColor::White;

			GraphData::ConnectionStyle	con_style;

			Visit( bm.data,
				[&style] (const HostAcquireNextImage &cmd) {
					style.label = "Acquire";
					if ( cmd.fence )
						style.bgColor = HtmlColor::Gold;
				},
				[&style] (const HostWaitForFences &) {
					style.label		= "Wait";
					style.bgColor	= HtmlColor::Red;
				},
				[&style] (const HostWaitForQueueIdle &) {
					style.label		= "Wait";
					style.bgColor	= HtmlColor::Red;
				},
				[&style] (const HostWaitForDeviceIdle &) {
					style.label		= "Wait";
					style.bgColor	= HtmlColor::Red;
				},
				[&style] (const HostQueueSubmit &) {
					style.label		= "Submit";
					style.bgColor	= HtmlColor::Blue;
				},
				[&style] (const HostResetFences &)	{ style.label.clear(); },
				[&style] (std::nullptr_t)			{ style.label.clear(); },
				[] (const auto &)					{ ASSERT(false); }
			);
			
			if ( style.label.empty() )
				continue;

			auto&	thread_info = thread_uids.insert({ bm.threadId, ThreadInfo{ 0, thread_uids.size() + 2, {} }}).first->second;

			thread_info.frames.insert( bm.frameId );

			graph.AddNode( bm.uid, "dev"s << ToString<16>( bm.uid ), GraphData::EScope::HostCmd, frameUIDs.find(bm.frameId)->second + thread_info.index, style );

			for (auto& in : bm.input) {
				SetupStyle( in.flags, OUT con_style );
				graph.AddConnection( in.uid, bm.uid, con_style );
			}

			for (auto& out : bm.output) {
				SetupStyle( out.flags, OUT con_style );
				graph.AddConnection( bm.uid, out.uid, con_style );
			}

			if ( thread_info.lastUID ) {
				SetupStyle( EConnectionFlags::Execution, OUT con_style );
				con_style.minlen = 2;
				graph.AddConnection( thread_info.lastUID, bm.uid, con_style );
			}

			thread_info.lastUID = bm.uid;
		}
		
		GraphData::NodeStyle	style;
		style.label			= "host thread";
		style.bgColor		= HtmlColor::MidnightBlue;
		style.labelColor	= HtmlColor::White;
		style.fontSize		= 18;

		for (auto& thread : thread_uids)
		{
			for (auto& frame_id : thread.second.frames)
			{
				const UID	frame_uid	= frameUIDs.find( frame_id )->second;
				const UID	thread_uid	= frame_uid + thread.second.index;

				graph.AddNode( thread_uid, "thrd"s << ToString<16>( thread_uid ), GraphData::EScope::HostThread, frame_uid, style );
			}
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
			style.bgColor		= RGBA8u{ 40, 40, 40, 0 };
			style.labelColor	= HtmlColor::White;
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
