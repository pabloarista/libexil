#ifndef ExilJsonFormatter_h__
#define ExilJsonFormatter_h__

#include <Exil.h>

namespace Exil
{
	class JsonFormatter : public Formatter
	{
	public:
		JsonFormatter(std::ostream& stream, bool pretty = true);

		template <typename T>
		JsonFormatter& operator<<(T* value);

		void write(Buffer& buffer);

		template <typename T>
		void _write(T* value, bool comma = false, bool leadTab = true);

		template <typename T>
		void _writePair(const char* name, T* value, bool comma = true);

		void _increaseTab();

		void _decreaseTab();
	
		bool mPretty;
		int mTabCount;
		String mTabs;
		Buffer& mBuffer;
	};

};//namespace Exil

#endif // ExilJsonFormatter_h__