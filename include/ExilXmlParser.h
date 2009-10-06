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
		typedef std::pair<String, String> StringPair;

	public:
		XmlParser(std::istream& stream)
			: mStream(stream)
		{
		}

		Value* parseValue()
		{
			char ch;
			StringPair nameValuePair;
			String tagName;
			Value::Type type;
			while(!mStream.eof())
			{
				mStream.get(ch);
				while(!mStream.eof() && isspace(ch))
					mStream.get(ch);

				getTagName(tagName, ch);

				// consume end tag
				if(tagName.empty() && ch == '/')
				{
					while(!mStream.eof() && ch != '>')
					{
						mStream.get(ch);
					}
					return NULL;
					continue;
				}

				type = Convert::toValueType(tagName);

				// if there is a space, there is either a named value or a '/'
				if(ch == ' ')
				{
					while(!mStream.eof())
					{
						mStream.get(ch);
						if(ch == '/')
						{
							// eat the '>'
							mStream.get(ch);
							break;
						}
						else if(isalnum(ch))
						{
							nameValuePair = parseTagPair(ch);
						}
					}
				}

				switch(type)
				{
				case Value::Types::String:
					return new Value(nameValuePair.second);
				case Value::Types::Number:
					return toNumber(nameValuePair.second);
				case Value::Types::Bool:
					return toBool(nameValuePair.second);
				case Value::Types::Object:
					return parseObject();
				case Value::Types::Array:
					return parseArray();
				default:
					return new Value();
				}
			}

			return new Value();
		}

		Pair parseValuePair()
		{
			char ch;
			StringPair nameValuePair;
			String tagName;
			Value::Type type;

			while(!mStream.eof())
			{
				mStream.get(ch);
				while(!mStream.eof() && isspace(ch))
					mStream.get(ch);

				getTagName(tagName, ch);

				// consume end tag
				if(tagName.empty() && ch == '/')
				{
					while(!mStream.eof() && ch != '>')
					{
						mStream.get(ch);
					}
					return Pair(BLANK_STRING, NULL);
					//continue;
				}

				try
				{
					type = Convert::toValueType(tagName);
				}
				catch(...)
				{
					return Pair(BLANK_STRING, new Value());
				}

				// if there is a space, there is either a named value or a '/'
				if(ch == ' ')
				{
					while(!mStream.eof() && ch != '>')
					{
						mStream.get(ch);
						if(ch == '/')
						{
							// eat the '>'
							mStream.get(ch);
							break;
						}
						else if(isalnum(ch))
						{
							nameValuePair = parseTagPair(ch);
						}
					}
				}

				switch(type)
				{
				case Value::Types::String:
					return Pair(nameValuePair.first, new Value(nameValuePair.second));
				case Value::Types::Number:
					return Pair(nameValuePair.first, toNumber(nameValuePair.second));
				case Value::Types::Bool:
					return Pair(nameValuePair.first, toBool(nameValuePair.second));
				case Value::Types::Object:
					return Pair(nameValuePair.second, parseObject());
				case Value::Types::Array:
					return Pair(nameValuePair.second, parseArray());
				default:
					return Pair(nameValuePair.first, new Value());
				}
			}

			return Pair(nameValuePair.first, new Value());
		}

		StringPair parseTagPair(char& ch)
		{
			String key;
			String value;

			while(!mStream.eof() && isalnum(ch))
			{
				key.push_back(ch);
				mStream.get(ch);
			}

			while(!mStream.eof() && !isalnum(ch))
				mStream.get(ch);

			while(!mStream.eof() && (isalnum(ch) || ch == '.'))
			{
				value.push_back(ch);
				mStream.get(ch);
			}

			return StringPair(key,value);
		}

		void getTagName(String& tagName, char& ch)
		{
			mStream.get(ch);
			while(!mStream.eof() && isalnum(ch))
			{
				tagName.push_back(ch);
				mStream.get(ch);
			}
		}

		Value* toNumber(const String& str)
		{
			float number = 0.0f;
			String::const_iterator iter = str.begin();
			while(iter != str.end() && isdigit(*iter))
			{
				if(*iter == '.')
					break;
				number = number * 10.0f + toNumber(*iter);
				++iter;
			}

			if(iter != str.end() && *iter == '.')
			{
				float denom = 10.0f;
				++iter;
				while(iter != str.end() && isdigit(*iter))
				{
					number = number + toNumber(*iter) / denom;
					denom *= 10.f;
					++iter;
				}
			}

			return new Value(number);
		}

		Value* toBool(const String& str)
		{
			if(str.at(0) == 't')
				return new Value(true);
			else
				return new Value(false);
		}

		Object* parseObject()
		{
			Object* obj = new Object;

			while(!mStream.eof())
			{
				Pair pair = parseValuePair();
				if(pair.first == "" && pair.second == NULL)
					return obj;
				obj->addValue(pair);
			}
			return obj;
		}

		Array* parseArray()
		{
			Array* arr = new Array;

			while(!mStream.eof())
			{
				Value* value = parseValue();
				if(value == NULL)
					return arr;
				arr->addValue(value);
			}
			return arr;
		}
/*
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
*/
		inline float toNumber(char ch)
		{
			return static_cast<float>(ch - 48);
		}

		std::istream& mStream;
	};

};//namespace Exil

#endif // ExilXmlParser_h__