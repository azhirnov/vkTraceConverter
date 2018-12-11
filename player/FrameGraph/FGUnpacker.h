// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

namespace VTPlayer
{

	//
	// FrameGraph Unpacker
	//

	struct FGUnpacker
	{
	// variables
	private:
		void *		_data;
		BytesU		_size;
		BytesU		_offset;


	// methods
	public:
		FGUnpacker (void *data, BytesU size, BytesU offset) :
			_data{data}, _size{size}, _offset{offset} {}

		~FGUnpacker ();
		
		template <typename T>	void			UnpackPtr (INOUT T &) const;
		template <typename T>	decltype(auto)  Get (uint count = 1);
		template <typename T>	decltype(auto)	GetArray (uint count);


		template <typename T>
		friend EnableIf<IsInteger<T> or IsEnum<T> or IsFloatPoint<T>, void>  operator << (OUT T &value, FGUnpacker &unpacker)
		{
			value = *static_cast<T *>(unpacker._Read( SizeOf<T>, AlignOf<T> ));
		}
		

		template <size_t Size, uint UID>
		friend void operator << (OUT _fg_hidden_::IDWithString<Size,UID> &value, FGUnpacker &unpacker)
		{
			memcpy( &value, unpacker._Read( BytesU::SizeOf(value), BytesU::AlignOf(value) ), sizeof(value) );
		}


	private:
		void*  _Read (BytesU size, BytesU align);
	};
	
/*
=================================================
	destructor
=================================================
*/	
	inline FGUnpacker::~FGUnpacker ()
	{
		ASSERT( _offset == _size );
	}

/*
=================================================
	_Read
=================================================
*/
	ND_ inline void *  FGUnpacker::_Read (BytesU size, BytesU align)
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
	inline void  FGUnpacker::UnpackPtr (INOUT T& ptr) const
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
	Get
=================================================
*/
	template <typename T>
	ND_ inline decltype(auto)  FGUnpacker::Get (uint count)
	{
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
	GetArray
=================================================
*/
	template <typename T>
	ND_ inline decltype(auto)  FGUnpacker::GetArray (uint count)
	{
		ASSERT( count > 0 );
		return static_cast<T *>(_Read( SizeOf<T> * count, AlignOf<void *> ));
	}


}	// VTPlayer
