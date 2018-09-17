// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

namespace VTC
{

/*
=================================================
	_MarkRequiredTypes_ProcessVar
=================================================
*/
	bool Generator::_MarkRequiredTypes_ProcessVar (ArrayView<StringView> types) const
	{			
		for (auto& type : types)
		{
			auto struct_info = _structs.find( SearchableStruct{type} );
			if ( struct_info != _structs.end() )
			{
				if ( struct_info->data.required )
					return false;

				struct_info->data.required = true;

				for (auto& field : struct_info->data.fields)
				{
					_MarkRequiredTypes_ProcessVar( field.type );
				}
				return true;
			}

			auto enum_info = _enums.find( SearchableEnum{type} );
			if ( enum_info != _enums.end() )
			{
				if ( enum_info->data.required )
					return false;

				enum_info->data.required = true;
				return true;
			}

			auto bitfield_info = _bitfields.find( SearchableBitfield{type} );
			if ( bitfield_info != _bitfields.end() )
			{
				if ( bitfield_info->data.required )
					return false;

				bitfield_info->data.required = true;

				enum_info = _enums.find( SearchableEnum{bitfield_info->data.enumName} );
				if ( enum_info != _enums.end() )
				{
					enum_info->data.required = true;
				}
				return true;
			}
		}
		return false;
	}

/*
=================================================
	_MarkRequiredTypes
=================================================
*/
	bool Generator::_MarkRequiredTypes (bool forSerialization) const
	{
		// reset all
		for (auto& en : _enums)
		{
			en.data.required = (forSerialization and _alwaysSerialize.find( en.data.name ) != _alwaysSerialize.end());
		}

		for (auto& bf : _bitfields)
		{
			bf.data.required = (forSerialization and _alwaysSerialize.find( bf.data.name ) != _alwaysSerialize.end());
		
			auto	enum_info = _enums.find( SearchableEnum{bf.data.enumName} );

			if ( bf.data.required and enum_info != _enums.end() )
				enum_info->data.required = true;
		}

		for (auto& st : _structs)
		{
			st.data.required = (forSerialization and _alwaysSerialize.find( st.data.name ) != _alwaysSerialize.end());
		
			if ( st.data.required ) {
				for (auto& field : st.data.fields) {
					_MarkRequiredTypes_ProcessVar( field.type );
				}
			}
		}

		for (auto& func : _funcs)
		{
			func.data.required = (forSerialization and _alwaysSerialize.find( func.data.name ) != _alwaysSerialize.end());

			if ( func.data.required ) {
				for (auto& arg : func.data.args) {
					_MarkRequiredTypes_ProcessVar( arg.type );
				}
			}
		}


		for (auto& packet : _packetIDs)
		{
			if ( packet.vkFunc.empty() )
				continue;

			if ( forSerialization and _skipPackets.find( packet.id ) != _skipPackets.end() )
				continue;
		
			auto	func_info = _funcs.find( SearchableFunc{packet.vkFunc} );
			CHECK_ERR( func_info != _funcs.end() );

			func_info->data.required = true;

			for (auto& arg : func_info->data.args)
			{
				_MarkRequiredTypes_ProcessVar( arg.type );
			}
		}

		return true;
	}

/*
=================================================
	MarkRequiredTypesForUnpack
=================================================
*/
	bool Generator::MarkRequiredTypesForUnpack () const
	{
		return _MarkRequiredTypes( false );
	}

/*
=================================================
	MarkRequiredTypesForSerializing
=================================================
*/
	bool Generator::MarkRequiredTypesForSerializing () const
	{
		return _MarkRequiredTypes( true );
	}

}	// VTC
