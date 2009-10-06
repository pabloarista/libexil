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

	//std::ostream& operator<< (std::ostream& os, Array* val);

#pragma region Conversion Methods
	template<typename T>
	struct TypeConversion<std::list<T> >
	{
		typedef std::list<T> Type;
		static Value* convertTo(Type list)
		{
			Array* arr = new Array;
			for(Type::iterator iter = list.begin();
				iter != list.end();
				++iter)
			{
				arr->addValue(*iter);
			}

			return arr;
		}

		static Type convertFrom(Value* val)
		{
			Array* arr = NULL;
			if( !(arr = val->toArray()) )
				throw ConversionException();

			Type list;
			for(ValueList::iterator iter = arr->values.begin();
				iter != arr->values.end();
				++iter)
			{
				list.push_back(TypeConversion<T>::convertFrom(*iter));
			}

			return list;
		}
	};

	template<typename T>
	struct TypeConversion<std::vector<T> >
	{
		typedef std::vector<T> Type;
		static Value* convertTo(Type list)
		{
			Array* arr = new Array;
			for(Type::iterator iter = list.begin();
				iter != list.end();
				++iter)
			{
				arr->addValue(*iter);
			}

			return arr;
		}

		static Type convertFrom(Value* val)
		{
			Array* arr = value->toArray();

			Type list;
			for(ValueList::iterator iter = arr->values.begin();
				iter != arr->values.end();
				++iter)
			{
				list.push_back(TypeConversion<T>::convertFrom(*iter));
			}

			return list;
		}
	};
#pragma endregion Conversion Methods

};
#endif // ExilArray_h__
