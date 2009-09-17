#ifndef ExilJsonStream_h__
#define ExilJsonStream_h__

#include <Exil.h>
#include <ExilDataStream.h>

#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	struct JsonStream : public DataStream
	{
		JsonStream(std::ostream& stream, bool pretty = true);

		template <typename T>
		JsonStream& operator<<(T type)
		{
			return *this << TypeConversion<T>::convertTo(type);
		}

		JsonStream& operator<<(Value* value);

		void _writeObject(Object* object, bool leadTab = true);

		void _writeArray(Array* list, bool leadTab = true);

		void _writePair(const String& name, Value* value, bool comma = true);

		void _writeValue(Value* value, bool comma = false, bool leadTab = true);

		void _increaseTab();

		void _decreaseTab();
	
		bool mPretty;
		int mTabCount;
		String mTabs;
	};

};//namespace Exil

#endif // ExilJsonStream_h__