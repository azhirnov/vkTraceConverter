// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/Default/AllResourcesBookmarks.h"
#include "stl/CompileTime/TypeList.h"
#include "stl/Stream/MemStream.h"
#include <typeindex>

namespace VTC
{
#	include "IDs/EPacketIDs.h"
#	include "Types/VkResourceTypes.h"
#	include "Types/TracePacketHeader.h"



	//
	// Trace Packer
	//

	class TracePacker
	{
	// types
	private:
		using Buffer_t = Array<uint8_t>;

		struct ScopeInfo {
			const void *	ptr;
			Buffer_t		buf;
			size_t			align;
			int				structDepth	= 0;
		};

		using PointerStack_t = Array< ScopeInfo >;


	// variables
	private:
		AllResourcesBookmarks const*	_resBookmarks;
		TraceRange::Bookmark			_currentPos;
		bool							_useUniqueIndices;

		PointerStack_t					_pointerStack;
		EPacketID						_currPacket;

		Buffer_t						_tempData;
		MemWStream						_file;


	// methods
	public:
		TracePacker (const AllResourcesBookmarks *rbm, bool uniqueIndices);
		
		void SetCurrentPos (const TraceRange::Bookmark &pos)
		{
			_currentPos = pos;
		}

		template <typename T>	void operator << (const T &);

								void Begin (EPacketID);
								void End (EPacketID);

		template <typename T>	void Push (T const *);
		template <typename T>	void Pop (OUT T const* const &);
		template <typename T>	void PopAndStore (T const *);
							
		template <typename T>	void RemapVkResource (INOUT T const *);
								void AddArray (const void*, size_t size);
								void AddString (const char *);

								void BeginStruct ();
		template <typename T>	void EndStruct (const T &);

								void Clear ();
								void Flush ();

		ND_ ArrayView<uint8_t>	GetData () const	{ return _file.GetData(); }


	private:
		template <typename T>	void _AddBasicType (const T &);
		template <typename T>	void _AddVkResource (T id);
		template <typename T>	void _AddPointer (const T &);

		void _Store (const void *data, size_t size, size_t align);
		void _PopAndPackPtr (OUT size_t &);
	};

	
/*
=================================================
	operator <<
=================================================
*/
	template <typename T>
	inline void TracePacker::operator << (const T &value)
	{
		if constexpr ( IsVkResource<T> )
			return _AddVkResource( value );
		else
		if constexpr ( IsPointer<T> )
			return _AddPointer( value );
		else
		if constexpr ( IsEnum<T> or IsInteger<T> or IsFloatPoint<T> )
			return _AddBasicType( value );
		else
			STATIC_ASSERT( false );
	}
	
/*
=================================================
	Push
=================================================
*/
	template <typename T>
	inline void TracePacker::Push (const T *obj)
	{
		_pointerStack.push_back({ obj, {}, alignof(T) });
	}

	template <>
	inline void TracePacker::Push (const void *obj)
	{
		_pointerStack.push_back({ obj, {}, alignof(void*) });
	}
	
/*
=================================================
	Pop
=================================================
*/
	template <typename T>
	inline void TracePacker::Pop (OUT T const* const& obj)
	{
		ASSERT( not _pointerStack.empty() );
		ASSERT( _pointerStack.back().ptr == obj );

		_PopAndPackPtr( OUT BitCast<size_t>( const_cast<T const*&>(obj) ) );
	}
	
/*
=================================================
	PopAndStore
=================================================
*/
	template <typename T>
	inline void TracePacker::PopAndStore (T const *obj)
	{
		ASSERT( not _pointerStack.empty() );
		ASSERT( _pointerStack.back().ptr == obj );

		size_t	value = BitCast<size_t>(obj);
		_PopAndPackPtr( OUT value );

		_Store( &value, sizeof(value), alignof(size_t) );
	}

/*
=================================================
	_AddBasicType
=================================================
*/
	template <typename T>
	inline void TracePacker::_AddBasicType (const T &value)
	{
		_Store( &value, sizeof(value), alignof(T) );
	}
	
/*
=================================================
	_AddVkResource
=================================================
*/
	template <typename T>
	inline void TracePacker::_AddVkResource (T id)
	{
		RemapVkResource( INOUT &id );
		_Store( &id, sizeof(id), alignof(T) );
	}
	
/*
=================================================
	RemapVkResource
=================================================
*/
	template <typename T>
	inline void TracePacker::RemapVkResource (INOUT T const* id)
	{
		ASSERT( id != null );
		T&	result = *const_cast<T *>( id );

		if ( result == VK_NULL_HANDLE ) {
			result = T(~0ull);
			return;
		}

		auto*	res_info = _resBookmarks->GetResource( GetVkResourceType<T>(), ResourceID(result), _currentPos );

		if ( not res_info ) {
			result = T(~0ull);
			return;
		}

		if ( _useUniqueIndices ) {
			CHECK_ERR( res_info->uniqueIndex != ~0ull, void());
			result = T(res_info->uniqueIndex);
		}else{
			CHECK_ERR( res_info->localIndex != ~0ull, void());
			result = T(res_info->localIndex);
		}
	}
	
/*
=================================================
	_AddPointer
=================================================
*/
	template <typename T>
	inline void TracePacker::_AddPointer (const T &value)
	{
		ASSERT( value == null );	// use Push/Pop to store pointer + data

		size_t	ptr = ~size_t(0);
		_Store( &ptr, sizeof(ptr), alignof(T) );
	}
	
/*
=================================================
	BeginStruct
=================================================
*/
	inline void TracePacker::BeginStruct ()
	{
		++(_pointerStack.back().structDepth);
	}

/*
=================================================
	EndStruct
=================================================
*/
	template <typename T>
	inline void TracePacker::EndStruct (const T &obj)
	{
		STATIC_ASSERT( (IsClass<T> or IsUnion<T>) and IsPOD<T> );
		ASSERT( _pointerStack.back().structDepth > 0 );

		if ( --(_pointerStack.back().structDepth) > 0 )
			return;

		_Store( &obj, sizeof(obj), alignof(T) );
	}


}	// VTC
