#ifndef ExilArray_h__
#define ExilArray_h__

#include <Exil.h>
#include <ExilObject.h>

namespace Exil
{
	struct Array : public Value
	{
		Array();
	
		void addValue(Value* value);
	
		template <typename T>
		void addValue(T value)
		{
			addValue(TypeConversion<T>::convertTo(value));
		}
	
		ValueList values;
	};

	std::ostream& operator<< (std::ostream& os, Array* val);

};
#endif // ExilArray_h__
