#ifndef ExilObject_h__
#define ExilObject_h__

#include <Exil.h>
#include <ExilValue.h>

namespace Exil
{
	class Object : public Value
	{
	public:
		Object();

		~Object();
	
		void addValue(const String& name, Value* value);
	
		template <typename T>
		void addValue(const String& name, T value)
		{
			addValue(name, TypeConversion<T>::convertTo(value));
		}

		bool hasValue(const String& name);

		Value* getValue(const String& name);

		template <typename T>
		T getValue(const String& name)
		{
			Value* value = getValue(name);
			if(!value)
				throw ConversionException();

			return TypeConversion<T>::convertFrom(value);
		}
	
		ValueMap values;
	};

	std::ostream& operator<< (std::ostream& os, Object* val);
};


#endif // ExilObject_h__