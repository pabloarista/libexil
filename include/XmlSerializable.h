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

#ifndef _EXIL_XMLSERIALIZABLE_H_
#define _EXIL_XMLSERIALIZABLE_H_
#pragma once

#include "Exil.h"

namespace Exil
{
	/// Interface for serializing to XML.
	/// @class XmlSerializable
	/// Must also implement:
	///		The name of the class, used for deserialization detection
	///			public static const String XMLSERIALIZABLE_TYPE = "ClassName";
	class XmlSerializable
	{
	public:
		XmlSerializable() {}
		virtual ~XmlSerializable() {}
		
		/// Passes parent node to which data is serialized.
		virtual XML::Element serialize(const String& name) = 0;
		
		/// Passes parent node from which data is deserialized.
		/// @remark Why is element not passed as a reference?
		virtual XML::ResultCode deserialize(XML::Element element) = 0;
	};

};//namespace Exil

#endif//_EXIL_XMLSERIALIZABLE_H_
