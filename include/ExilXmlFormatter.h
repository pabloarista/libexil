#ifndef ExilXmlFormatter_h__
#define ExilXmlFormatter_h__

#include <Exil.h>
#ifdef UPGRADE_COMPLETE

namespace Exil
{
	class XmlFormatter : public Formatter
	{
	public:
		XmlFormatter(std::ostream& stream);

		XmlFormatter& operator<<(Value* value);

		void _writeObject(Object* object, bool writeName = true, bool leadTab = true);

		void _writeArray(Array* list, bool writeName = true, bool leadTab = true);

		void _writePair(const String& name, Value* value);

		void _writeValue(Value* value, bool writeName = true, bool leadTab = true);

		void _increaseTab();

		void _decreaseTab();

		String mTabs;
	};

};//namespace Exil
#endif
#endif // ExilXmlFormatter_h__
