
#include <iostream>
#include <list>
#include <vector>

#include "Exil.h"
#include "ExilTimer.h"
#include "ExilBuffer.h"

#pragma pack(push,1)

namespace Exil
{

	class Writer
	{
	public:
		Writer(Buffer& buffer)
			: mBuffer(buffer)
		{
		}
	
		template <typename T>
		void write(const T& value);
	
		template <typename T>
		void write(const T* value);
	
		Data::Object& CreateObject();
	
		Data::Array& CreateArray();
	
		static SizeT GetSize(const char* ptr)
		{
			return *reinterpret_cast<const SizeT*>(ptr - sizeof(SizeT));
		}
	
		static Type GetType(const char* ptr)
		{
			InternalType it = *reinterpret_cast<const InternalType*>(ptr);
			return static_cast<Type>(it);
		}
	
		size_t getSize() const
		{
			return mBuffer.getSize();
		}
	
	private:
		Buffer& mBuffer;
	};
	
	class Reader
	{
	public:
		Reader(Buffer& buffer)
			: mBuffer(buffer)
		{
		}
	
		template <typename T>
		void read(T& value);
	
		Data::Object& CreateObject();
	
		Data::Array& CreateArray();
	
	private:
		Buffer& mBuffer;
	};
	
	
	template <typename T>
	struct ConvertType
	{
		static void To(T& t, Writer& writer)
		{
			writer.write(t);
		}
	
		static void From(T& t, Reader& reader)
		{
			reader.read(t);
		}
	};
	
namespace Data
{
	
		class Object
		{
		private:
			Object(const Object&);
		public:
			Object(Reader* reader)
			{
				if(mType != Types::Object)
					throw "Not an Object";
		
				mSystem = reader;
			}
		
			Object(Writer* writer)
			{
				mType = Types::Object;
				mNumItems = 0;
				mSystem = writer;
			}
		
			SizeT getNumItems()
			{
				return mNumItems;
			}
		
			static SizeT Size(SizeT len)
			{
				return sizeof(Object);
			}
		
			template <typename T>
			Object& set(const char* str, T& value)
			{
				++mNumItems;
				Writer* writer = static_cast<Writer*>(mSystem);
				ConvertType<const char*>::To(str, *writer);
				ConvertType<T>::To(value, *writer);
				return *this;
			}
		
			template <typename T>
			Object& get(const char* str, T& value)
			{
				Reader* reader = static_cast<Reader*>(mSystem);
		
				std::string s;
				ConvertType<std::string>::From(s, *reader);
				if(strcmp(str, s.c_str()) != 0)
					throw "Incorrect key name";
		
				ConvertType<T>::From(value, *reader);
				return *this;
			}
		
		private:
			InternalType mType;
			SizeT mNumItems;
			void* mSystem;
		};
		
		class Array
		{
		public:
			Array(Reader* reader)
			{
				if(mType != Types::Array)
					throw "Not an Array";
				mSystem = reader;
			}
		
			Array(Writer* writer)
				: mType(Types::Array), mNumItems(0)
			{
				mSystem = writer;
			}
		
			template <typename T>
			Array& add(T& value)
			{
				Writer* writer = static_cast<Writer*>(mSystem);
				++mNumItems;
				ConvertType<T>::To(value, *writer);
				return *this;
			}
		
			template <typename T>
			void set(std::list<T>& list)
			{
				for(std::list<T>::iterator iter = list.begin();
					iter != list.end();
					++iter)
				{
					add(*iter);
				}
			}
		
			template <typename T>
			Array& get(std::list<T>& list)
			{
				Reader* reader = static_cast<Reader*>(mSystem);
		
				for(SizeT i = 0; i < mNumItems; ++i)
				{
					T value;
					ConvertType<T>::From(value, *reader);
					list.push_back(value);
				}
				return *this;
			}
		
			SizeT getValue()
			{
				return mNumItems;
			}
		
			static SizeT Size(SizeT len)
			{
				return sizeof(Array);
			}
		
		private:
			InternalType mType;
			SizeT mNumItems;
			void* mSystem;
		};
		
		class String
		{
		public:
			String()
			{
				if(mType != Types::String)
					throw "Not a String";
			}
		
			String(const char* str, SizeT len)
			{
				mType = Types::String;
				char* value = reinterpret_cast<char*>(&mType) + sizeof(mType);
				memcpy(value, str, len);
			}
		
			String(const std::string& str)
			{
				mType = Types::String;
				char* value = reinterpret_cast<char*>(&mType) + sizeof(mType);
				memcpy(value, str.c_str(), str.size());
			}
		
			const char* getValue()
			{
				return reinterpret_cast<char*>(&mType) + sizeof(InternalType);
			}
		
			SizeT getLength()
			{
				return *(reinterpret_cast<SizeT*>(&mType) - sizeof(InternalType)) - sizeof(InternalType);
			}
		
			static SizeT Size(SizeT len)
			{
				return sizeof(InternalType) + len;
			}
		
		private:
			InternalType mType;
		};
		
		class Float
		{
		public:
			Float()
			{
				if(mType != Types::Float)
					throw "Not a Float!";
			}
			Float(float f)
			{
				mType = Types::Float;
				mValue = f;
			}
		
			float getValue()
			{
				return mValue;
			}
		
		private:
			InternalType mType;
			float mValue;
		};
		
		class Integer
		{
		public:
			Integer()
			{
				if(mType != Types::Integer)
					throw "Not an Integer";
			}
		
			Integer(int i)
			{
				mType = Types::Integer;
				mValue = i;
			}
		
			inline int getValue()
			{
				return mValue;
			}
		
		private:
			InternalType mType;
			int mValue;
		};
		
		class Boolean
		{
		public:
			Boolean()
			{
				if(mType != Types::Boolean)
					throw "Not a Boolean";
			}
		
			Boolean(bool b)
			{
				mType = Types::Boolean;
				mValue = b;
			}
		
			inline bool getValue()
			{
				return mValue;
			}
		
		private:
			InternalType mType;
			bool mValue;
		};
		

};//namespace Data

	#pragma region read
	
	template <>
	void Reader::read(int& value)
	{
		Data::Integer* i = new(mBuffer.reallocate(sizeof(Data::Integer))) Data::Integer();
		value = i->getValue();
	}
	
	template <>
	void Reader::read(float& value)
	{
		Data::Float* f = new(mBuffer.reallocate(sizeof(Data::Float))) Data::Float();
		value = f->getValue();
	}
	
	template <>
	void Reader::read(bool& value)
	{
		Data::Boolean* b = new(mBuffer.reallocate(sizeof(Data::Boolean))) Data::Boolean();
		value = b->getValue();
	}
	
	template <>
	void Reader::read(std::string& value)
	{
		char* ptr = mBuffer.reallocate(sizeof(Data::String));
		Data::String* s = new(ptr) Data::String();
		const char* c = s->getValue();
		SizeT len = s->getLength();
		value = std::string(s->getValue(), s->getLength());
	}
	
	Data::Object& Reader::CreateObject()
	{
		Data::Object* obj = new(mBuffer.reallocate(Data::Object::Size(0))) Data::Object(this);
		return *obj;
	}
	
	Data::Array& Reader::CreateArray()
	{
		Data::Array* arr = new(mBuffer.reallocate(Data::Array::Size(0))) Data::Array(this);
		return *arr;
	}
	
	
	#pragma endregion read
	#pragma region write
	
	template <>
	void Writer::write(const int& value)
	{
		new(mBuffer.allocate(sizeof(Data::Integer))) Data::Integer(value);
	}
	
	template <>
	void Writer::write(const float& value)
	{
		new(mBuffer.allocate(sizeof(Data::Float))) Data::Float(value);
	}
	
	template <>
	void Writer::write(const bool& value)
	{
		new(mBuffer.allocate(sizeof(Data::Boolean))) Data::Boolean(value);
	}
	
	template <>
	void Writer::write(const std::string& value)
	{
		new(mBuffer.allocate(Data::String::Size(value.size()))) Data::String(value);
	}
	
	template <>
	void Writer::write(const char* value)
	{
		SizeT length = strlen(value);
		new(mBuffer.allocate(Data::String::Size(length))) Data::String(value, length);
	}
	
	Data::Object& Writer::CreateObject()
	{
		Data::Object* obj = new(mBuffer.allocate(Data::Object::Size(0))) Data::Object(this);
		return *obj;
	}
	
	Data::Array& Writer::CreateArray()
	{
		Data::Array* arr = new(mBuffer.allocate(Data::Array::Size(0))) Data::Array(this);
		return *arr;
	}

};//namespace Exil

#pragma endregion write
#pragma region Tests
/*
template <typename T>
struct ConvertType
{
static void To(T, Creator&);
static void From(T&, Creator&);
};
*/

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

#pragma endregion Tests


#pragma pack(pop)

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