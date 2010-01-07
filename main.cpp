#include <iostream>
#include <sstream>

/// DataStream definitions
#include <ExilDataStream.h>

/// basic types
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>
#include <ExilReader.h>
#include <ExilWriter.h>

/// only needed for tests
#include <ExilTimer.h>

typedef Exil::String String;

struct Vector3
{
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x,y,z;
};

struct Item
{
	Item(const std::string& n = Exil::BLANK_STRING, int q = 0)
		: name(n), quantity(q)
	{}
	std::string name;
	int quantity;
};

typedef std::list<Item> ItemList;

struct Player
{
	std::string name;
	int id;
	Vector3 position;
	ItemList items;
	bool alive;
	bool dead;
};

namespace Exil
{
	template <>
	struct ConvertType<Vector3>
	{
		static void To(Vector3& t, Writer& writer)
		{
			writer.CreateObject()
				.set("x",t.x)
				.set("y",t.y)
				.set("z",t.z);
		}

		static void From(Vector3& t, Reader& reader)
		{
			reader.CreateObject()
				.get("x", t.x)
				.get("y", t.y)
				.get("z", t.z);
		}
	};

	template <>
	struct ConvertType<Item>
	{
		static void To(Item& t, Writer& writer)
		{
			writer.CreateObject()
				.set("name",t.name)
				.set("quantity",t.quantity);
		}

		static void From(Item& t, Reader& reader)
		{
			reader.CreateObject()
				.get("name", t.name)
				.get("quantity", t.quantity);
		}
	};

	template <>
	struct ConvertType<Player>
	{
		static void To(Player& t, Writer& writer)
		{
			writer.CreateObject()
				.set("name",t.name)
				.set("id", t.id)
				.set("position", t.position)
				.set("items", t.items)
				.set("alive", t.alive)
				.set("dead", t.dead);
		}

		static void From(Player& t, Reader& reader)
		{
			reader.CreateObject()
				.get("name", t.name)
				.get("id", t.id)
				.get("position", t.position)
				.get("items", t.items)
				.get("alive", t.alive)
				.get("dead", t.dead);
		}
	};

};//namespace Exil

#pragma region Tests

const int TEST_LIMIT = 10000;

void test(Player& p)
{
	Exil::Timer timer;
	timer.reset();
	std::cout << "Construction test for: buffer" << std::endl;
	{
		Exil::Buffer buffer(1024);
		Exil::Writer writer(buffer);

		std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
		std::cout << std::endl;

		timer.reset();
		std::cout << "Write test for: writer" << std::endl;
		for(int i = 0; i < TEST_LIMIT; ++i)
		{
			Exil::ConvertType<Player>::To(p, writer);
		}
		std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
		std::cout << "Size was: ~" << writer.getSize() << std::endl;

		Exil::Reader reader(buffer);
		Player p2;

		timer.reset();
		std::cout << "Read test for: reader" << std::endl;
		for(int i = 0; i < TEST_LIMIT; ++i)
		{
			Exil::ConvertType<Player>::From(p2, reader);
		}
		std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
		std::cout << std::endl;

		timer.reset();
		std::cout << "Destruction test for: buffer" << std::endl;
	}
	std::cout << "Test took: " << timer.getTimeElapsed() << std::endl;
	std::cout << std::endl;
}



/*
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
*/
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

	test(player);
/*
	Exil::dsout << player;

	
	/// Performance tests
	test<Exil::JsonStream>(player);
	test<Exil::XmlStream>(player);
	test<Exil::BinStream>(player);
	testOptimal(player);
	testAlloc();
	/// Second pass
	test<Exil::JsonStream>(player);
	test<Exil::XmlStream>(player);
	test<Exil::BinStream>(player);
	testOptimal(player);
	testAlloc();
*/	

	std::cin.get();

	return 0;
}
