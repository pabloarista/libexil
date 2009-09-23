#ifndef ExilXmlParser_h__
#define ExilXmlParser_h__

#include <Exil.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>
#include <cctype>

namespace Exil
{
	class XmlParser
	{
	public:
		XmlParser(std::istream& stream)
			: mStream(stream)
		{
		}

		String parseTagName()
		{
			char ch;
			String str;
			mStream.get(ch);
			while(!mStream.eof() && isalnum(ch))
			{
				str.push_back(ch);
				mStream.get(ch);
			}

			return str;
		}

		String parseKeyName()
		{
			char lastCh = 0;
			char ch;
			String str;

			mStream.get(ch);
			while( !mStream.eof() && isalnum(ch) )
			{
				lastCh = ch;
				str.push_back(ch);
				mStream.get(ch);
			}

			return str;
		}

		Value* parseNumber()
		{
			float number = 0.0f;
			char ch;

			mStream.get(ch);
			while(!mStream.eof() && isdigit(ch))
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
				while(!mStream.eof() && isdigit(ch))
				{
					number = number + toNumber(ch) / denom;
					denom *= 10.f;
					mStream.get(ch);
				}
			}

			return new Value(number);
		}

		Value* parseString()
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

			return new Value(str);
		}

		Value* parseBool()
		{
			char ch;
			mStream.get(ch);
			if(ch == 't')
			{
				mStream.ignore(3);
				return new Value(true);
			}
			if(ch == 'f')
			{
				mStream.ignore(4);
				return new Value(false);
			}

			return new Value();			
		}

		Object* parseObject()
		{
			Object* obj = new Object;

			while(!mStream.eof())
			{
				Pair pair = parseObjectPair();
				obj->addValue(pair);
			}
			return obj;
		}

		Value* getRoot()
		{
			Pair pair = parseObjectPair();
			return pair.second;
		}

		Array* parseArray()
		{
			char ch;
			mStream.get(ch);

			Array* arr = new Array;

			while(!mStream.eof())
			{
				Pair pair = parseObjectPair();
				arr->addValue(pair.second);
			}
			return arr;
		}

		Pair parseObjectPair()
		{
			char ch;
			mStream.get(ch);

			while(!mStream.eof())
			{
				if(isspace(ch))
				{
					mStream.get(ch);
					continue;
				}

				// check for open brace
				if(ch == '<')
				{
					String typeStr = parseTagName();

					// happens when tag begins with a '/'
					if(typeStr.empty())
					{
						// consume until we get a close brace
						while(!mStream.eof() && ch != '>')
							mStream.get(ch);
						continue;
					}

					Value::Type type = Convert::toValueType(typeStr);

					String key = parseKeyName();
					//if(key.empty())
					//	throw ConversionException();
					Value* value = NULL;

					if(!key.empty())
					{
						// consume until we get to the named value
						while(!mStream.eof() && ch != '\"')
							mStream.get(ch);

						switch(type)
						{
						case Value::Types::Bool:
							value = parseBool();
							break;
						case Value::Types::Number:
							value = parseNumber();
							break;
						case Value::Types::String:
						case Value::Types::Object:
						case Value::Types::Array:
							value = parseString();
							break;
						default:
							value = new Value();
						}

						// consume until we get a close brace
						while(!mStream.eof() && ch != '>')
							mStream.get(ch);

					}

					if(type == Value::Types::Object)
					{
						Object* object = parseObject();

						Pair pair(value?value->toString():BLANK_STRING, object);
						delete value;
						return pair;
					}
					else if(type == Value::Types::Array)
					{
						Array* arr = parseArray();

						Pair pair(value?value->toString():BLANK_STRING, arr);
						delete value;
						return pair;
					}
					else
					{
						return Pair(key, value);
					}
				}//end check for open brace
				else
				{
					mStream.get(ch);
				}
			}//end while
		}

		inline float toNumber(char ch)
		{
			return static_cast<float>(ch - 48);
		}

		std::istream& mStream;
	};

};//namespace Exil

#endif // ExilXmlParser_h__