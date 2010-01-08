#ifndef Tests_h__
#define Tests_h__

#include "Exil.h"
#include "ExilData.h"
#include "ExilWriter.h"
#include "ExilReader.h"

#include <list>

const std::string BLANK_STRING;

struct Vector3
{
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x,y,z;
};

struct Item
{
	Item(const std::string& n = BLANK_STRING, int q = 0)
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

template <>
struct Exil::ConvertType<Vector3>
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
struct Exil::ConvertType<Item>
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
struct Exil::ConvertType<Player>
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

template <typename T>
struct Exil::ConvertType<std::list<T> >
{
	static void To(std::list<T>& list, Writer& writer)
	{
		writer.CreateArray()
			.set(list);
	}

	static void From(std::list<T>& list, Reader& reader)
	{
		reader.CreateArray()
			.get(list);
	}
};

#endif // Tests_h__
