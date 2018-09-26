// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/IDs/EPacketIDs.h"
#include "Analyzer/Default/AllResourcesBookmarks.h"
#include "Converters/Utils/VkResourceType.h"
#include <typeindex>

namespace VTC
{

	//
	// Trace Packer
	//

	class TracePacker
	{
	// types
	private:
		using Buffer_t			= Array<uint8_t>;
		using StructStack_t		= Array<Pair< const void*, std::type_index >>;
		using PointerStack_t	= Array<Pair< const void*, Buffer_t >>;


	// variables
	private:
		AllResourcesBookmarks const*	_resBookmarks;
		TraceRange::Bookmark			_currentPos;

		StructStack_t					_structStack;	// used for error checking
		PointerStack_t					_pointerStack;
		EPacketID						_currPacket;

		Buffer_t						_tempData;
		Buffer_t						_packedData;


	// methods
	public:
		explicit TracePacker (const AllResourcesBookmarks *rbm);
		
		void SetCurrentPos (const TraceRange::Bookmark &pos)
		{
			_currentPos = pos;
		}

		template <typename T>	void operator << (const T &);
		//template <typename T>	void SetOutput (T *data);
		//template <typename T>	void SetOutput (T *data, size_t count);

		template <typename T>	void BeginStruct (const T *);
		template <typename T>	void EndStruct (const T *);

								void Begin (EPacketID);
								void End (EPacketID);

		template <typename T>	void Push (const T *);
		template <typename T>	void Push (const T *, size_t count);
		template <typename T>	void Pop (const T *);
							
								void SetArray (const void*, size_t size);

								void Clear ();
								void Flush ();

		ND_ ArrayView<uint8_t>		GetPackedData () const	{ return _packedData; }


	private:
		template <typename T>	void _AddBasicType (const T &);
		template <typename T>	void _AddVkResource (const T &);
		template <typename T>	void _AddPointer (const T &);

		void _Store (const void *data, size_t size);
		void _PopAndStorePtr ();
	};

	
/*
=================================================
	operator <<
=================================================
*/
	template <typename T>
	inline void TracePacker::operator << (const T &value)
	{
		if constexpr ( IsVkResource<T>::value )
			return _AddVkResource( value );
		else
		if constexpr ( std::is_pointer_v<T> )
			return _AddPointer( value );
		else
		if constexpr ( std::is_enum_v<T> or std::is_integral_v<T> or std::is_floating_point_v<T> )
			return _AddBasicType( value );
		else
			STATIC_ASSERT( false );
	}

/*
=================================================
	BeginStruct
=================================================
*/
	template <typename T>
	inline void TracePacker::BeginStruct (const T *obj)
	{
		STATIC_ASSERT( std::is_class_v<T> or std::is_union_v<T> );

		DEBUG_ONLY( _structStack.push_back({ Cast<void>( obj ), typeid(T) }) );
	}
	
/*
=================================================
	EndStruct
=================================================
*/
	template <typename T>
	inline void TracePacker::EndStruct (const T *obj)
	{
		ASSERT( _structStack.size() > 0 );
		ASSERT( _structStack.back().first == obj );
		ASSERT( _structStack.back().second == typeid(T) );

		DEBUG_ONLY( _structStack.pop_back() );
	}
	
/*
=================================================
	Push
=================================================
*/
	template <typename T>
	inline void TracePacker::Push (const T *obj)
	{
		_pointerStack.push_back({ obj, {} });
	}
	
/*
=================================================
	Push
=================================================
*/
	template <typename T>
	inline void TracePacker::Push (const T *obj, size_t)
	{
		_pointerStack.push_back({ obj, {} });
	}
	
/*
=================================================
	Pop
=================================================
*/
	template <typename T>
	inline void TracePacker::Pop (const T *obj)
	{
		ASSERT( not _pointerStack.empty() );
		ASSERT( _pointerStack.back().first == obj );

		_PopAndStorePtr();
	}
	
/*
=================================================
	_AddBasicType
=================================================
*/
	template <typename T>
	inline void TracePacker::_AddBasicType (const T &value)
	{
		_Store( &value, sizeof(value) );
	}
	
/*
=================================================
	_AddVkResource
=================================================
*/
	template <typename T>
	inline void TracePacker::_AddVkResource (const T &)
	{
		// TODO: remap and store
	}
	
/*
=================================================
	_AddPointer
=================================================
*/
	template <typename T>
	inline void TracePacker::_AddPointer (const T &value)
	{
		ASSERT( value == null );
		_Store( &value, sizeof(value) );
	}


}	// VTC
