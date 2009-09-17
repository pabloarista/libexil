#ifndef ExilValue_h__
#define ExilValue_h__

#include <Exil.h>

namespace Exil
{
	struct Value
	{
		Value(float num);
	
		Value(int num);
	
		Value(String _string);
	
		Value(bool val);
	
		Value();	
	
		struct Types
		{
			enum Type
			{
				Number,
				String,
				Object,
				Array,
				True,
				False,
				Null			
			};
		};
		typedef Types::Type Type;
	
		Object* toObject();
	
		Array* toArray();
	
		bool isNull();
	
		bool isTrue();
	
		bool isFalse();
	
		template <typename NumberType>
		NumberType toNumber();
	
		template <>
		float toNumber<float>()
		{
			return number;
		}
	
		template <>
		int toNumber<int>()
		{
			return static_cast<int>(number);
		}
	
		char* toString();
	
		// data
		Type type;
		union
		{
			float number;
			char* string;
		};
	};

	template <>
	struct TypeConversion<float>
	{
		static Value* convertTo(float num)
		{
			return new Value(num);
		}

		static float convertFrom(Value* value)
		{
			return value->toNumber<float>();
		}
	};

	template <>
	struct TypeConversion<int>
	{
		static Value* convertTo(int num)
		{
			return new Value(num);
		}

		static int convertFrom(Value* value)
		{
			return value->toNumber<int>();
		}
	};

	template <>
	struct TypeConversion<String>
	{
		static Value* convertTo(String num)
		{
			return new Value(num);
		}

		static String convertFrom(Value* value)
		{
			return value->toString();
		}
	};

	template <>
	struct TypeConversion<bool>
	{
		static Value* convertTo(bool b)
		{
			return new Value(b);
		}

		static bool convertFrom(Value* value)
		{
			return value->isTrue();
		}
	};

	std::ostream& operator<< (std::ostream& os, Value* val);

}
#endif // ExilValue_h__
