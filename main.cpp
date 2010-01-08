#include <iostream>

#include "Exil.h"
#include "ExilTimer.h"
#include "ExilBuffer.h"
#include "ExilData.h"

#include "Tests.h"

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


int main()
{

	//	Writer writer;
	/*
	Vector3 v1(10,20,30);
	Vector3 v2;

	ConvertType<Vector3>::To(v1,writer);
	Reader reader(writer.mBuffer);
	ConvertType<Vector3>::From(v2, reader);
	*/
	/*
	Player player;
	player.name = "Zeus";
	player.id = 12345;
	player.position = Vector3(10,20,30);
	player.items.push_back(Item("Stick", 5));
	player.items.push_back(Item("Sword", 2));
	player.items.push_back(Item("Potion", 99));
	player.alive = true;
	player.dead = false;
	*/
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

	//ConvertType<Player>::To(player, writer);

	//Player player2;
	//Reader reader(writer.mBuffer);
	//ConvertType<Player>::From(player2, reader);

	test(player);
	test(player);
	test(player);
	test(player);
	test(player);
	test(player);
	test(player);
	test(player);
	test(player);


	/*
	creator.write("Hello World!", 12);
	creator.write(50);
	creator.write(3.14159f);

	int i = 0;
	float f = 0;
	std::string s;

	Reader reader(creator.mBuffer);
	reader.read(s);
	std::cout << "s = " << s.c_str() << std::endl;
	reader.read(i);
	std::cout << "i = " << i << std::endl;
	reader.read(f);
	std::cout << "f = " << f << std::endl;
	*/
	/*
	std::list<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	creator.write(list, 0);
	*/
	std::cin.get();

	return 0;
}