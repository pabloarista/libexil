#include <ExilJsonStream.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	JsonStream::JsonStream( std::iostream& stream, bool pretty )
		: mStream(stream), mPretty(pretty), mTabCount(0), mParser(stream)
	{

	}

	JsonStream& JsonStream::operator<<( Value* value )
	{
		_writeValue(value);
		//delete value;
		return *this;
	}

	void JsonStream::_writeObject( Object* object, bool leadTab /*= true*/ )
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

	void JsonStream::_writeArray( Array* list, bool leadTab /*= true*/ )
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

	void JsonStream::_writePair( const String& name, Value* value, bool comma /*= true*/ )
	{
		mStream << mTabs << "\"" << name << "\" : ";
		_writeValue(value, comma, false);
	}

	void JsonStream::_writeValue( Value* value, bool comma /*= false*/, bool leadTab /*= true*/ )
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

	void JsonStream::_increaseTab()
	{
		if(!mPretty)
			return;
		mTabCount += 1;
		mTabs += '\t';
	}

	void JsonStream::_decreaseTab()
	{
		if(!mPretty)
			return;
		mTabCount -= 1;
		mTabs.erase(mTabCount, 1);
	}
};//namespace Exil