#include <ExilValue.h>
#include <ExilArray.h>
#include <ExilObject.h>
#include <ExilDataStream.h>

namespace Exil
{
	Value::Value( float num )
	{
		mType = Types::Number;
		mNumber = num;
	}

	Value::Value( int num )
	{
		mType = Types::Number;
		mNumber = static_cast<float>(num);
	}

	Value::Value( String _string )
	{
		_setString(_string.c_str(), _string.size());
	}

	Value::Value( const char* str )
	{
		_setString(str, strlen(str));
	}

	Value::Value( const char* str, size_t size )
	{
		_setString(str, size);
	}

	Value::Value( bool val )
	{
		mType = Types::Bool;
		mBool = val;
	}

	Value::Value()
	{
		mType = Types::Null;
	}

	Value::~Value()
	{
		if(mType == Types::String)
			delete mString;
	}

	void Value::_setString(const char* str, size_t size)
	{
		mType = Types::String;
		mString = new char[size + 1];
		strncpy(mString, str, size);
		mString[size] = 0;
	}

	bool Value::isNull()
	{
		return mType == Types::Null;
	}

	bool Value::toBool()
	{
		if(mType != Types::Bool)
			throw ConversionException();

		return mBool;
	}

	char* Value::toString()
	{
		return mString;
	}

	Object* Value::toObject()
	{
		if(mType != Types::Object)
			throw ConversionException();

		return static_cast<Object*>(this);
	}

	Array* Value::toArray()
	{
		if(mType != Types::Array)
			throw ConversionException();

		return static_cast<Array*>(this);
	}

	std::ostream& operator<< (std::ostream& os, Value* val)
	{
		dsout << val;
		//switch(val->type())
		//{
		//case Value::Types::Number:
		//	os << "Number(" << val->toNumber<float>() << ")" << std::endl;
		//	break;
		//case Value::Types::String:
		//	os << "String(" << val->toString() << ")" <<  std::endl;
		//	break;
		//case Value::Types::Bool:
		//	if(val->toBool())
		//		os << "True" << std::endl;
		//	else
		//		os << "False" << std::endl;
		//	break;
		//case Value::Types::Null:
		//	os << "Null" << std::endl;
		//	break;
		//case Value::Types::Object:
		//	os << val->toObject() << std::endl;
		//	break;
		//case Value::Types::Array:
		//	os << val->toArray() << std::endl;
		//	break;
		//}
		return os;
	}

	namespace Convert
	{
		String toString(Value::Type type)
		{
			switch(type)
			{
			case Value::Types::Array:
				return "Array";
			case Value::Types::Object:
				return "Object";
			case Value::Types::String:
				return "String";
			case Value::Types::Number:
				return "Number";
			case Value::Types::Bool:
				return "Bool";
			case Value::Types::Null:
			default:
				return "Null";
			}
		}

		Value::Type toValueType(const String& str)
		{
			if(str == "Array")
				return Value::Types::Array;
			if(str == "Object")
				return Value::Types::Object;
			if(str == "String")
				return Value::Types::String;
			if(str == "Number")
				return Value::Types::Number;
			if(str == "Bool")
				return Value::Types::Bool;
			if(str == "Null")
				return Value::Types::Null;

			throw ConversionException();
		}

	};//namespace Convert

};//namespace Exil

