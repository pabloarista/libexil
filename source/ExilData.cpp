#include "ExilData.h"

namespace Exil
{
	namespace Data
	{

#pragma region Object

		Object::Object( Reader* reader )
		{
			if(mType != Types::Object)
				throw "Not an Object";

			mSystem = reader;
		}

		Object::Object( Writer* writer )
		{
			mType = Types::Object;
			mNumItems = 0;
			mSystem = writer;
		}

		Exil::SizeT Object::getNumItems()
		{
			return mNumItems;
		}

		Exil::SizeT Object::Size( SizeT len )
		{
			return sizeof(Object);
		}

#pragma endregion Object
#pragma region Array

		Array::Array( Reader* reader )
		{
			if(mType != Types::Array)
				throw "Not an Array";
			mSystem = reader;
		}

		Array::Array( Writer* writer ) : mType(Types::Array), mNumItems(0)
		{
			mSystem = writer;
		}

		Exil::SizeT Array::getValue()
		{
			return mNumItems;
		}

		Exil::SizeT Array::Size( SizeT len )
		{
			return sizeof(Array);
		}

#pragma endregion Array
#pragma region String

		String::String()
		{
			if(mType != Types::String)
				throw "Not a String";
		}

		String::String( const char* str, SizeT len )
		{
			mType = Types::String;
			char* value = reinterpret_cast<char*>(&mType) + sizeof(mType);
			memcpy(value, str, len);
		}

		String::String( const std::string& str )
		{
			mType = Types::String;
			char* value = reinterpret_cast<char*>(&mType) + sizeof(mType);
			memcpy(value, str.c_str(), str.size());
		}

		const char* String::getValue()
		{
			return reinterpret_cast<char*>(&mType) + sizeof(InternalType);
		}

		Exil::SizeT String::getLength()
		{
			return *(reinterpret_cast<SizeT*>(&mType) - sizeof(InternalType)) - sizeof(InternalType);
		}

		Exil::SizeT String::Size( SizeT len )
		{
			return sizeof(InternalType) + len;
		}

#pragma endregion String
#pragma region Float

		Float::Float()
		{
			if(mType != Types::Float)
				throw "Not a Float!";
		}

		Float::Float( float f )
		{
			mType = Types::Float;
			mValue = f;
		}

#pragma endregion Float
#pragma region Integer

		Integer::Integer()
		{
			if(mType != Types::Integer)
				throw "Not an Integer";
		}

		Integer::Integer( int i )
		{
			mType = Types::Integer;
			mValue = i;
		}

#pragma endregion Integer
#pragma region Boolean

		Boolean::Boolean()
		{
			if(mType != Types::Boolean)
				throw "Not a Boolean";
		}

		Boolean::Boolean( bool b )
		{
			mType = Types::Boolean;
			mValue = b;
		}
#pragma endregion Boolean

	}//namespace Data

}//namespace Exil
