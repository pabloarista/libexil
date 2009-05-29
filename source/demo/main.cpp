#include <Exil/Exil.h>
#include <Exil/ExilDocument.h>
#include <Exil/ExilElement.h>
#include <Exil/ExilSerializable.h>

#include <iostream>

typedef std::string String;


class Person : public Exil::Serializable
{
public:
	const static String EXIL_SERIALIZABLE_TYPE;
public:
	Person()
		: mName(), mAge(-1.0f)
	{
	}

	Person(const String& name, float age)
		: mName(name), mAge(age)
	{
	}

	Exil::Element serialize(const String& name)
	{
		Exil::Element element;
		element.create(EXIL_SERIALIZABLE_TYPE);
		element.setAttribute("name", name);
		element.setAttribute("personName", mName);
		element.setAttribute("age", mAge);
		return element;
	}

	Exil::ResultCode deserialize(Exil::Element element)
	{
		element.getAttribute("personName", mName, String("NO NAME!"));
		element.getAttribute("age", mAge, -1.0f);
		return Exil::ResultCodes::SUCCESS;
	}

public:
	String mName;
	float mAge;
};

const String Person::EXIL_SERIALIZABLE_TYPE = "Person";


std::ostream& operator<<(std::ostream& os, Person& person)
{
	return os << person.mName << " is " << person.mAge << " years old." << std::endl;
}

int main()
{
	Exil::Document doc;
	Exil::Element root;

	root.create("Thing");
	doc.addChild(root);
	root.setAttribute("x", "woooo");
	root.setText("WHATAHAHAHAHA!!");

	{
		Exil::Element obj;
		obj.create("Woopty");
		obj.setAttribute("name", "hoohoo");
		obj.setAttribute("x", "thingtastic");
		obj.setAttribute("anInt", 200);
		obj.setAttribute("isBoolean", true);
		obj.setAttribute("pi", 3.14159);
		root.addChild(obj);
		Person person1("steve jackson", 34);
		root.addChild(person1.serialize("person1"));
		std::cout << obj << std::endl;
	}

	doc.print();
	std::cout << doc << std::endl;

	{
		Exil::Element obj1 = root.getChildElement("hoohoo");
		Exil::String x;
		int anInt = 0;
		bool isBoolean = false;
		float pi = 0.0f;
		obj1.getAttribute("x", x, "");
		obj1.getAttribute("anInt", anInt, 10);
		obj1.getAttribute("isBoolean", isBoolean, false);
		obj1.getAttribute("pi", pi, 1.0);
		Person person2;
		Person person3;
		root.getChildElement("person1", person2);
		Exil::Element elPerson2 = root.getChildElement("person1");
/*		Exil::Element elPerson3 = elPerson2.getNextSibling();

		for(Exil::Element child = root.getChildElement("person1");
			!child.isValid();
			child = child.getNextSibling())
		{
			// do something
		}
*/
		std::cout
			<< "x = " << x << std::endl
			<< "anInt = " << anInt << std::endl
			<< "isBoolean = " << (isBoolean ? "true" : "false") << std::endl
			<< "pi = " << pi << std::endl
			<< person2 << std::endl;
	}

	std::cin.get();

	Exil::Document doc2;
	doc2.load("d:/pathways/media/Avatar.xml");

	std::cout << "AVATAR.XML" << std::endl;
	doc2.print();

	Exil::Element root2 = doc2.getFirstChild();
	Exil::Element bodiesElement = root2.getFirstChild("Bodies");
	std::cout << root2.getType() << std::endl;

	if(!bodiesElement.isValid())
		std::cout << "<Bodies> is not valid" << std::endl;

	Exil::Element bodyElement = bodiesElement.getFirstChild();
	std::cout << "First body is named: " << bodyElement.getName() << std::endl;

	std::cin.get();

	return 0;
}

