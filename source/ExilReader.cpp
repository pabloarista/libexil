#include "ExilReader.h"

#include "ExilData.h"
#include "ExilBuffer.h"

namespace Exil
{
	Reader::Reader( Buffer& buffer ) : mBuffer(buffer)
	{
	}
	
	template <>
	void Reader::read(int& value)
	{
		Data::Integer* i = new(mBuffer.reallocate(sizeof(Data::Integer))) Data::Integer();
		value = i->getValue();
	}
	
	template <>
	void Reader::read(float& value)
	{
		Data::Float* f = new(mBuffer.reallocate(sizeof(Data::Float))) Data::Float();
		value = f->getValue();
	}
	
	template <>
	void Reader::read(bool& value)
	{
		Data::Boolean* b = new(mBuffer.reallocate(sizeof(Data::Boolean))) Data::Boolean();
		value = b->getValue();
	}
	
	template <>
	void Reader::read(std::string& value)
	{
		char* ptr = mBuffer.reallocate(sizeof(Data::String));
		Data::String* s = new(ptr) Data::String();
		const char* c = s->getValue();
		SizeT len = s->getLength();
		value = std::string(s->getValue(), s->getLength());
	}
	
	Data::Object& Reader::CreateObject()
	{
		Data::Object* obj = new(mBuffer.reallocate(Data::Object::Size(0))) Data::Object(this);
		return *obj;
	}
	
	Data::Array& Reader::CreateArray()
	{
		Data::Array* arr = new(mBuffer.reallocate(Data::Array::Size(0))) Data::Array(this);
		return *arr;
	}

};//namespace Exil


