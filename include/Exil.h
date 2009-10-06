#ifndef Exil_h__
#define Exil_h__

#pragma warning(disable:4996)
#pragma warning (disable:4661)

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
	typedef char int8_t;
	typedef short int16_t;
	typedef long int32_t;
	typedef long long int64_t;
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned long uint32_t;
	typedef unsigned long long uint64_t;
	typedef float real_t;

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
		static Value* convertTo(T);

		static T convertFrom(Value*);
	};

};//namespace Exil

#endif // Exil_h__