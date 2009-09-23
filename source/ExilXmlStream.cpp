#include <ExilXmlStream.h>
#include <ExilValue.h>
#include <ExilObject.h>
#include <ExilArray.h>

namespace Exil
{
	XmlStream::XmlStream( std::iostream& stream )
		: mStream(stream)
	{

	}

	XmlStream& XmlStream::operator<<( Value* value )
	{
		_writeValue(value);
		delete value;
		return *this;
	}

	void XmlStream::_writeObject( Object* object, bool writeName /*= true*/, bool leadTab /*= true*/ )
	{
		if(writeName)
			mStream << (leadTab?mTabs:BLANK_STRING) << "<Object>" << std::endl;
		_increaseTab();

		for(ValueMap::iterator iter = object->values.begin();
			iter != object->values.end();
			++iter)
		{
			_writePair(iter->first, iter->second);
		}

		_decreaseTab();
		mStream << mTabs << "</Object>" << std::endl;
	}

	void XmlStream::_writeArray( Array* list, bool writeName /*= true*/, bool leadTab /*= true*/ )
	{
		if(writeName)
			mStream << (leadTab?mTabs:BLANK_STRING) << "<Array>" << std::endl;
		_increaseTab();

		for(ValueList::iterator iter = list->values.begin();
			iter != list->values.end();
			++iter)
		{
			_writeValue(*iter, true);
		}

		_decreaseTab();
		mStream << mTabs << "</Array>" << std::endl;
	}

	void XmlStream::_writePair( const String& name, Value* value )
	{
		if(value->type() == Value::Types::Array || value->type() == Value::Types::Object)
		{
			mStream << mTabs << "<" << Convert::toString(value->type()) <<" name=\"" << name << "\">" << std::endl;
			_writeValue(value, false, false);
		}
		else if(value->type() == Value::Types::Bool)
		{
			mStream << mTabs << "<Bool " << name << "=";
			_writeValue(value, true, false);
			mStream << " />" << std::endl;
		}
		else
		{
			mStream << mTabs << "<" << Convert::toString(value->type()) << " " << name << "=";
			_writeValue(value, true, false);
			mStream << " />" << std::endl;
		}
	}

	void XmlStream::_writeValue( Value* value, bool writeName /*= true*/, bool leadTab /*= true*/ )
	{
		switch(value->type())
		{
		case Value::Types::Array:
			_writeArray(value->toArray(), writeName, leadTab);
			break;
		case Value::Types::Object:
			_writeObject(value->toObject(), writeName, leadTab);
			break;
		case Value::Types::String:
			mStream << (leadTab?mTabs:BLANK_STRING) << "\"" << value->toString() << "\"";
			break;
		case Value::Types::Number:
			mStream << (leadTab?mTabs:BLANK_STRING) << "\"" << value->toNumber<float>() << "\"";
			break;
		case Value::Types::Bool:
			if(value->toBool())
				mStream << (leadTab?mTabs:BLANK_STRING) << "\"true\"";
			else
				mStream << (leadTab?mTabs:BLANK_STRING) << "\"false\"";
			break;
		case Value::Types::Null:
			mStream << (leadTab?mTabs:BLANK_STRING) << "\"null\"";
			break;
		}
	}

	void XmlStream::_increaseTab()
	{
		mTabs += '\t';
	}

	void XmlStream::_decreaseTab()
	{
		if(mTabs.empty())
			return;
		mTabs.erase(mTabs.size() - 1, 1);
	}
};//namespace Exil
