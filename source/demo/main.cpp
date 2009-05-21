#include "Exil.h"
#include "Document.h"
#include "Element.h"

#include <iostream>

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
	}
	doc.print();
	//std::cout << doc << std::endl;

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

		std::cout
			<< "x = " << x << std::endl
			<< "anInt = " << anInt << std::endl
			<< "isBoolean = " << (isBoolean ? "true" : "false") << std::endl
			<< "pi = " << pi << std::endl;
	}

	std::cin.get();

	return 0;
}

