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

#ifndef _EXIL_H_
#define _EXIL_H_
#pragma once

#include <string>
#include <sstream>

// Macros for printing messages in the compile log
//
// Use:
// #pragma message(__LOC__ "This is the message!")
//
// Output:
// d:\project\include\Exil\Exil.h(11) : This is the message!
//
// source: http://www.codeproject.com/KB/macros/location_pragma.aspx
#ifndef __LOC__
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : "
#endif

/// DLL Export definition
#ifdef EXIL_EXPORTS
#	define EXIL_API __declspec(dllexport)
#else
#	define EXIL_API __declspec(dllimport)
#	ifdef _DEBUG
#		pragma message(__LOC__ "Including Exil_d.lib")
#		pragma comment(lib, "Exil_d.lib")
#	else
#		pragma message(__LOC__ "Including Exil.lib")
#		pragma comment(lib, "Exil.lib")
#	endif
#endif

// forward declare the TinyXML classes
class TiXmlDocument;
class TiXmlElement;

namespace Exil
{
	namespace ResultCodes
	{
		enum ResultCode
		{
			/// Returned when an element or attribute is successfully found
			SUCCESS = 0,
			/// Returned when 
			NOATTRIBUTE = 1,
			WRONGTYPE = 2
		};
	};
	typedef ResultCodes::ResultCode ResultCode;

	class Element;
	class Document;

	typedef std::string String;
	const String BLANK_STRING;

};//namespace Exil

#endif//_EXIL_H_
