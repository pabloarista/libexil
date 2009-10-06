#ifndef ExilJsonStream_h__
#define ExilJsonStream_h__

#include <Exil.h>
#include <ExilJsonParser.h>

namespace Exil
{
	class JsonStream
	{
	public:
		JsonStream(std::ostream& stream, bool pretty = true);

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
		std::ostream& mStream;
	};

};//namespace Exil

#endif // ExilJsonStream_h__