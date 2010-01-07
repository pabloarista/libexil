#ifndef ExilBinFormatter_h__
#define ExilBinFormatter_h__

#include <Exil.h>
#include <ExilValue.h>
#ifdef UPGRADE_COMPLETE

namespace Exil
{
	class BinFormatter : public Formatter
	{
	public:
		BinFormatter(std::ostream& stream);

		BinFormatter& operator<<(Value* value);

		void _writeObject(Object* object);

		void _writeArray(Array* list);

		void _writePair(const String& name, Value* value);

		void _writeValue(Value* value);

		void _writeString(const String& str);
		void _writeBool(bool b);

		void _writeInt(int number);
		void _writeFloat(float number);
		void _writeType(Value::Type type);
	};

};//namespace Exil
#endif
#endif // ExilBinFormatter_h__