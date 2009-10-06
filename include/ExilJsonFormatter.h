#ifndef ExilJsonFormatter_h__
#define ExilJsonFormatter_h__

#include <Exil.h>

namespace Exil
{
	class JsonFormatter : public Formatter
	{
	public:
		JsonFormatter(std::ostream& stream, bool pretty = true);

		JsonFormatter& operator<<(Value* value);

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

#endif // ExilJsonFormatter_h__