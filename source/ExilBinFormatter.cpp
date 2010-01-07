#include <ExilBinFormatter.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

#ifdef UPGRADE_COMPLETE

namespace Exil
{
	BinFormatter::BinFormatter( std::ostream& stream )
		: Formatter(stream)
	{

	}

	BinFormatter& BinFormatter::operator<<( Value* value )
	{
		_writeValue(value);
		delete value;
		return *this;
	}

	void BinFormatter::_writeObject( Object* object )
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

	void BinFormatter::_writeArray( Array* list )
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

	void BinFormatter::_writePair( const String& name, Value* value )
	{
		_writeString(name);
		_writeValue(value);
	}

	void BinFormatter::_writeValue( Value* value )
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


	void BinFormatter::_writeString( const String& str )
	{
		_writeInt(str.size());
		mStream.write(str.c_str(), str.length() * sizeof(char));
	}

	void BinFormatter::_writeInt( int number )
	{
		mStream.write(reinterpret_cast<char*>(&number), sizeof(int));
	}

	void BinFormatter::_writeBool( bool b )
	{
		mStream.write(reinterpret_cast<char*>(&b), sizeof(char));
	}

	void BinFormatter::_writeFloat( float number )
	{
		mStream.write(reinterpret_cast<char*>(&number), sizeof(float));
	}

	void BinFormatter::_writeType( Value::Type type )
	{
		mStream.write(reinterpret_cast<char*>(&type), sizeof(char));
	}
};//namespace Exil
#endif
