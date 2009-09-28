#include <ExilBinStream.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	BinStream::BinStream( std::iostream& stream )
		: mStream(stream), mParser(stream)
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
		_writeType(Value::Types::Object);
		_writeInt(object->values.size());
		for(ValueMap::iterator iter = object->values.begin();
			iter != object->values.end();)
		{
			ValueMap::iterator current = iter++;
			_writePair(current->first, current->second);
		}
	}

	void BinStream::_writeArray( Array* list )
	{
		_writeType(Value::Types::Array);
		_writeInt(list->values.size());
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
			_writeType(Value::Types::String);
			_writeString(value->toString());
			break;
		case Value::Types::Number:
			_writeType(Value::Types::Number);
			_writeFloat(value->toNumber<float>());
			break;
		case Value::Types::Bool:
			_writeType(Value::Types::Bool);
			_writeBool(value->toBool());
			break;
		case Value::Types::Null:
			_writeType(Value::Types::Null);
			break;
		}
	}


	void BinStream::_writeString( const String& str )
	{
		_writeInt(str.size());
		mStream.write(str.c_str(), str.length() * sizeof(char));
	}

	void BinStream::_writeInt( int number )
	{
		mStream.write(reinterpret_cast<char*>(&number), sizeof(int));
	}

	void BinStream::_writeBool( bool b )
	{
		mStream.write(reinterpret_cast<char*>(&b), sizeof(char));
	}

	void BinStream::_writeFloat( float number )
	{
		mStream.write(reinterpret_cast<char*>(&number), sizeof(float));
	}

	void BinStream::_writeType( Value::Type type )
	{
		mStream.write(reinterpret_cast<char*>(&type), sizeof(char));
	}
};//namespace Exil