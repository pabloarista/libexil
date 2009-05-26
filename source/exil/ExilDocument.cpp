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

#include "Exil.h"
#include "ExilDocument.h"
#include "ExilElement.h"
#include "tinyxml.h"

namespace Exil
{
	//--------
	Document::Document()
		: mDoc(0)
	{
		mDoc = new TiXmlDocument();
	}

	//--------
	Document::Document(const String& filename)
		: mFilename(filename)
	{
		mDoc = new TiXmlDocument(filename);
	}

	//--------
	Document::~Document()
	{
		delete mDoc;
		mDoc = 0;
	}

	//--------
	Element Document::getFirstChild()
	{
		if(mDoc)
			return Element(mDoc->FirstChildElement());

		return Element(NULL);
	}

	//--------
	void Document::addChild(Element el)
	{
		if(mDoc && el.isValid())
			mDoc->LinkEndChild(el.mElement);
	}

	//--------
	void Document::print()
	{
		if(mDoc)
			mDoc->Print();
	}

	//--------
	void Document::save(const String& filename)
	{
		if(mDoc)
		{
			if(!filename.empty())
				mDoc->SaveFile(filename);
			else if(!mFilename.empty())
				mDoc->SaveFile(mFilename);
			else
				throw "Could not save document. No filename specified.";
		}
	}

	//--------
	std::ostream& operator<<(std::ostream& os, const Document& doc)
	{
		os << *(doc.mDoc);
		return os;
	}


};//namespace Spark
