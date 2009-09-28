#ifndef ExilBinStream_h__
#define ExilBinStream_h__

#include <Exil.h>
#include <ExilValue.h>
#include <ExilBinParser.h>

namespace Exil
{
	class BinStream
	{
	public:
		BinStream(std::iostream& stream);

		template <typename T>
		BinStream& operator<<(T type)
		{
			return *this << TypeConversion<T>::convertTo(type);
		}

		BinStream& operator<<(Value* value);

		template <typename T>
		BinStream& operator>>(T& type)
		{
			Value* value = mParser.parseValue();
			type = TypeConversion<T>::convertFrom(value);
			delete value;
			return *this;
		}

		void _writeObject(Object* object);

		void _writeArray(Array* list);

		void _writePair(const String& name, Value* value);

		void _writeValue(Value* value);

		void _writeString(const String& str);
		void _writeBool(bool b);

		void _writeInt(int number);
		void _writeFloat(float number);
		void _writeType(Value::Type type);

		std::iostream& mStream;
		BinParser mParser;
	};

};//namespace Exil

#endif // ExilBinStream_h__