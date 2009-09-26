#include <ExilBinStream.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	BinStream::BinStream( std::iostream& stream )
		: mStream(stream)
	{

	}

	BinStream& BinStream::operator<<( Value* value )
	{
		_writeValue(value);
		//delete value;
		return *this;
	}

	void BinStream::_writeObject( Object* object )
	{
		mStream << Value::Types::Object;
		mStream << object->values.size();
		for(ValueMap::iterator iter = object->values.begin();
			iter != object->values.end();)
		{
			ValueMap::iterator current = iter++;
			_writePair(current->first, current->second);
		}
	}

	void BinStream::_writeArray( Array* list )
	{
		mStream << Value::Types::Object;
		mStream << list->values.size();
		for(ValueList::iterator iter = list->values.begin();
			iter != list->values.end();
			++iter)
		{
			_writeValue(*iter);
		}
	}

	void BinStream::_writePair( const String& name, Value* value )
	{
		_writeString(name);
		_writeValue(value);
	}

	void BinStream::_writeValue( Value* value )
	{
		switch(value->type())
		{
		case Value::Types::Array:
			_writeArray(value->toArray());
			break;
		case Value::Types::Object:
			_writeObject(value->toObject());
			break;
		case Value::Types::String:
			mStream << Value::Types::String;
			_writeString(value->toString());
			break;
		case Value::Types::Number:
			mStream << Value::Types::Number;
			mStream << value->toNumber<float>();
			break;
		case Value::Types::Bool:
			mStream << Value::Types::Bool;
			mStream << value->toBool();
			break;
		case Value::Types::Null:
			mStream << Value::Types::Null;
			break;
		}
	}

	void BinStream::_writeString( const String& str )
	{
		mStream << str.size() << str.c_str();
	}
};//namespace Exil