#include <ExilObject.h>

namespace Exil
{
	Object::Object()
	{
		type = Types::Object;
	}

	void Object::addValue( const String& name, Value* value )
	{
		values.insert(Pair(name, value));
	}

	std::ostream& operator<< (std::ostream& os, Object* val)
	{
		os << "{" << std::endl;

		for(ValueMap::iterator iter = val->values.begin();
			iter != val->values.end();
			++iter)
		{
			os << iter->first << " = " << iter->second << std::endl;
		}

		os << "}" << std::endl;
		return os;
	}

};//namespace Exil
