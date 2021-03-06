// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "VkTraceCommon.h"
#include "../utils/AlignedBuffer.h"

namespace VTC
{


	//
	// VkTrace Range
	//

	class TraceRange
	{
	// types
	public:
		using RStreamPtr	= SharedPtr<FileRStream>;


		struct Bookmark
		{
			friend class TraceRange;
			friend struct Iterator;
			friend struct std::hash< VTC::TraceRange::Bookmark >;

		// variables
		private:
			BytesU		_offset		= ~0_b;


		// methods
		private:
			explicit Bookmark (BytesU off) : _offset{off} {}

		public:
			Bookmark () {}

			ND_ bool operator == (Bookmark rhs) const	{ return _offset == rhs._offset; }
			ND_ bool operator != (Bookmark rhs) const	{ return _offset != rhs._offset; }

			ND_ bool operator >  (Bookmark rhs) const	{ return _offset >  rhs._offset; }
			ND_ bool operator <  (Bookmark rhs) const	{ return _offset <  rhs._offset; }
			ND_ bool operator >= (Bookmark rhs) const	{ return _offset >= rhs._offset; }
			ND_ bool operator <= (Bookmark rhs) const	{ return _offset <= rhs._offset; }

			ND_ BytesU	Value ()				const	{ return _offset; }
		};


		struct Iterator
		{
			friend class TraceRange;

		// variables
		private:
			AlignedBuffer<alignof(size_t)>	_buffer;
			vktrace_trace_packet_header*	_lastPacket		= null;
			RStreamPtr						_file;
			BytesU							_offset;
			BytesU							_nextOffset;
			
			static constexpr size_t			_MaxBufferSize	= (64u << 20);


		// methods
		private:
			Iterator (const RStreamPtr &file, BytesU offset);

			bool _ReadPacket ();
			void _ReleasePacket ();

		public:
			Iterator ();
			~Iterator ()	{ _ReleasePacket(); }

			Iterator (Iterator &&);
			Iterator (const Iterator &) = delete;

				Iterator&	operator = (Iterator &&);
				Iterator&	operator = (const Iterator &) = delete;

				Iterator&	operator ++ ();

			ND_ bool		IsValid () const								{ return _lastPacket != null; }

			ND_ bool		operator == (const Iterator &rhs)	const		{ return _file == rhs._file and _offset == rhs._offset; }
			ND_ bool		operator != (const Iterator &rhs)	const		{ return not (*this == rhs); }

			ND_ bool		operator <  (Bookmark rhs)			const		{ return _offset <  rhs._offset; }
			ND_ bool		operator >  (Bookmark rhs)			const		{ return _offset >  rhs._offset; }

			ND_ Bookmark	GetBookmark () const							{ return Bookmark{ _offset }; }

			template <typename T>
			ND_ T const&	Cast () const;

			ND_ vktrace_trace_packet_header *	operator -> ()	const		{ ASSERT( _lastPacket );  return _lastPacket; }
			ND_ vktrace_trace_packet_header *	operator * ()	const		{ return _lastPacket; }
		};


	// variables
	private:
		RStreamPtr	_file;
		BytesU		_firstPacketOffset;
		BytesU		_lastPacketOffset;


	// methods
	private:
		TraceRange (const RStreamPtr &file, BytesU first, BytesU last);

	public:
		TraceRange () {}
		explicit TraceRange (const RStreamPtr &file);

		ND_ Iterator	begin ()	const;
		//ND_ Iterator	end ()		const;		// use 'LastBookmark()' instead
		ND_ bool		empty ()	const;

		ND_ Bookmark	FirstBookmark ()	const		{ return Bookmark{ _firstPacketOffset }; }
		ND_ Bookmark	LastBookmark ()		const		{ return Bookmark{ _lastPacketOffset }; }

		ND_ TraceRange  SubRange (const Bookmark &begin, const Bookmark &end) const;

		ND_ Iterator	Get (const Bookmark &bookmark) const;

		ND_ uint64_t	GetPositionInFile (const Iterator &iter, const void* hdr, const void* member) const;
		ND_ uint64_t	GetPositionInFile (const Bookmark &bookmark, const void* hdr, const void* member) const;

		ND_ bool		Contains (const Iterator &value) const;
		ND_ bool		Contains (const Bookmark &value) const;
	};
	


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

		if constexpr ( IsPointer<T> )
			return BitCast< const T >( _lastPacket->pBody );
		else
			return *BitCast< T const *>( _lastPacket->pBody );
	}

}	// VTC


namespace std
{
	template <>
	struct hash< VTC::TraceRange::Bookmark >
	{
		ND_ size_t  operator () (const VTC::TraceRange::Bookmark &value) const noexcept
		{
			return std::hash< decltype(value._offset) >()( value._offset );
		}
	};

}	// std
