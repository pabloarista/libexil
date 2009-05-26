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
#include "ExilStringConverter.h"
#include <locale>

namespace Exil
{
	namespace Convert
	{
		//--------
		String& toLower(String& str)
		{
			// convert to lower case
			size_t i = 0;
			size_t length = str.size();
			for(; i < length; ++i)
				str[i] = std::tolower(str[i], std::locale(""));
				
			return str;
		}
		
		//--------
		String& toUpper(String& str)
		{
			// convert to lower case
			size_t i = 0;
			size_t length = str.size();
			for(; i < length; ++i)
				str[i] = std::toupper(str[i], std::locale(""));
				
			return str;
		}

		//--------
		String toLower(const String& str)
		{
			String temp = str;
			// convert to lower case
			size_t i = 0;
			size_t length = temp.size();
			for(; i < length; ++i)
				temp[i] = std::tolower(temp[i], std::locale(""));
				
			return temp;
		}
		
		//--------
		String toUpper(const String& str)
		{
			String temp = str;
			// convert to lower case
			size_t i = 0;
			size_t length = temp.size();
			for(; i < length; ++i)
				temp[i] = std::toupper(temp[i], std::locale(""));
				
			return temp;
		}

		String toString(bool data)
		{
			std::stringstream ss;
			if(data)
				ss << "true";
			else
				ss << "false";

			return ss.str();
		}
		
	};//namespace Convert

};//namespace Exil
