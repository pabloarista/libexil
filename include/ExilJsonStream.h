#ifndef ExilJsonStream_h__
#define ExilJsonStream_h__

#include <Exil.h>
#include <ExilJsonParser.h>

namespace Exil
{
	class JsonStream
	{
	public:
		JsonStream(std::iostream& stream, bool pretty = true);

		template <typename T>
		JsonStream& operator<<(T type)
		{
			return *this << TypeConversion<T>::convertTo(type);
		}

		JsonStream& operator<<(Value* value);

		template <typename T>
		JsonStream& operator>>(T& type)
		{
			Value* value = mParser.parseValue();
			type = TypeConversion<T>::convertFrom(value);
			delete value;
			return *this;
		}

		Value* get()
		{
			return mParser.parseValue();
		}

		void _writeObject(Object* object, bool leadTab = true);

		void _writeArray(Array* list, bool leadTab = true);

		void _writePair(const String& name, Value* value, bool comma = true);

		void _writeValue(Value* value, bool comma = false, bool leadTab = true);

		void _increaseTab();

		void _decreaseTab();
	
		JsonParser mParser;
		bool mPretty;
		int mTabCount;
		String mTabs;
		std::iostream& mStream;
	};

};//namespace Exil

#endif // ExilJsonStream_h__