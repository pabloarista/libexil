#include <iostream>
#include <sstream>
#include <ExilArray.h>
#include <ExilObject.h>
#include <ExilValue.h>
#include <ExilDataStream.h>
#include <ExilXmlStream.h>
#include <ExilJsonStream.h>

#include <ExilJsonParser.h>

typedef std::string String;

struct Vector3
{
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x,y,z;
};

struct Item
{
	Item(const String& n = Exil::BLANK_STRING, int q = 0)
		: name(n), quantity(q)
	{}
	String name;
	int quantity;
};

typedef std::list<Item> ItemList;

struct Player
{
	String name;
	int id;
	Vector3 position;
	ItemList items;
	bool alive;
	bool dead;
};

namespace Exil
{

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
		}
	};

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
	struct TypeConversion<Item>
	{
		static Value* convertTo(Item item)
		{
			Object* object = new Object;
			object->addValue("name", item.name);
			object->addValue("quantity", item.quantity);
			return object;
		}

		static Item convertFrom(Value* value)
		{
			Item item;
			return item;
		}
	};

	template<>
	struct TypeConversion<Player>
	{
		static Value* convertTo(Player player)
		{
			Object* object = new Object;
			object->addValue("name", player.name);
			object->addValue("id", player.id);
			object->addValue("position", player.position);
			object->addValue("items", player.items);
			object->addValue("alive", player.alive);
			object->addValue("dead", player.dead);

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
	Player player;
	player.position = Vector3(1.1f, 2.2f, 3.3f);
	player.name = "Woot";
	player.id = 12345;
	player.alive = true;
	player.dead = false;
	player.items.push_back(Item("This", 1));
	player.items.push_back(Item("Thing", 2));
	player.items.push_back(Item("Wont", 3));
	player.items.push_back(Item("Stop", 4));


	std::stringstream ss;

	Exil::JsonStream json(ss, true);

	json << player;

/*	Exil::XmlStream xml(std::cout);

	xml << player;
*/

	std::cout << ss.str();

	Exil::JsonParser jparser(ss);

	Exil::Value* object = jparser.parseObject();

	std::cout << object;

	Exil::JsonStream jout(std::cout);

	jout << object;

	std::cin.get();

	return 0;
}
