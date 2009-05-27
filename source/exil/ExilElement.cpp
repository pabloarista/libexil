/**
	Exil library. Simply compose objects from xml and serialize back.

	@author James Wynn
	@date 4/15/2009

	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

#include <Exil/Exil.h>
#include <Exil/ExilElement.h>
#include "tinyxml.h"

namespace Exil
{
	//--------
	Element::Element()
		: mElement(NULL)
	{
	}

	//--------
	Element::Element(TiXmlElement* el)
		: mElement(el)
	{
	}

	//--------
	Element::Element(const Element& copy)
	{
		mElement = copy.mElement;
	}

	//--------
	Element& Element::operator=(const Element& other)
	{
		mElement = other.mElement;
		return *this;
	}

	//--------
	void Element::create(const String& type)
	{
		delete mElement;
		mElement = new TiXmlElement(type);
	}

	//--------
	bool Element::isValid() const
	{
		return !!mElement;
	}

	//--------
	Element Element::getNextSibling() const
	{
		if(mElement)
			return Element(mElement->NextSiblingElement());

		return Element(NULL);
	}

	//--------
	Element Element::getFirstChild() const
	{
		if(mElement)
			return Element(mElement->FirstChildElement());

		return Element(NULL);
	}

	//--------
	String Element::getType() const
	{
		if(!mElement)
			return BLANK_STRING;

		return String(mElement->Value());
	}

	//--------
	String Element::getName() const
	{
		if(!mElement)
			return BLANK_STRING;

		String name;
		getAttribute("name", name, "");

		return name;
	}

	//--------
	ResultCode Element::getAttribute(const String& name, int& value, int defaultValue) const
	{
		if(!mElement)
			return ResultCodes::NOATTRIBUTE;

		int result = mElement->QueryIntAttribute(name.c_str(), &value);

		if(result != TIXML_SUCCESS)
			value = defaultValue;

		return ResultCodes::SUCCESS;
	}

	//--------
	ResultCode Element::getAttribute(const String& name, float& value, float defaultValue) const
	{
		if(!mElement)
			return ResultCodes::NOATTRIBUTE;

		int result = mElement->QueryFloatAttribute(name.c_str(), &value);

		if(result != TIXML_SUCCESS)
			value = defaultValue;

		return ResultCodes::SUCCESS;
	}

	//--------
	ResultCode Element::getAttribute(const String& name, String& value, const String& defaultValue) const
	{
		if(!mElement)
			return ResultCodes::NOATTRIBUTE;

		const char* temp = NULL;

		temp = mElement->Attribute(name.c_str());

		if(temp == NULL)
		{
			value = defaultValue;
			return ResultCodes::NOATTRIBUTE;
		}

		value = temp;
		return ResultCodes::SUCCESS;
	}

	//--------
	ResultCode Element::getAttribute(const String& name, bool& value, bool defaultValue) const
	{
		if(!mElement)
			return ResultCodes::NOATTRIBUTE;

		const char* temp = NULL;

		//Convert::toLower(name);
		temp = mElement->Attribute(name.c_str());

		if(temp == NULL)
		{
			value = defaultValue;
			return ResultCodes::NOATTRIBUTE;
		}
		// make the const char* into a String then convert it to lower case
		String str(temp);
		
		value = (str == "true");

		return ResultCodes::SUCCESS;
	}

	//--------
	Element Element::getChildElement(const String& name) const
	{
		for(Element el = getFirstChild(); el.isValid(); el = el.getNextSibling())
		{
			if(el.getName() == name)
			{
				return el;
			}
		}

		return Element();
	}

	//--------
	void Element::setAttribute(const String& name, const String& value)
	{
		if(mElement)
			mElement->SetAttribute(name, value);
	}

	//--------
	void Element::addChild(Element child)
	{
		mElement->LinkEndChild(child.mElement);
	}

	//--------
	bool Element::hasText() const
	{
		for(TiXmlNode* child = mElement->FirstChild(); child; child = child->NextSibling())
		{
			if(child->ToText())
				return true;
		}

		return false;
	}

	//--------
	String Element::getText() const
	{
		for(TiXmlNode* child = mElement->FirstChild(); child; child = child->NextSibling())
		{
			TiXmlText* textNode = child->ToText();
			if(textNode && textNode->CDATA())
			{
				return String(textNode->Value());
			}
		}

		return BLANK_STRING;
	}

	//--------
	void Element::setText(const String& text)
	{
		for(TiXmlNode* child = mElement->FirstChild(); child; child = child->NextSibling())
		{
			TiXmlText* textNode = child->ToText();
			if(textNode && textNode->CDATA())
			{
				textNode->SetValue(text);
				return;
			}
		}

		TiXmlText* textNode = new TiXmlText(text);
		textNode->SetCDATA(true);
		mElement->LinkEndChild(textNode);
	}

	//--------
	std::ostream& operator<<(std::ostream& os, const Element& el)
	{
		os << *(el.mElement);
		return os;
	}

};//namespace Exil
