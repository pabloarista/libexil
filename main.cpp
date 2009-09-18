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
				throw ConversionException();

			Vector3 vec;
			vec.x = object->getValue<float>("x");
			vec.y = object->getValue<float>("y");
			vec.z = object->getValue<float>("z");

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
			Object* object = NULL;
			if( !(object = value->toObject()) )
				throw ConversionException();

			Item item;
			item.name = object->getValue<String>("name");
			item.quantity = object->getValue<int>("quantity");
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
			Object* object = NULL;
			if( !(object = value->toObject()) )
				throw ConversionException();

			Player player;
			player.name = object->getValue<String>("name");
			player.id = object->getValue<int>("id");
			player.position = object->getValue<Vector3>("position");
			player.items = object->getValue<std::list<Item> >("items");
			player.alive = object->getValue<bool>("alive");
			player.dead = object->getValue<bool>("dead");
			return player;
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

	std::cout << ss.str() << std::endl;

	Player player2;
	json >> player2;

/*	Exil::XmlStream xml(std::cout);

	xml << player;
*/

	//std::cout << ss.str();

	//Exil::JsonParser jparser(ss);

	//Exil::Value* object = jparser.parseObject();

	//std::cout << object;

	//Exil::JsonStream jout(std::cout);

	//jout << object;

	std::cin.get();

	return 0;
}
