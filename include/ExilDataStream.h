#ifndef ExilDataStream_h__
#define ExilDataStream_h__

#include <Exil.h>
#include <iostream>

#include <ExilJsonFormatter.h>
#include <ExilBinFormatter.h>
#include <ExilXmlFormatter.h>

#include <ExilJsonParser.h>
#include <ExilBinParser.h>
#include <ExilXmlParser.h>

#ifdef UPGRADE_COMPLETE

namespace Exil
{
	struct NullIStream: 
		std::istream { 
			NullIStream(): std::ios(0), std::istream(0) {} 
	}; 
	extern NullIStream NullIn;

	struct NullOStream: 
		std::ostream { 
			NullOStream(): std::ios(0), std::ostream(0) {} 
	}; 
	extern NullOStream NullOut;

	typedef JsonFormatter DefaultFormatterPolicy;
	typedef JsonParser DefaultParserPolicy;

	class EmptyParserPolicy
	{
	public:
		EmptyParserPolicy(std::istream&) {}
		Value* getValue() { return NULL; }
	};

	class EmptyFormatterPolicy
	{
	public:
		EmptyFormatterPolicy(std::ostream&) {}
		EmptyFormatterPolicy& operator<<(Value* value) { return *this; }

	};

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

		DataStream& operator<<(Value* value)
		{
			mFormatter << value;
			return *this;
		}

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

	typedef DataStream<XmlParser, XmlFormatter> XmlStream;
	typedef DataStream<JsonParser, JsonFormatter> JsonStream;
	typedef DataStream<BinParser, BinFormatter> BinStream;

	typedef Exil::DataStream<Exil::EmptyParserPolicy, Exil::JsonFormatter> DSOutType;
	extern DSOutType dsout;

};//namespace Exil

#endif

#endif // ExilDataStream_h__