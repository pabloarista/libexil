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

#ifndef _EXIL_ELEMENT_H_
#define _EXIL_ELEMENT_H_
#pragma once

#include "Exil.h"
#include "ExilStringConverter.h"

namespace Exil
{
	/// A thin wrapper around a TiXmlElement.
	///
	///
	class EXIL_API Element
	{
	public:
		Element();
		Element(TiXmlElement* el);
		Element(const Element& copy);

		Element& operator=(const Element& other);

		void create(const String& type);

		bool isValid() const;

		Element getNextSibling() const;

		Element getFirstChild() const;

		Element getFirstChild(const String& type) const;

		String getType() const;

		String getName() const;

		/// Templated function for serializing an element into an
		/// object. The object's class must derive from XmlSerializable
		/// and must be of the appropriate type.
		///
		/// @param name The name attribute of the element to be deserialized.
		/// @param obj The XmlSerializable object to which the element will be deserialized.
		template <typename TType>
		ResultCode getChildElement(const String& name, TType& obj) const;

		template <>
		ResultCode getChildElement(const String& name, int& value) const;

		template <>
		ResultCode getChildElement(const String& name, float& value) const;

		template <>
		ResultCode getChildElement(const String& name, String& value) const;

		template <>
		ResultCode getChildElement(const String& name, bool& value) const;

		Element getChildElement(const String& name) const;

		ResultCode getAttribute(const String& name, int& value, int defaultValue = 0) const;

		ResultCode getAttribute(const String& name, float& value, float defaultValue = 0.0f) const;

		ResultCode getAttribute(const String& name, String& value, const String& defaultValue = BLANK_STRING) const;

		ResultCode getAttribute(const String& name, bool& value, bool defaultValue = false) const;

		void setAttribute(const String& name, const String& value);

		template <typename TType>
		void setAttribute(const String& name, TType value);

		void addChild(Element child);

		bool hasText() const;
		String getText() const;
		void setText(const String& text);

	private:
		TiXmlElement* mElement;
		friend class Document;

		friend std::ostream EXIL_API & operator<<(std::ostream& os, const Element& doc);

	};//class Element

	//--------
	template <typename TType>
	inline void Element::setAttribute(const String& name, TType value)
	{
		setAttribute(name, Convert::toString(value));
	}

	//--------
	template <typename TType>
	ResultCode Element::getChildElement(const String& name, TType& obj) const
	{
		String type = TType::EXIL_SERIALIZABLE_TYPE;

		for(Element el = getFirstChild(); el.isValid(); el = el.getNextSibling())
		{
			String elementName = el.getName();
			String elementType = el.getType();
			if(elementName == name && elementType == type)
			{
				return obj.deserialize(el);
			}
			else if(elementName == name && elementType != type)
			{
				return ResultCodes::WRONGTYPE;
			}
		}
		return ResultCodes::NOATTRIBUTE;
	}

	//--------
	template <>
	ResultCode Element::getChildElement(const String& name, int& value) const
	{
		for(Element el = getFirstChild(); el.isValid(); el = el.getNextSibling())
		{
			String elementName = el.getName();
			String elementType = el.getType();
			if(elementName == name && elementType == "integer")
			{
				return el.getAttribute("value", value, 0);
			}
			else if(elementName == name && elementType != "integer")
			{
				return ResultCodes::WRONGTYPE;
			}
		}
		return ResultCodes::NOATTRIBUTE;
	}

	//--------
	template <>
	ResultCode Element::getChildElement(const String& name, float& value) const
	{
		for(Element el = getFirstChild(); el.isValid(); el = el.getNextSibling())
		{
			String elementName = el.getName();
			String elementType = el.getType();
			if(elementName == name && elementType == "float")
			{
				return el.getAttribute("value", value, 0.0f);
			}
			else if(elementName == name && elementType != "float")
			{
				return ResultCodes::WRONGTYPE;
			}
		}
		return ResultCodes::NOATTRIBUTE;
	}

	//--------
	template <>
	ResultCode Element::getChildElement(const String& name, String& value) const
	{
		for(Element el = getFirstChild(); el.isValid(); el = el.getNextSibling())
		{
			String elementName = el.getName();
			String elementType = el.getType();
			if(elementName == name && elementType == "string")
			{
				return el.getAttribute("value", value, BLANK_STRING);
			}
			else if(elementName == name && elementType != "string")
			{
				return ResultCodes::WRONGTYPE;
			}
		}
		return ResultCodes::NOATTRIBUTE;
	}

	//--------
	template <>
	ResultCode Element::getChildElement(const String& name, bool& value) const
	{
		for(Element el = getFirstChild(); el.isValid(); el = el.getNextSibling())
		{
			String elementName = el.getName();
			String elementType = el.getType();
			if(elementName == name && elementType == "bool")
			{
				return el.getAttribute("value", value, false);
			}
			else if(elementName == name && elementType != "bool")
			{
				return ResultCodes::WRONGTYPE;
			}
		}
		return ResultCodes::NOATTRIBUTE;
	}

	/// Output function for Element objects.
	/// @param os The stream to which the Element is to be written
	/// @param el The Element object being written
	/// @return A reference to the stream being passed in
	std::ostream EXIL_API &operator<<(std::ostream& os, const Element& el);

};//namespace Exil

#endif//_EXIL_ELEMENT_H_
