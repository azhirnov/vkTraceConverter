// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "stl/include/ArrayView.h"
#include "stl/include/FixedArray.h"
#include "stl/include/DefaultType.h"
#include "stl/include/StringUtils.h"
#include "stl/include/File.h"

#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"

#include <filesystem>

namespace VTC
{
	using namespace FG;
	namespace fs = std::filesystem;


	//
	// VkTrace Helpers Generator
	//

	class Generator
	{
	// types
	public:
		enum class EFuncScope
		{
			Unknown,
			Library,
			Instance,
			Device,
		};


		struct FuncArg
		{
		// variables
			Array<StringView>	type;
			StringView			name;

		// methods
			FuncArg () {}
			explicit FuncArg (StringView name) : name{name} {}
		};


		struct VkFunctionInfo
		{
		// variables
			StringView			name;
			FuncArg				result;
			Array<FuncArg>		args;
			uint				fileIndex	= ~0u;
			mutable EFuncScope	scope		= EFuncScope::Unknown;
			mutable bool		required	= false;

		// methods
			VkFunctionInfo () {}
		};


		struct EnumField
		{
			StringView			name;
			StringView			value;
		};


		struct VkEnumInfo
		{
		// variables
			StringView			name;
			Array<EnumField>	fields;
			uint				fileIndex	= ~0u;
			mutable bool		required	= false;

		// methods
			VkEnumInfo () {}
		};


		struct VkBitfieldInfo
		{
		// variables
			StringView			name;
			StringView			enumName;
			uint				fileIndex	= ~0u;
			mutable bool		required	= false;

		// methods
			VkBitfieldInfo () {}
		};


		struct VkStructInfo
		{
		// variables
			StringView			name;
			Array<FuncArg>		fields;
			uint				fileIndex	= ~0u;
			mutable bool		required	= false;

		// methods
			VkStructInfo () {}
		};


		struct SearchableFunc
		{
		// variables
			VkFunctionInfo		data;

		// methods
			SearchableFunc () {}
			SearchableFunc (const VkFunctionInfo &data) : data{data} {}
			explicit SearchableFunc (StringView name) { data.name = name; }

			ND_ bool  operator == (const SearchableFunc &right) const	{ return data.name == right.data.name; }
			ND_ bool  operator >  (const SearchableFunc &right) const	{ return data.name >  right.data.name; }
		};
	
		struct SearchableFuncHash {
			ND_ size_t  operator () (const SearchableFunc &value) const {
				return size_t(HashOf( value.data.name ));
			}
		};


		struct SearchableEnum
		{
		// variables
			VkEnumInfo			data;

		// methods
			SearchableEnum () {}
			SearchableEnum (const VkEnumInfo &data) : data{data} {}
			explicit SearchableEnum (StringView name) { data.name = name; }

			ND_ bool  operator == (const SearchableEnum &right) const	{ return data.name == right.data.name; }
			ND_ bool  operator >  (const SearchableEnum &right) const	{ return data.name >  right.data.name; }
		};

		struct SearchableEnumHash {
			ND_ size_t  operator () (const SearchableEnum &value) const {
				return size_t(HashOf( value.data.name ));
			}
		};


		struct SearchableBitfield
		{
		// variables
			VkBitfieldInfo		data;

		// methods
			SearchableBitfield () {}
			SearchableBitfield (const VkBitfieldInfo &data) : data{data} {}
			explicit SearchableBitfield (StringView name) { data.name = name; }

			ND_ bool  operator == (const SearchableBitfield &right) const	{ return data.name == right.data.name; }
			ND_ bool  operator >  (const SearchableBitfield &right) const	{ return data.name >  right.data.name; }
		};

		struct SearchableBitfieldHash {
			ND_ size_t  operator () (const SearchableBitfield &value) const {
				return size_t(HashOf( value.data.name ));
			}
		};


		struct SearchableStruct
		{
		// variables
			VkStructInfo		data;

		// methods
			SearchableStruct () {}
			SearchableStruct (const VkStructInfo &data) : data{data} {}
			explicit SearchableStruct (StringView name) { data.name = name; }

			ND_ bool  operator == (const SearchableStruct &right) const	{ return data.name == right.data.name; }
			ND_ bool  operator >  (const SearchableStruct &right) const	{ return data.name >  right.data.name; }
		};

		struct SearchableStructHash {
			ND_ size_t  operator () (const SearchableStruct &value) const {
				return size_t(HashOf( value.data.name ));
			}
		};


		struct FileInfo
		{
		// variables
			String		data;
			String		macro;

		// methods
			FileInfo () {}
			FileInfo (String &&data, StringView macro) : data{std::move(data)}, macro{macro} {}
		};


		enum class EBasicType
		{
			Void,
			Bool,
			Char,
			Int,
			UInt,
			USize,
			Long,
			ULong,
			Float,
			Handle,
			Struct,
			WCharString,
		};


		using FuncMap_t			= HashSet< SearchableFunc, SearchableFuncHash >;
		using EnumMap_t			= HashSet< SearchableEnum, SearchableEnumHash >;
		using BitfieldMap_t		= HashSet< SearchableBitfield, SearchableBitfieldHash >;
		using StructMap_t		= HashSet< SearchableStruct, SearchableStructHash >;
		using CounterMap_t		= HashMap< Pair<StringView, StringView>, StringView >;
		using DestructorSet_t	= HashSet< Pair<StringView, StringView> >;
		using BasicTypeMap_t	= HashMap< StringView, EBasicType >;
		using FileDataArray_t	= FixedArray< FileInfo, 16 >;
	
	
		struct PacketInfo
		{
			String		id;
			String		suffix;
			String		vkFunc;
		};
		using PacketIDs_t		= Array< PacketInfo >;

		using EResourceType		= VkDebugReportObjectTypeEXT;


		struct ResourceTypeInfo
		{
			EResourceType		type;
			String				typeName;
		};
		using ResourceTypes_t	= HashMap< StringView, ResourceTypeInfo >;
		

		struct TypeInfo
		{
			StructMap_t::const_iterator			structInfo;
			EnumMap_t::const_iterator			enumInfo;
			BitfieldMap_t::const_iterator		bitfieldInfo;
			ResourceTypes_t::const_iterator		resInfo;
			BasicTypeMap_t::const_iterator		basicInfo;

			uint								numPointers	= 0;
			bool								isArray		= false;
			bool								isConst		= false;
			bool								hasSType	= false;
			bool								isField		= true;
		};


	// variables
	private:
		FileDataArray_t			_fileData;

		FuncMap_t				_funcs;
		EnumMap_t				_enums;
		BitfieldMap_t			_bitfields;
		StructMap_t				_structs;

		PacketIDs_t				_packetIDs;
		ResourceTypes_t			_resourceTypes;
		BasicTypeMap_t			_basicTypes;

		HashSet<StringView>		_skipPackets;		// skip all vkGet*** functions
		HashSet<StringView>		_alwaysSerialize;	// define any type name that be always serialized
		HashSet<StringView>		_neverSerialize;

		CounterMap_t			_funcArgCountOf;
		CounterMap_t			_funcArgCounter;

		CounterMap_t			_structFieldCountOf;
		CounterMap_t			_structFieldCounter;

		DestructorSet_t			_funcArgDestructors;


	// methods
	public:
		Generator () {}

		bool ParseVkHeaders (const fs::path &folder);
		bool ParsePacketIDs (const fs::path &filename);
		bool BuildBasicTypeMap ();
		bool BuildResourceTypeMap ();
		bool BuildFuncArgCountOfMap ();
		bool BuildFuncArgDestructorMap ();
		bool BuildStructFieldCountOfMap ();
		bool BuildSkipPacketsMap ();
		bool SetFunctionsScope ();

		bool GenBookmarksForFunc (const fs::path &output) const;
		bool GenBookmarksForStruct (const fs::path &output) const;

		bool MarkRequiredTypesForUnpack () const;
		bool MarkRequiredTypesForSerializing () const;

		bool GenEnumToString (const fs::path &headerFile, const fs::path &sourceFile) const;
		bool GenStructToString (const fs::path &headerFile, const fs::path &sourceFile) const;
		bool GenStructTypeHelpers (const fs::path &output) const;

		bool GenUnpacker (const fs::path &output) const;

		bool GenRawVulkanCalls (const fs::path &output) const;

		bool GenVulkanTracePacker (const fs::path &packetIDsFile, const fs::path &structHeaderFile,
								   const fs::path &structSourceFile, const fs::path &funcFile) const;

		bool GenVulkanTracePlayer (const fs::path &structHeaderFile, const fs::path &structSourceFile,
								   const fs::path &funcFile) const;


	private:
		bool _GenBookmarks_ProcessPacket (const PacketInfo &packet, OUT String &str) const;
		bool _GenBookmarks_AddResource (StringView vkFunc, const FuncArg &arg, INOUT String &str) const;
		bool _GenBookmarks_AddStructResources (const VkStructInfo &info, uint level, uint mode, StringView fieldName, OUT String &str) const;

		static StringView  _FindStructTypeEnum (StringView structType, INOUT Array<Generator::EnumField> &values);
	
		bool _GenUnpacker_ForFunc (OUT String &str) const;
		bool _GenUnpacker_ForStruct (OUT String &str) const;
		bool _GenUnpacker_ProcessPacket (const PacketInfo &packet, OUT String &str) const;
		bool _GenUnpacker_ProcessStruct (const VkStructInfo &info, OUT String &str) const;
		bool _GenUnpacker_ProcessStruct2 (const VkStructInfo &info, OUT String &str) const;
		bool _GenUnpacker_UnpackType (StringView parentName, StringView fieldName, ArrayView<StringView> typeParts,
									  StringView counterName, StringView indent, OUT String &str) const;
	
		bool _GenStructToString_ProcessStruct (const VkStructInfo &info, StringView stype, OUT String &str) const;
		bool _GenStructToString_ProcessVar (StringView fieldName, ArrayView<StringView> fieldType, StringView indent, StringView counterName,
											bool isField, INOUT String &str, INOUT String &beforeStr, INOUT String &afterStr) const;
		
		bool _SerializeSingleObject (const TypeInfo &t, StringView fieldName, StringView indent, INOUT String &str, INOUT String &beforeStr) const;
		
		bool _SerializeOutputObject (const TypeInfo &t, StringView fieldName, StringView indent, StringView counter,
									   INOUT String &str, INOUT String &beforeStr, INOUT String &afterStr) const;
		
		bool _SerializePointerToObject (const TypeInfo &t, StringView fieldName, StringView indent, StringView counter,
										INOUT String &str, INOUT String &beforeStr) const;
		
		bool _SerializePointerToPointerToObject (const TypeInfo &t, StringView fieldName, StringView indent, StringView counter,
												 INOUT String &str, INOUT String &beforeStr) const;

		bool _GenRawVulkanCalls_ProcessPacket (const PacketInfo &packet, OUT String &str) const;
	
		bool _MarkRequiredTypes (bool forSerialization) const;
		bool _MarkRequiredTypes_ProcessVar (ArrayView<StringView> type, bool forSerialization) const;

		ND_ ResourceTypeInfo const*  _GetResourceType (StringView typeName) const;

		ND_ StringView  _GetFuncArgCounterName (StringView func, StringView argName) const;
		ND_ StringView  _GetStructFieldCounterName (StringView structType, StringView fieldName) const;
		
		ND_ bool  _IsFuncArgCounter (StringView func, StringView counterName) const;
		ND_ bool  _IsStructFieldCounter (StringView structType, StringView counterName) const;

		ND_ bool  _IsFuncArgWillBeDestroyed (StringView func, StringView argName) const;

		ND_ static bool _HasSType (const VkStructInfo &st);

		ND_ static bool _IsWord (StringView value);
		ND_ static bool _IsTypeOrQual (StringView value);
		ND_ static bool _IsNumber (StringView value);

		static bool _GenerateVK1 (StringView fileData,
								  const uint fileIndex,
								  ArrayView< StringView > enableIfdef,
								  ArrayView< StringView > disableIfdef,
								  bool defaultSkip,
								  INOUT FuncMap_t &outFunctions,
								  INOUT EnumMap_t &outEnums,
								  INOUT StructMap_t &outStructs,
								  INOUT BitfieldMap_t &outBitfields);

		ND_ static HashSet<StringView> const&  _GetRequiredForPackingFunctionsV1 ();
		ND_ static HashSet<StringView> const&  _GetRequiredForPackingStructures ();	// only structures that used as pNext extension

		ND_ static bool _IsRequiredForPackingFunction (StringView vkFunc);
		
		ND_ static String  _GenPacketIDName (StringView vkFunc);

		bool _VulkanTracePacker_MarkRequiredTypes () const;
		bool _VulkanTracePacker_MarkRequiredTypes (ArrayView<StringView> types) const;
		bool _VulkanTracePacker_GenIDs (const fs::path &output) const;
		bool _VulkanTracePacker_GenStructPacker (const fs::path &headerFile, const fs::path &sourceFile) const;
		bool _VulkanTracePacker_GenFuncPacker (const fs::path &output) const;
		bool _VulkanTracePacker_ProcessStruct (const VkStructInfo &info, StringView stype, OUT String &str) const;
		bool _VulkanTracePacker_ProcessVar (StringView fieldName, ArrayView<StringView> fieldType, StringView indent,
											StringView counterName, bool isField, INOUT String &str) const;
		
		bool _VulkanTracePlayer_GenStructUnpacker (const fs::path &headerFile, const fs::path &sourceFile) const;
		bool _VulkanTracePlayer_GenFuncUnpacker (const fs::path &output) const;
		bool _VulkanTracePlayer_ProcessStruct (const VkStructInfo &info, StringView stype, OUT String &str) const;
		bool _VulkanTracePlayer_UnpackType (StringView parentName, StringView fieldName, ArrayView<StringView> typeParts,
											StringView counterName, StringView indent, OUT String &str) const;
	};

}	// VTC
