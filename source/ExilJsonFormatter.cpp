#include <ExilJsonFormatter.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	JsonFormatter::JsonFormatter( std::ostream& stream, bool pretty )
		: mStream(stream), mPretty(pretty), mTabCount(0)
	{

	}

	JsonFormatter& JsonFormatter::operator<<( Value* value )
	{
		_writeValue(value);
		delete value;
		return *this;
	}

	void JsonFormatter::_writeObject( Object* object, bool leadTab /*= true*/ )
	{
		mStream << (leadTab?mTabs:BLANK_STRING) << "{";
		_increaseTab();

		if(mPretty)
			mStream << std::endl;

		for(ValueMap::iterator iter = object->values.begin();
			iter != object->values.end();)
		{
			ValueMap::iterator current = iter++;
			_writePair(current->first, current->second, iter != object->values.end());
		}

		_decreaseTab();
		mStream << mTabs << "}";
	}

	void JsonFormatter::_writeArray( Array* list, bool leadTab /*= true*/ )
	{
		mStream << (leadTab?mTabs:BLANK_STRING) << "[";
		_increaseTab();

		if(mPretty)
			mStream << std::endl;

		for(ValueList::iterator iter = list->values.begin();
			iter != list->values.end();
			++iter)
		{
			_writeValue(*iter, true);
		}

		_decreaseTab();
		mStream << mTabs << "]";
	}

	void JsonFormatter::_writePair( const String& name, Value* value, bool comma /*= true*/ )
	{
		mStream << mTabs << "\"" << name << "\" : ";
		_writeValue(value, comma, false);
	}

	void JsonFormatter::_writeValue( Value* value, bool comma /*= false*/, bool leadTab /*= true*/ )
	{
		switch(value->type())
		{
		case Value::Types::Array:
			_writeArray(value->toArray(), leadTab);
			break;
		case Value::Types::Object:
			_writeObject(value->toObject(), leadTab);
			break;
		case Value::Types::String:
			mStream << (leadTab?mTabs:BLANK_STRING) << "\"" << value->toString() << "\"";
			break;
		case Value::Types::Number:
			mStream << (leadTab?mTabs:BLANK_STRING) << value->toNumber<float>();
			break;
		case Value::Types::Bool:
			if(value->toBool())
				mStream << (leadTab?mTabs:BLANK_STRING) << "true";
			else
				mStream << (leadTab?mTabs:BLANK_STRING) << "false";
			break;
		case Value::Types::Null:
			mStream << (leadTab?mTabs:BLANK_STRING) << "null";
			break;
		}

		if(comma)
			mStream << ",";

		if(mPretty)
			mStream << std::endl;
	}

	void JsonFormatter::_increaseTab()
	{
		if(!mPretty)
			return;
		mTabCount += 1;
		mTabs += '\t';
	}

	void JsonFormatter::_decreaseTab()
	{
		if(!mPretty)
			return;
		mTabCount -= 1;
		mTabs.erase(mTabCount, 1);
	}
};//namespace Exil