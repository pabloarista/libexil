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
	typedef std::string String;
	const String BLANK_STRING;
	typedef char I8;
	typedef short I16;
	typedef long I32;
	typedef long long I64;
	typedef unsigned char U8;
	typedef unsigned short U16;
	typedef unsigned long U32;
	typedef unsigned long long U64;
	typedef float F32;
	typedef double F64;

	namespace Data
	{
		class Array;
		class Object;
		class Integer;
		class Float;
		class Boolean;
		class String;
	}

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
	typedef U8 InternalType;
	typedef U16 SizeT;

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

};//namespace Exil

#endif // Exil_h__