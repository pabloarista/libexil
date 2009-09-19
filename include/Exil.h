#ifndef Exil_h__
#define Exil_h__

#pragma warning(disable:4996)

#include <string>
#include <map>
#include <list>
#include <vector>
#include <map>
#include <exception>

namespace Exil
{
	typedef std::string String;
	const String BLANK_STRING;

	class Value;
	class Object;
	class Array;
	class JsonStream;
	class JsonParser;
	class XmlStream;
	class XmlParser;
	typedef std::pair<String, Value*> Pair;
	typedef std::map<String, Value*> ValueMap;
	typedef std::list<Value*> ValueList;

	class Exception : public std::runtime_error
	{
	public:
		Exception(const String& message);
	};

	class ConversionException : public Exception
	{
	public:
		ConversionException();
	};

	template <typename T>
	struct TypeConversion
	{
		static Value* convertTo(typename T);

		static T convertFrom(Value*);
	};

};//namespace Exil

#endif // Exil_h__