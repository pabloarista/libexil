#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <functional>

typedef std::string String;

namespace Exil
{

	struct Object;
	struct Array;
	struct Value;
	typedef std::pair<String, Value*> Pair;
	typedef std::map<String, Value*> ValueMap;
	typedef std::list<Value*> ValueList;

	struct Value
	{
		Value(float num)
		{
			type = Types::Number;
			number = num;
		}
		
		Value(int num)
		{
			type = Types::Number;
			number = num;
		}
		
		Value(String _string)
		{
			type = Types::String;
			string = new char[_string.size() + 1];
			strncpy(string, _string.c_str(), _string.size());
			string[_string.size()] = 0;
		}
		
		Value(bool val)
		{
			if(val)
				type = Types::True;
			else
				type = Types::False;
		}
		
		Value()
		{
			type = Types::Null;
		}	
		
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
		
		bool isNull()
		{
			return type == Types::Null;
		}
		
		bool isTrue()
		{
			return type == Types::True;
		}
		
		bool isFalse()
		{
			return type == Types::False;
		}
		
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
		
		char* toString()
		{
			return string;
		}
		
		// data
		Type type;
		union
		{
			float number;
			char* string;
		};
	};
	
	template <typename T>
	struct TypeConversion
	{
		static Value* convertTo(typename T);
		
		static T convertFrom(Value*);
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
	
	struct Object : public Value
	{
		Object()
		{
			type = Types::Object;
		}
		
		void addValue(const String& name, Value* value)
		{
			values.insert(Pair(name, value));
		}
		
		template <typename T>
		void addValue(const String& name, T value)
		{
			addValue(name, TypeConversion<T>::convertTo(value));
		}
		
		ValueMap values;
	};

	struct Array : public Value
	{
		Array()
		{
			type = Types::Array;
		}
		
		void addValue(Value* value)
		{
			values.push_back(value);
		}
		
		template <typename T>
		void addValue(T value)
		{
			addValue(TypeConversion<T>::convertTo(value));
		}
		
		ValueList values;
	};

	Object* Value::toObject()
	{
		if(type == Types::Object)
			return static_cast<Object*>(this);
		
		return NULL;
	}

	Array* Value::toArray()
	{
		if(type == Types::Array)
			return static_cast<Array*>(this);
			
		return NULL;
	}
	
	std::ostream& operator<< (std::ostream& os, Object* val);
	std::ostream& operator<< (std::ostream& os, Array* val);
	std::ostream& operator<< (std::ostream& os, Value* val)
	{
		os << "Value: ";
		switch(val->type)
		{
			case Value::Types::Number:
				os << "Number = " << val->toNumber<float>() << std::endl;
				break;
			case Value::Types::String:
				os << "String = " << val->toString() << std::endl;
				break;
			case Value::Types::True:
				os << "True" << std::endl;
				break;
			case Value::Types::False:
				os << "False" << std::endl;
				break;
			case Value::Types::Null:
				os << "Null" << std::endl;
				break;
			case Value::Types::Object:
				os << val->toObject() << std::endl;
				break;
			case Value::Types::Array:
				os << val->toArray() << std::endl;
				break;
		}
		return os;
	}

	std::ostream& operator<< (std::ostream& os, Object* val)
	{
		os << "{" << std::endl;
		
		for(ValueMap::iterator iter = val->values.begin();
			iter != val->values.end();
			++iter)
		{
			os << iter->first << " = " << iter->second << std::endl;
		}
		
		os << "}" << std::endl;
		return os;
	}

	std::ostream& operator<< (std::ostream& os, Array* val)
	{
		os << "[" << std::endl;
		
		for(ValueList::iterator iter = val->values.begin();
			iter != val->values.end();
			++iter)
		{
			os << *iter << std::endl;
		}
		
		os << "]" << std::endl;
		return os;
	}	

	
	struct DataStream
	{
		DataStream(std::ostream& stream)
			: mStream(stream)
		{
		}
		
		virtual DataStream& operator<<(Value* value) = 0;
		
		std::ostream& mStream;
	};
	
	struct XmlStream : public DataStream
	{
		XmlStream(std::ostream& stream)
			: DataStream(stream)
		{
		}
		
		virtual XmlStream& operator<<(Value* value)
		{
			
		
			return *this;
		}
	};
	
	

};//namespace Exil

	struct Vector3
	{
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		
		float x,y,z;
	};
	
	struct Player
	{
		String name;
		int id;
		Vector3 position;
	};
	
namespace Exil
{

	template<>
	struct TypeConversion<Vector3>
	{
		static Value* convertTo(Vector3 vec)
		{
			Object* object = new Object;
			object->addValue("x", vec.x);
			object->addValue("y", vec.y);
			object->addValue("z", vec.z);
			
			return object;
		}
		
		static Vector3 convertFrom(Value* val)
		{
			Object* object = NULL;
			if( !(object = val->toObject()) )
				return Vector3();
				
			Vector3 vec;
			
			for(ValueMap::iterator iter = object->values.begin();
				iter != object->values.end();
				++iter)
			{
				if(iter->first.compare("x") == 0)
					vec.x = iter->second->toNumber<float>();
				else if(iter->first.compare("y") == 0)
					vec.y = iter->second->toNumber<float>();
				else if(iter->first.compare("z") == 0)
					vec.z = iter->second->toNumber<float>();
			}
			
			return vec;
		}
	};
	
	template<>
	struct TypeConversion<Player>
	{
		static Value* convertTo(Player player)
		{
			Object* object = new Object;
			object->values.insert(Pair("name", new Value(player.name)));
			object->values.insert(Pair("id", new Value(player.id)));
			object->values.insert(Pair("position", TypeConversion<Vector3>::convertTo(player.position)));
			
			return object;
		}
		
		static Player convertFrom(Value* value)
		{
			return Player();
		}
	};

};//namespace Exil

/*
int main()
{
	Vector3 vec1(1.1, 2.2, 3.3);

	Exil::Value* value = Exil::TypeConversion<Vector3>::convertTo(vec1);
	
	std::cout << value;	

	Vector3 vec2 = Exil::TypeConversion<Vector3>::convertFrom(value);
	
	std::cout << vec2.x << ", " << vec2.y << ", " << vec2.z << std::endl;
	
	Player player;
	player.position = vec1;
	player.name = "Woot";
	player.id = 12345;
	
	Exil::Value* value2 = Exil::TypeConversion<Player>::convertTo(player);
	
	std::cout << value2;
	
	return 0;
}
*/