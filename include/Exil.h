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
#include <iostream>

namespace Exil
{
	//typedef std::string String;
	const std::string BLANK_STRING;
	typedef char int8_t;
	typedef short int16_t;
	typedef long int32_t;
	typedef long long int64_t;
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned long uint32_t;
	typedef unsigned long long uint64_t;
	typedef float real_t;
	typedef uint16_t SizeT;

	namespace Types
	{
		enum Type
		{
			Nothing = 0,
			Object = 1,
			Array = 2,
			String = 3,
			Float = 4,
			Integer = 5,
			Boolean = 6,
			Null = 7
		};
	};
	typedef Types::Type Type;
	typedef unsigned char InternalType;

	// Base types
	class Object;
	class Array;
	class Integer;
	class String;
	class Float;
	class Boolean;

	// Basic reader/writer
	class Reader;
	class Writer;

	//class JsonFormatter;
	//class JsonParser;
	//class XmlFormatter;
	//class XmlParser;
	//typedef std::pair<String, Value*> Pair;
	//typedef std::map<String, Value*> ValueMap;
	//typedef std::list<Value*> ValueList;

	class Exception : public std::runtime_error
	{
	public:
		Exception(const std::string& message);
	};

	class ConversionException : public Exception
	{
	public:
		ConversionException();
	};

	template <typename T>
	struct ConvertType
	{
		static void To(T& t, Writer& writer)
		{
			writer.write(t);
		}

		static void From(T& t, Reader& reader)
		{
			reader.read(t);
		}
	};

	SizeT GetSize(const char* ptr);

	Type GetType(const char* ptr);

	/*
	class Formatter
	{
	public:
		Formatter(std::ostream& stream)
			: mStream(stream)
		{}

		virtual Formatter& operator<<(Value* value) = 0;

		std::ostream& mStream;
	};
	*/

};//namespace Exil

#endif // Exil_h__