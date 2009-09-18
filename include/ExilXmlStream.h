#ifndef ExilXmlStream_h__
#define ExilXmlStream_h__

#include <Exil.h>

namespace Exil
{
	class XmlStream
	{
	public:
		XmlStream(std::iostream& stream);

		template <typename T>
		XmlStream& operator<<(T type)
		{
			return *this << TypeConversion<T>::convertTo(type);
		}

		XmlStream& operator<<(Value* value);

		void _writeObject(Object* object, bool writeName = true, bool leadTab = true);

		void _writeArray(Array* list, bool writeName = true, bool leadTab = true);

		void _writePair(const String& name, Value* value);

		void _writeValue(Value* value, bool writeName = true, bool leadTab = true);

		void _increaseTab();

		void _decreaseTab();

		std::iostream& mStream;
		String mTabs;
	};

};//namespace Exil

#endif // ExilXmlStream_h__
