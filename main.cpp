#include <iostream>

#include "Exil.h"
#include "ExilTimer.h"
#include "ExilBuffer.h"
#include "ExilData.h"

#include "Tests.h"

const int TEST_LIMIT = 10000;

Player createPlayer()
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

	return player;
}

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
	Player player = createPlayer();
	//test(player);

	Exil::Buffer buff;
	Exil::Writer writer(buff);

	Exil::ConvertType<Player>::To(player, writer);

	Exil::RawBuffer* raw = buff.toString();

	Exil::Buffer buff2(raw->buffer, raw->size);
	Exil::Reader reader(buff2);

	Player player2;
	Exil::ConvertType<Player>::From(player2, reader);

	std::cin.get();

	return 0;
}