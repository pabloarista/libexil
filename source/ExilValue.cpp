#include <ExilValue.h>
#include <ExilArray.h>
#include <ExilObject.h>

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
		mType = Types::String;
		mString = new char[_string.size() + 1];
		strncpy(mString, _string.c_str(), _string.size());
		mString[_string.size()] = 0;
	}

	Value::Value( bool val )
	{
		if(val)
			mType = Types::True;
		else
			mType = Types::False;
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

	bool Value::isNull()
	{
		return mType == Types::Null;
	}

	bool Value::isTrue()
	{
		return mType == Types::True;
	}

	bool Value::isFalse()
	{
		return mType == Types::False;
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
		switch(val->type())
		{
		case Value::Types::Number:
			os << "Number(" << val->toNumber<float>() << ")" << std::endl;
			break;
		case Value::Types::String:
			os << "String(" << val->toString() << ")" <<  std::endl;
			break;
		case Value::Types::True:
			os << "True" << std::endl;
			break;
		case Value::Types::False:
			os << "False" << std::endl;
			break;
		case Value::Types::Null:
			os << "Null" << std::endl;
			break;
		case Value::Types::Object:
			os << val->toObject() << std::endl;
			break;
		case Value::Types::Array:
			os << val->toArray() << std::endl;
			break;
		}
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
			case Value::Types::True:
				return "True";
			case Value::Types::False:
				return "False";
			case Value::Types::Null:
			default:
				return "Null";
			}

		}
	};//namespace Convert

};//namespace Exil

