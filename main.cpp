#include <iostream>
#include <sstream>

#include <ExilXmlFormatter.h>
#include <ExilXmlParser.h>
#include <ExilJsonFormatter.h>
#include <ExilJsonParser.h>
#include <ExilBinFormatter.h>
#include <ExilBinParser.h>
#include <ExilTimer.h>
#include <ExilDataStream.h>

typedef Exil::String String;

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

		static Vector3 convertFrom(Value* value)
		{
			Object* object = value->toObject();

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
			Object* object = value->toObject();

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
			Object* object = value->toObject();

			Player player;
			player.name = object->getValue<String>("name");
			player.id = object->getValue<int>("id");
			player.position = object->getValue<Vector3>("position");
			player.items = object->getValue<ItemList>("items");
			player.alive = object->getValue<bool>("alive");
			player.dead = object->getValue<bool>("dead");
			return player;
		}
	};

};//namespace Exil

#pragma region Tests

const int TEST_LIMIT = 10000;

template <class StreamType>
void test(const Player& p)
{
	std::stringstream ss;
	StreamType stream(ss);
	Exil::Timer timer;
	timer.reset();
	std::cout << "Write test for: " << typeid(StreamType).name() << std::endl;
	for(int i = 0; i < TEST_LIMIT; ++i)
	{
		stream << p;
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
	std::cout << "Size was: " << ss.str().length() << std::endl;
	//String str = ss.str();


	Player p2;

	timer.reset();
	std::cout << "Read test for: " << typeid(StreamType).name() << std::endl;
	for(int i = 0; i < TEST_LIMIT; ++i)
	{
		stream >> p2;
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
	std::cout << std::endl;
}

void testAlloc()
{
	Exil::Timer timer;
	timer.reset();
	std::cout << "Value allocation test" << std::endl;
	Exil::ValueList list;
	for(int i = 0; i < TEST_LIMIT * 10; ++i)
	{
		list.push_back(new Exil::Value("Testing!"));
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;

	timer.reset();
	std::cout << "Value Deletion Test" << std::endl;
	Exil::ValueList::iterator iter = list.begin();
	for(int i = 0; i < TEST_LIMIT * 10; ++i)
	{
		Exil::Value* v = *iter;
		++iter;
		delete v;
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
	std::cout << std::endl;
}


inline void optimalSerialize(std::stringstream& ss, Player& player)
{
	// write the name
	int i;
	i = player.name.size();
	ss.write(reinterpret_cast<char*>(&i), sizeof(int));
	ss.write(player.name.c_str(), player.name.size() * sizeof(char));

	// write the id
	ss.write(reinterpret_cast<char*>(&player.id), sizeof(int));

	// write bools
	ss.write(reinterpret_cast<char*>(&player.alive), sizeof(char));
	ss.write(reinterpret_cast<char*>(&player.dead), sizeof(char));

	// write position
	ss.write(reinterpret_cast<char*>(&player.position.x), sizeof(float));
	ss.write(reinterpret_cast<char*>(&player.position.y), sizeof(float));
	ss.write(reinterpret_cast<char*>(&player.position.z), sizeof(float));

	// write items
	i = player.items.size();
	ss.write(reinterpret_cast<char*>(&i), sizeof(int));
	for(ItemList::iterator iter = player.items.begin();
		iter != player.items.end();
		++iter)
	{
		Item& item = *iter;
		i = item.name.size();
		ss.write(reinterpret_cast<char*>(&i), sizeof(int));
		ss.write(item.name.c_str(), item.name.size() * sizeof(char));

		ss.write(reinterpret_cast<char*>(&item.quantity), sizeof(int));
	}
}

inline void optimalDeserialize(std::stringstream& ss, Player& player)
{
	// read the name
	int i(0);
	ss.read(reinterpret_cast<char*>(&i), sizeof(int));
	char* buff = new char[i + 1];
	ss.read(buff, i * sizeof(char));
	buff[i] = 0;
	player.name = buff;
	delete buff;

	// write the id
	ss.read(reinterpret_cast<char*>(&player.id), sizeof(int));

	// write bools
	ss.read(reinterpret_cast<char*>(&player.alive), sizeof(char));
	ss.read(reinterpret_cast<char*>(&player.dead), sizeof(char));

	// write position
	ss.read(reinterpret_cast<char*>(&player.position.x), sizeof(float));
	ss.read(reinterpret_cast<char*>(&player.position.y), sizeof(float));
	ss.read(reinterpret_cast<char*>(&player.position.z), sizeof(float));

	// write items
	ss.read(reinterpret_cast<char*>(&i), sizeof(int));
	int k = 0;
	for(int j = 0; j < i; ++j)
	{
		Item item;
		ss.read(reinterpret_cast<char*>(&k), sizeof(int));
		buff = new char[k + 1];
		ss.read(buff, k * sizeof(char));
		buff[k] = 0;
		item.name = buff;
		delete buff;
		ss.read(reinterpret_cast<char*>(&item.quantity), sizeof(int));
		player.items.push_back(item);
	}
}

void testOptimal(Player& player)
{
	std::stringstream ss;
	Exil::Timer timer;
	timer.reset();
	std::cout << "Write test for: Optimal" << std::endl;
	for(int i = 0; i < TEST_LIMIT; ++i)
	{
		optimalSerialize(ss, player);
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
	std::cout << "Size was: " << ss.str().length() << std::endl;

	Player p2;
	timer.reset();
	std::cout << "Read test for: Optimal" << std::endl;
	for(int i = 0; i < TEST_LIMIT; ++i)
	{
		optimalDeserialize(ss, p2);
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
	std::cout << std::endl;
}
#pragma endregion Tests

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

	test<Exil::JsonStream>(player);
	test<Exil::XmlStream>(player);
	test<Exil::BinStream>(player);
	testOptimal(player);
	testAlloc();

	test<Exil::JsonStream>(player);
	test<Exil::XmlStream>(player);
	test<Exil::BinStream>(player);
	testOptimal(player);
	testAlloc();
	std::cin.get();

	return 0;
}
