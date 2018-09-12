// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Common.h"
#include "vulkan/vulkan.h"
#include <sstream>
#include "../engine/FIValue.h"

namespace VTC
{
	using namespace std::string_literals;

/*
=================================================
	BoolToString
=================================================
*/
	ND_ inline String  BoolToString (VkBool32 value)
	{
		return value ? "true" : "false";
	}
	
/*
=================================================
	HexToString
=================================================
*/
	template <typename T>
	ND_ inline String  HexToString (const T &value)
	{
		auto&	ivalue = BitCast< NearUInt<T> >( value );

		std::stringstream	str;
		str << "0x" << std::hex << ivalue;
		
		if constexpr ( std::is_same_v< T, uint32_t > or (std::is_pointer_v<T> and sizeof(T) == sizeof(uint32_t)) )
			str << 'u';
		else if constexpr ( std::is_same_v< T, uint64_t > or (std::is_pointer_v<T> and sizeof(T) == sizeof(uint64_t)) )
			str << "ull";
		else if constexpr ( std::is_same_v< T, int64_t > )
			str << "ll";

		return str.str();
	}
	
/*
=================================================
	IntToString
=================================================
*/
	template <typename T>
	ND_ inline std::enable_if_t<std::is_integral_v<T>, String>  IntToString (const T &value)
	{
		String	str = ToString( value );

		if constexpr ( std::is_same_v< T, uint32_t > )
			str << 'u';
		else if constexpr ( std::is_same_v< T, uint64_t > )
			str << "ull";
		else if constexpr ( std::is_same_v< T, int64_t > )
			str << "ll";

		return str;
	}
	
/*
=================================================
	FloatToString
=================================================
*/
	ND_ inline String  FloatToString (float value)
	{
		// TODO
		return ToString( value ) << 'f';
	}
	
/*
=================================================
	WCharToString
=================================================
*/
# ifdef VULKAN_WIN32_H_
	ND_ inline String  WCharToString (LPCWSTR str)
	{
		STATIC_ASSERT( sizeof(str[0]) == 2 );	// 2 bytes in wchar

		std::wstring_view	ws{str};
		String				result	= "L\"";
		char				buf[]	= "\\x0000";

		for (auto& w : ws)
		{
			buf[2] = char((w >> 12) & 0xF);
			buf[3] = char((w >>  8) & 0xF);
			buf[4] = char((w >>  4) & 0xF);
			buf[5] = char((w)       & 0xF);

			result << buf;
		}
		result << "\"";

		return result;
	}
# endif
	
/*
=================================================
	EnumToString
=================================================
*/
	template <typename T>
	ND_ inline String  EnumToString (const T &value)
	{
		return ToString( BitCast<NearUInt<T>>( value ));
	}
	
/*
=================================================
	VoidToFIValueString
=================================================
*/
	ND_ String  VoidToFIValueString (const void *data, size_t offset)
	{
		FIValue		value;
		memcpy( &value, static_cast<const char*>(data) + offset, sizeof(value) );

		String	fstr = FloatToString( value.f );
		String	ustr = HexToString( value.u );

		if ( fstr.length() > ustr.length()+4 )
			return ustr;
		else
			return fstr;
	}


}	// VTC
