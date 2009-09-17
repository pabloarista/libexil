#include <ExilValue.h>
#include <ExilArray.h>
#include <ExilObject.h>

namespace Exil
{
	Value::Value( float num )
	{
		type = Types::Number;
		number = num;
	}

	Value::Value( int num )
	{
		type = Types::Number;
		number = static_cast<float>(num);
	}

	Value::Value( String _string )
	{
		type = Types::String;
		string = new char[_string.size() + 1];
		strncpy(string, _string.c_str(), _string.size());
		string[_string.size()] = 0;
	}

	Value::Value( bool val )
	{
		if(val)
			type = Types::True;
		else
			type = Types::False;
	}

	Value::Value()
	{
		type = Types::Null;
	}

	Value::~Value()
	{
		if(type == Types::String)
			delete string;
	}

	bool Value::isNull()
	{
		return type == Types::Null;
	}

	bool Value::isTrue()
	{
		return type == Types::True;
	}

	bool Value::isFalse()
	{
		return type == Types::False;
	}

	char* Value::toString()
	{
		return string;
	}

	Object* Value::toObject()
	{
		if(type == Types::Object)
			return static_cast<Object*>(this);

		return NULL;
	}

	Array* Value::toArray()
	{
		if(type == Types::Array)
			return static_cast<Array*>(this);

		return NULL;
	}
	std::ostream& operator<< (std::ostream& os, Value* val)
	{
		switch(val->type)
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

