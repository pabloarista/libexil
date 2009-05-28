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

#ifndef _EXIL_DOCUMENT_H_
#define _EXIL_DOCUMENT_H_
#pragma once

#include "Exil.h"

namespace Exil
{

	///
	/// @class Document
	class EXIL_API Document
	{
	public:
		Document();
		Document(const String& filename);
		~Document();
		Element getFirstChild();
		void addChild(Element el);
		void print();
		void save(const String& filename = BLANK_STRING);
		void load(const String& filename = BLANK_STRING);

	private:
		TiXmlDocument* mDoc;
		String mFilename;

		friend std::ostream EXIL_API &operator<<(std::ostream& os, const Document& doc);
	};

	/// Output function for Document objects.
	/// @param os The stream to which the Document is to be written
	/// @param doc The document object being written
	/// @return A reference to the stream being passed in
	std::ostream EXIL_API &operator<<(std::ostream& os, const Document& doc);

};//namespace Exil

#endif//_EXIL_DOCUMENT_H_
