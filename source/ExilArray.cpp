#include <ExilArray.h>
#include <ExilObject.h>
#include <ExilDataStream.h>

namespace Exil
{
	Array::Array()
	{
		mType = Types::Array;
	}

	Array::~Array()
	{
		for(ValueList::iterator iter = values.begin();
			iter != values.end();
			++iter)
		{
			delete *iter;
		}
	}

	void Array::addValue( Value* value )
	{
		values.push_back(value);
	}

	//std::ostream& operator<< (std::ostream& os, Array* val)
	//{
	//	dsout << val;

	//	//os << "[" << std::endl;

	//	//for(ValueList::iterator iter = val->values.begin();
	//	//	iter != val->values.end();
	//	//	++iter)
	//	//{
	//	//	os << *iter << std::endl;
	//	//}

	//	//os << "]" << std::endl;
	//	return os;
	//}	

};

