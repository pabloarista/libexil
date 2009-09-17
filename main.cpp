#include <iostream>
#include <ExilArray.h>
#include <ExilObject.h>
#include <ExilValue.h>
#include <ExilXmlStream.h>
#include <ExilJsonStream.h>

typedef std::string String;

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



int main()
{
	Vector3 vec1(1.1f, 2.2f, 3.3f);

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
