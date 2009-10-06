#ifndef ExilDataStream_h__
#define ExilDataStream_h__

#include <Exil.h>
#include <istream>
#include <ostream>
#include <iostream>

namespace Exil
{
	class DefaultParserPolicy {};
	class DefaultFormatterPolicy {};

	template <
		class ParserPolicy = DefaultParserPolicy,
		class FormatterPolicy = DefaultFormatterPolicy
	>
	class DataStream
	{
	public:
		typedef ParserPolicy ParserPolicyType;
		typedef FormatterPolicy FormatterPolicyType;

		DataStream(std::ostream& os, std::istream& is)
			: mFormatter(os), mParser(is)
		{}

		DataStream(std::iostream& stream)
			: mParser(stream), mFormatter(stream)
		{}

		template <typename T>
		DataStream& operator<<(T type)
		{
			mFormatter << TypeConversion<T>::convertTo(type);
			return *this;
		}

		template <typename T>
		DataStream& operator>>(T& type)
		{
			Value* value = mParser.parseValue();
			type = TypeConversion<T>::convertFrom(value);
			delete value;
			return *this;
		}

		ParserPolicy mParser;
		FormatterPolicy mFormatter;

	};

};//namespace Exil

#endif // ExilDataStream_h__