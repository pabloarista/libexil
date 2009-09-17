#include <ExilArray.h>

namespace Exil
{
	Array::Array()
	{
		type = Types::Array;
	}

	void Array::addValue( Value* value )
	{
		values.push_back(value);
	}

	std::ostream& operator<< (std::ostream& os, Array* val)
	{
		os << "[" << std::endl;

		for(ValueList::iterator iter = val->values.begin();
			iter != val->values.end();
			++iter)
		{
			os << *iter << std::endl;
		}

		os << "]" << std::endl;
		return os;
	}	

};

