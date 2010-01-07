#ifndef ExilValue_h__
#define ExilValue_h__

#include <Exil.h>
#ifdef UPGRADE_COMPLETE
namespace Exil
{
	class Value
	{
	public:
		struct Types
		{
			enum Type
			{
				Number,
				String,
				Object,
				Array,
				Bool,
				Null
			};
		};
		typedef Types::Type Type;

	public:
		Value(float num);
	
		Value(int num);
	
		Value(String _string);

		Value(const char* str);

		Value(const char* str, size_t size);
	
		Value(bool val);
	
		Value();

		virtual ~Value();
	
		Object* toObject();
	
		Array* toArray();

		bool toBool();
	
		bool isNull();
	
		template <typename NumberType>
		NumberType toNumber();
	
		template <>
		float toNumber<float>()
		{
			return mNumber;
		}
	
		template <>
		int toNumber<int>()
		{
			return static_cast<int>(mNumber);
		}
	
		char* toString();

		inline Type type()
		{
			return mType;
		}

	private:
		void _setString(const char* str, size_t size);

	protected:
		// data
		Type mType;

	private:
		union
		{
			float mNumber;
			char* mString;
			bool mBool;
		};
	};

#pragma region Conversion Methods
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
			return value->toBool();
		}
	};

	std::ostream& operator<< (std::ostream& os, Value* val);

	namespace Convert
	{
		String toString(Value::Type type);
		Value::Type toValueType(const String& str);
	}

#pragma endregion Conversion Methods
};//namespace Exil

#endif

#endif // ExilValue_h__
