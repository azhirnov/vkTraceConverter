// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

namespace VTPlayer
{

	//
	// Vulkan Unpacker
	//

	struct VUnpacker
	{
	// types
	public:
		using ResourceID		= uint64_t;
		using ResourceMap_t		= StaticArray< Array<ResourceID>, VkResourceTypes::Count >;
		using AfterCallFn_t		= void (VUnpacker::*) ();
		using Allocator_t		= LinearAllocator<>;

		static constexpr size_t		ResMapSize = std::tuple_size<ResourceMap_t>::value;


	// variables
	private:
		void *				_data;
		BytesU				_size;
		BytesU				_offset;
		ResourceMap_t&		_resources;

		// used for resource remapping after constructor call
		Allocator_t&		_allocator;
		AfterCallFn_t		_afterCall		= null;
		void *				_resourceIDs	= null;		// origin array with resource indices, used to map new handles to origin
		void *				_newVkHandles	= null;		// array where vulkan handles will be writen during constructor call
		uint				_resCount		= 0;


	// methods
	public:
		VUnpacker (void *data, BytesU size, BytesU offset, ResourceMap_t& resources, Allocator_t &alloc) :
			_data{data}, _size{size}, _offset{offset}, _resources{resources}, _allocator{alloc} {}

		~VUnpacker ();

		template <typename T>	decltype(auto)  Get (uint count = 1);

		template <typename T>	void			UnpackPtr (INOUT T &) const;
		template <typename T>	void			RemapVkResources (INOUT T*, uint) const;


	private:
		template <typename T>	T *			_GetPtr (T* ptr, uint count);
		template <typename T>	T const&	_GetRef ()					{ return *_GetPtr<T>( 1 ); }

		template <typename T>	T const*	_GetVkResources (T* src, uint count);
		template <typename T>	T *			_EditVkResources (T* src, uint count);

		template <typename T>	T			_RemapResource (T res) const;
		template <typename T>	T&			_EditResource (T res);

								void*		_Read (BytesU size, BytesU align);

		template <typename T>	void		_RemapAfterCall ();
	};
	
/*
=================================================
	destructor
=================================================
*/	
	VUnpacker::~VUnpacker ()
	{
		ASSERT( _offset == _size );

		if ( _afterCall )
			(this->*_afterCall)();
	}

/*
=================================================
	_Read
=================================================
*/
	ND_ void *  VUnpacker::_Read (BytesU size, BytesU align)
	{
		_offset = AlignToLarger( _offset, align );
		ASSERT( _offset <= _size );

		void *	result = _data + _offset;

		_offset += size;
		ASSERT( _offset <= _size );

		return result;
	}

/*
=================================================
	UnpackPtr
=================================================
*/
	template <typename T>
	void  VUnpacker::UnpackPtr (INOUT T& ptr) const
	{
		STATIC_ASSERT( IsPointer<T> );

		if ( ptr == T(~size_t(0)) )
		{
			const_cast< std::remove_const_t<T> &>(ptr) = null;
			return;
		}

		const_cast< std::remove_const_t<T> &>(ptr) = BitCast<T>( BitCast<size_t>(_data) + BitCast<size_t>(ptr) );

		ASSERT( ptr >= _data and ptr < _data + _size );
	}
	
/*
=================================================
	RemapVkResources
=================================================
*/
	template <typename T>
	void  VUnpacker::RemapVkResources (INOUT T* ptr, uint count) const
	{
		using B = std::remove_const_t<T>;
		STATIC_ASSERT( IsVkResource<B> );

		if ( ptr == null or count == 0 )
		{
			ptr = null;
			return;
		}
		
		for (uint i = 0; i < count; ++i)
		{
			const_cast<B &>( ptr[i] ) = _RemapResource( ptr[i] );
		}
	}

/*
=================================================
	_GetVkResources
=================================================
*/
	template <typename T>
	T const*  VUnpacker::_GetVkResources (T* ptr, uint count)
	{
		using B = std::remove_const_t<T>;
		STATIC_ASSERT( IsVkResource<B> );
		
		if ( ptr == null or count == 0 )
			return null;

		for (uint i = 0; i < count; ++i)
		{
			const_cast<B &>( ptr[i] ) = _RemapResource( ptr[i] );
		}
		return ptr;
	}
	
/*
=================================================
	_EditVkResources
=================================================
*/
	template <typename T>
	T *  VUnpacker::_EditVkResources (T* src, uint count)
	{
		STATIC_ASSERT( IsVkResource<T> );

		if ( src == null or count == 0 )
			return null;

		ASSERT( _resourceIDs == null and _resCount == 0 );
		
		_resourceIDs	= src;
		_resCount		= count;
		_afterCall		= &VUnpacker::_RemapAfterCall<T>;
		_newVkHandles	= _allocator.Alloc<T>( count );

		return static_cast<T *>( _newVkHandles );
	}
	
/*
=================================================
	_RemapAfterCall
=================================================
*/
	template <typename T>
	void  VUnpacker::_RemapAfterCall ()
	{
		ASSERT( _resourceIDs and _resCount );

		T *			idx = static_cast<T *>( _resourceIDs );
		const T*	src = static_cast<T *>( _newVkHandles );

		for (uint i = 0; i < _resCount; ++i)
		{
			_EditResource( idx[i] ) = src[i];
		}
	}

/*
=================================================
	_RemapResource
----
	map index to vulkan resource
=================================================
*/
	template <typename T>
	T  VUnpacker::_RemapResource (const T res) const
	{
		const auto	res_id = BitCast<NearUInt<T>>( res );

		if ( res_id == ~NearUInt<T>(0) )
			return VK_NULL_HANDLE;

		constexpr uint	index = VkResourceIndex<T>;
		STATIC_ASSERT( index < ResMapSize );

		ASSERT( res_id < _resources[index].size() );

		const T  result = BitCast<T>( _resources[index] [res_id] );
		ASSERT( result != VK_NULL_HANDLE );

		return result;
	}
	
/*
=================================================
	_EditResource
----
	map index to editable vulkan resource
=================================================
*/
	template <typename T>
	T&  VUnpacker::_EditResource (const T res)
	{
		const auto		res_id	= BitCast<NearUInt<T>>( res );
		constexpr uint	index	= VkResourceIndex<T>;

		STATIC_ASSERT( index < ResMapSize );
		ASSERT( res_id < _resources[index].size() );
		
		T&	result = BitCast<T>( _resources[index] [res_id] );

		return result;
	}

/*
=================================================
	Get
=================================================
*/
	template <typename T>
	ND_ decltype(auto)  VUnpacker::Get (uint count)
	{
		if constexpr ( IsVkResource< std::remove_const_t<T> > )
		{
			ASSERT( count == 1 );
			return *_GetVkResources<T>( static_cast<T *>(_Read( SizeOf<T>, AlignOf<T> )), 1 );
		}
		else
		if constexpr ( IsInteger<T> or IsEnum<T> or IsFloatPoint<T> )
		{
			ASSERT( count == 1 );
			return *static_cast<T *>(_Read( SizeOf<T>, AlignOf<T> ));
		}
		else
		if constexpr ( IsStaticArray<T> )
		{
			using B = std::remove_all_extents_t<T>;

			ASSERT( count > 0 );
			return static_cast<B *>(_Read( SizeOf<T>, AlignOf<B> ));
		}
		else
		if constexpr ( IsPointer<T> )
		{
			using B = std::remove_pointer_t<T>;
			using C = std::remove_const_t<B>;
			
			C*	ptr = *static_cast<C**>(_Read( SizeOf<T>, AlignOf<T> ));
			UnpackPtr( INOUT ptr );

			if constexpr ( IsVkResource<B> )
				return _EditVkResources<B>( ptr, count );
			else
			if constexpr ( IsVkResource<C> )
				return _GetVkResources<B>( ptr, count );
			else
			if constexpr ( IsPointer<B> ) {
				for (uint i = 0; i < count; ++i)
					UnpackPtr( INOUT ptr[i] );
				return ptr;
			}else
			if constexpr ( IsInteger<C> or IsEnum<C> or IsFloatPoint<C> or IsSameTypes<T, const void *> ) {
				ASSERT( (ptr != null) == (count > 0) );
				return ptr;
			}else{
				STATIC_ASSERT( IsClass<C> or IsUnion<C> );
				return _GetPtr( ptr, count );
			}
		}
		else
		{
			STATIC_ASSERT(false);
		}
	}

/*
=================================================
	_GetPtr<>
=================================================
*/
#	include "Generated/VulkanTraceStructUnpacker.h"

/*
=================================================
	operator <<
=================================================
*/
	template <typename T>
	void operator << (OUT T &dst, VUnpacker &self)
	{
		dst = self.Get<T>();
	}

/*
=================================================
	VUnpackStruct
=================================================
*/
# ifdef COMPILER_MSVC
#	pragma warning (push)
#	pragma warning (disable: 4100)
# endif

#	include "Generated/VulkanTraceStructUnpackerImpl.h"

# ifdef COMPILER_MSVC
#	pragma warning (pop)
# endif

}	// VTPlayer
