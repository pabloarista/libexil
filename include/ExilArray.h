#ifndef ExilArray_h__
#define ExilArray_h__

#include <Exil.h>
#include <ExilValue.h>

namespace Exil
{
	class Array : public Value
	{
	public:
		Array();
		~Array();

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
