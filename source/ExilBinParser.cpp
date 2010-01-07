#include <ExilBinParser.h>
#include <ExilValue.h>
#include <ExilArray.h>
#include <ExilObject.h>

#ifdef UPGRADE_COMPLETE

namespace Exil
{
	BinParser::BinParser( std::istream& stream ) 
		: mStream(stream)
	{

	}

	Value* BinParser::parseValue()
	{
		Value::Type type = Value::Types::Null;
		mStream.read(reinterpret_cast<char*>(&type), sizeof(char));

		switch(type)
		{
		case Value::Types::Array:
			return parseArray();
		case Value::Types::Object:
			return parseObject();
		case Value::Types::Number:
			return parseNumber();
		case Value::Types::String:
			return new Value(parseString());
		case Value::Types::Bool:
			return parseBool();
		case Value::Types::Null:
		default:
			return new Value();
		}
	}

	Value* BinParser::parseObject()
	{
		int size = parseInt();
		String key;
		Value *value = NULL;
		Object* object = new Object;

		for(int i = 0; i < size; ++i)
		{
			key = parseString();
			value = parseValue();
			object->values[key] = value;
		}

		return object;
	}

	Value* BinParser::parseArray()
	{
		int size = parseInt();
		String key;
		Array* arr = new Array;

		for(int i = 0; i < size; ++i)
		{
			arr->values.push_back(parseValue());
		}

		return arr;
	}

	Value* BinParser::parseNumber()
	{
		float f;
		mStream.read(reinterpret_cast<char*>(&f), sizeof(float));
		return new Value(f);
	}

	String BinParser::parseString()
	{
		int size = parseInt();
		char* c = new char[size + 1];
		mStream.read(c, size * sizeof(char));
		c[size] = 0;
		String str(c);
		delete c;
		return str;
	}

	Value* BinParser::parseBool()
	{
		bool b = false;
		mStream.read(reinterpret_cast<char*>(&b), sizeof(char));
		return new Value(b);
	}

	int BinParser::parseInt()
	{
		int i;
		mStream.read(reinterpret_cast<char*>(&i), sizeof(int));
		return i;
	}
};//namespace Exil
#endif