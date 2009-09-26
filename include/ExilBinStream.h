#ifndef ExilBinStream_h__
#define ExilBinStream_h__

#include <Exil.h>

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

		void _writeObject(Object* object);

		void _writeArray(Array* list);

		void _writePair(const String& name, Value* value);

		void _writeValue(Value* value);

		void _writeString(const String& str);

		std::iostream& mStream;
	};

};//namespace Exil

#endif // ExilBinStream_h__