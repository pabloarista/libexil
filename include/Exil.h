#ifndef Exil_h__
#define Exil_h__

#include <string>
#include <map>
#include <list>
#include <map>

namespace Exil
{
	typedef std::string String;

	struct Object;
	struct Array;
	struct Value;
	typedef std::pair<String, Value*> Pair;
	typedef std::map<String, Value*> ValueMap;
	typedef std::list<Value*> ValueList;

	template <typename T>
	struct TypeConversion
	{
		static Value* convertTo(typename T);

		static T convertFrom(Value*);
	};

};//namespace Exil

#endif // Exil_h__