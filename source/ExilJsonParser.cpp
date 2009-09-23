#include <ExilJsonParser.h>
#include <ExilValue.h>
#include <ExilArray.h>
#include <ExilObject.h>

namespace Exil
{
	JsonParser::JsonParser( std::istream& stream ) 
		: mStream(stream)
	{

	}

	Exil::String JsonParser::parseString()
	{
		char lastCh = 0;
		char ch;
		String str;

		mStream.get(ch);
		while(!(mStream.eof() || (ch == '"' && lastCh != '\\')))
		{
			lastCh = ch;
			str.push_back(ch);
			mStream.get(ch);
		}

		return str;
	}

	float JsonParser::parseNumber( char ch )
	{
		float number = 0.0f;

		while(!mStream.eof() && isNumber(ch))
		{
			if(ch == '.')
				break;
			number = number * 10.0f + toNumber(ch);
			mStream.get(ch);
		}

		if(ch == '.')
		{
			float denom = 10.0f;
			mStream.get(ch);
			while(!mStream.eof() && isNumber(ch))
			{
				number = number + toNumber(ch) / denom;
				denom *= 10.f;
				mStream.get(ch);
			}
		}

		return number;
	}

	Exil::Pair JsonParser::parsePair( char ch )
	{
		Pair pair;

		// eat whitespace
		//mStream.get(ch);
		while(!mStream.eof() && isWhiteSpace(ch))
			mStream.get(ch);

		pair.first = parseString();

		// eat whitespace and the ':'
		mStream.get(ch);
		while(!mStream.eof() && (ch == ':' || isWhiteSpace(ch)))
			mStream.get(ch);

		pair.second = parseValue(ch);

		return pair;
	}

	Object* JsonParser::parseObject()
	{
		Object* object = new Object;
		char ch;

		mStream.get(ch);
		if(ch == '{')
			mStream.get(ch);

		while(!mStream.eof() && ch != '}')
		{
			if(isWhiteSpace(ch) || ch == ',')
			{
				mStream.get(ch);
				continue;
			}

			object->addValue(parsePair(ch));
			mStream.get(ch);
		}

		return object;
	}

	Array* JsonParser::parseArray()
	{
		Array* arr = new Array;
		char ch;

		mStream.get(ch);

		while(!mStream.eof() && ch != ']')
		{
			if(isWhiteSpace(ch) || ch == ',')
			{
				mStream.get(ch);
				continue;
			}

			arr->values.push_back(parseValue(ch));
			mStream.get(ch);
		}

		return arr;
	}

	Value* JsonParser::parseValue( char ch /*= 0*/ )
	{
		if(ch == 0)
			mStream.get(ch);

		while(!mStream.eof())
		{
			if(isWhiteSpace(ch))
			{
				mStream.get(ch);
				continue;
			}

			// starts a number
			if(isNumber(ch))
			{
				return new Value(parseNumber(ch));
			}

			// starts a string
			if(ch == '"')
			{
				return new Value(parseString());
			}

			// starts an object
			if(ch == '{')
			{
				return parseObject();
			}

			// starts an array
			if(ch == '[')
			{
				return parseArray();
			}

			// starts 'true'
			if(ch == 't')
			{
				mStream.ignore(3);
				return new Value(true);
			}

			// starts 'false'
			if(ch == 'f')
			{
				mStream.ignore(4);
				return new Value(false);
			}

			// starts 'null'
			if(ch == 'n')
			{
				mStream.ignore(3);
				return new Value();
			}
			mStream.get(ch);
		}

		return new Value();
	}
};//namespace Exil
