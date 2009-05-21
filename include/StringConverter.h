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

#ifndef _EXIL_STRINGCONVERTER_H_
#define _EXIL_STRINGCONVERTER_H_
#pragma once

#include "Exil.h"

namespace Exil
{
	namespace Convert
	{
		/// Converts a string to lower case.
		String EXIL_API &toLower(String& str);
		
		/// Converts a string to upper case.
		String EXIL_API &toUpper(String& str);
		
		/// Converts a string to lower case.
		String EXIL_API toLower(const String& str);
		
		/// Converts a string to upper case.
		String EXIL_API toUpper(const String& str);
		
		/// Converts a string to an int
		inline int EXIL_API toInt(const String& str)
		{
			return atoi(str.c_str());
		}
		
		/// Converts a string to a float
		inline float EXIL_API toFloat(const String& str)
		{
			return static_cast<float>(atof(str.c_str()));
		}
		
		/// Converts a string to a double
		inline double EXIL_API toDouble(const String& str)
		{
			return atof(str.c_str());
		}
		
		/// Converts any type with an operator<< to a string
		template <typename TType>
		String toString(TType data)
		{
			std::stringstream ss;
			ss << data;
			return ss.str();
		}

		String EXIL_API toString(bool data);

	};//namespace Convert

};//namespace Exil

#endif//_EXIL_STRINGCONVERTER_H_
