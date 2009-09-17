#ifndef ExilObject_h__
#define ExilObject_h__

#include <Exil.h>
#include <ExilValue.h>

namespace Exil
{
	struct Object : public Value
	{
		Object();
	
		void addValue(const String& name, Value* value);
	
		template <typename T>
		void addValue(const String& name, T value)
		{
			addValue(name, TypeConversion<T>::convertTo(value));
		}
	
		ValueMap values;
	};

	std::ostream& operator<< (std::ostream& os, Object* val);
};


#endif // ExilObject_h__