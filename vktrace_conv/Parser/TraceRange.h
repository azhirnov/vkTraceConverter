// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "VkTraceCommon.h"

namespace VTC
{


	//
	// VkTrace Range
	//

	class TraceRange
	{
	// types
	public:
		struct Bookmark
		{
			friend class TraceRange;
			friend struct Iterator;

		// variables
		private:
			uint64_t	_offset	= ~0ull;


		// methods
		private:
			explicit Bookmark (uint64_t off) : _offset{off} {}

		public:
			Bookmark () {}

			template <typename T1, typename T2>
			ND_ uint64_t GenResourceDataID (const T1* hdr, const T2* member) const;

			ND_ bool operator == (Bookmark rhs) const	{ return _offset == rhs._offset; }
			ND_ bool operator != (Bookmark rhs) const	{ return _offset != rhs._offset; }
		};


		struct Iterator
		{
			friend class TraceRange;

		// variables
		private:
			vktrace_trace_packet_header*	_lastPacket	= null;
			FileLike *						_file		= null;
			uint64_t						_offset		= 0;
			uint64_t						_nextOffset	= 0;


		// methods
		private:
			Iterator (FileLike* file, uint64_t offset) : _file{file}, _offset{offset} { _ReadPacket(); }

			void _ReadPacket ();
			void _ReleasePacket ();

		public:
			Iterator ()		{}
			~Iterator ()	{ _ReleasePacket(); }

			Iterator (Iterator &&) = default;
			Iterator (const Iterator &) = delete;

				Iterator&	operator = (Iterator &&) = default;
				Iterator&	operator = (const Iterator &) = delete;

				Iterator&	operator ++ ();

			ND_ bool		IsValid () const								{ return _lastPacket != null; }

			ND_ bool		operator == (const Iterator &rhs) const			{ return _file == rhs._file and _offset == rhs._offset; }
			ND_ bool		operator != (const Iterator &rhs) const			{ return not (*this == rhs); }

			ND_ bool		operator <  (const Iterator &rhs) const;

			ND_ Bookmark	GetBookmark () const							{ return Bookmark{ _offset }; }

			template <typename T>
			ND_ T const&	Cast () const;

			ND_ vktrace_trace_packet_header *	operator -> ()	const		{ ASSERT( _lastPacket );  return _lastPacket; }
			ND_ vktrace_trace_packet_header *	operator * ()	const		{ return _lastPacket; }
		};


	// variables
	private:
		FileLike *		_file				= null;
		uint64_t		_firstPacketOffset	= 0;
		uint64_t		_lastPacketOffset	= 0;


	// methods
	private:
		TraceRange (FileLike* file, uint64_t first, uint64_t last);

	public:
		TraceRange () {}
		explicit TraceRange (FileLike* file);

		ND_ Iterator	begin ()	const;
		ND_ Iterator	end ()		const;
		ND_ bool		empty ()	const;

		ND_ TraceRange  SubRange (Iterator begin, Iterator end) const;

		ND_ Iterator	Get (const Bookmark &bookmark) const;

		ND_ bool		Contains (const Iterator &value) const;
		ND_ bool		Contains (const Bookmark &value) const;
	};
	

	
/*
=================================================
	constructor
=================================================
*/
	inline TraceRange::TraceRange (FileLike* file, uint64_t first, uint64_t last) :
		_file{file}, _firstPacketOffset{first}, _lastPacketOffset{last}
	{
		ASSERT( _file );
		ASSERT( _firstPacketOffset <= _lastPacketOffset );
		ASSERT( _lastPacketOffset <= _file->mFileLen );
	}
	
/*
=================================================
	constructor
=================================================
*/
	inline TraceRange::TraceRange (FileLike* file) :
		_file{ file },
		_firstPacketOffset{ vktrace_FileLike_GetCurrentPosition( _file ) },
		_lastPacketOffset{ _file->mFileLen }
	{}

/*
=================================================
	begin
=================================================
*/
	inline TraceRange::Iterator  TraceRange::begin () const
	{
		return Iterator{ _file, _firstPacketOffset };
	}
	
/*
=================================================
	end
=================================================
*/
	inline TraceRange::Iterator  TraceRange::end () const
	{
		return Iterator{ _file, _lastPacketOffset };
	}
	
/*
=================================================
	empty
=================================================
*/
	inline bool  TraceRange::empty () const
	{
		return	not _file	or
				_firstPacketOffset == _lastPacketOffset;
	}
	
/*
=================================================
	SubRange
=================================================
*/
	inline TraceRange  TraceRange::SubRange (Iterator beginIter, Iterator endIter) const
	{
		ASSERT( beginIter._file == endIter._file );
		ASSERT( beginIter._offset <= endIter._offset );
		ASSERT( Contains( beginIter ) );
		ASSERT( Contains( endIter ) );

		return TraceRange{ beginIter._file, beginIter._offset, endIter._offset };
	}
	
/*
=================================================
	Get
=================================================
*/
	inline TraceRange::Iterator  TraceRange::Get (const Bookmark &bookmark) const
	{
		ASSERT( Contains( bookmark ) );
		return Iterator{ _file, bookmark._offset };
	}

/*
=================================================
	Contains
=================================================
*/
	inline bool  TraceRange::Contains (const Iterator &value) const
	{
		return	_file == value._file					and
				value._offset >= _firstPacketOffset		and
				value._offset < _lastPacketOffset;
	}
	
/*
=================================================
	Contains
=================================================
*/
	inline bool  TraceRange::Contains (const Bookmark &value) const
	{
		return	value._offset >= _firstPacketOffset		and
				value._offset < _lastPacketOffset;
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	operator ++
=================================================
*/
	inline TraceRange::Iterator&  TraceRange::Iterator::operator ++ ()
	{
		_offset = _nextOffset;

		_ReadPacket();

		return *this;
	}
	
/*
=================================================
	Cast
=================================================
*/
	template <typename T>
	inline T const&  TraceRange::Iterator::Cast () const
	{
		ASSERT( _lastPacket );

		if constexpr ( std::is_pointer_v<T> )
			return BitCast< const T >( _lastPacket->pBody );
		else
			return *BitCast< T const *>( _lastPacket->pBody );
	}

/*
=================================================
	operator <
=================================================
*/
	inline bool  TraceRange::Iterator::operator <  (const Iterator &rhs) const
	{
		ASSERT( _file == rhs._file );	// it is very strange if you compare iterators with diferrent files

		return	_file != rhs._file	?	_file < rhs._file	:
										_offset < rhs._offset;
	}
//-----------------------------------------------------------------------------
	


/*
=================================================
	GenResourceDataID
=================================================
*/
	template <typename T1, typename T2>
	inline uint64_t  TraceRange::Bookmark::GenResourceDataID (const T1* hdr, const T2* member) const
	{
		const size_t	off_1	= BitCast<size_t>( hdr );
		const size_t	off_2	= BitCast<size_t>( member );

		ASSERT( off_1 < off_2 );

		return _offset + uint64_t(off_2 - off_1);
	}


}	// VTC
