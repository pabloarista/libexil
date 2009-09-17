#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	Object::Object()
	{
		type = Types::Object;
	}

	Object::~Object()
	{
		for(ValueMap::iterator iter = values.begin();
			iter != values.end();
			++iter)
		{
			delete iter->second;
		}
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
			os << "\"" << iter->first << "\" = " << iter->second << std::endl;
		}

		os << "}" << std::endl;
		return os;
	}

};//namespace Exil
