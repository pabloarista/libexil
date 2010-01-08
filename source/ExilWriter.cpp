#include "ExilWriter.h"

#include "ExilData.h"
#include "ExilBuffer.h"

namespace Exil
{
	Writer::Writer( Buffer& buffer ) : mBuffer(buffer)
	{
	}

	size_t Writer::getSize() const
	{
		return mBuffer.getSize();
	}

	Data::Object& Writer::CreateObject()
	{
		Data::Object* obj = new(mBuffer.allocate(Data::Object::Size(0))) Data::Object(this);
		return *obj;
	}

	Data::Array& Writer::CreateArray()
	{
		Data::Array* arr = new(mBuffer.allocate(Data::Array::Size(0))) Data::Array(this);
		return *arr;
	}

	template <>
	void Writer::write(const int& value)
	{
		new(mBuffer.allocate(sizeof(Data::Integer))) Data::Integer(value);
	}
	
	template <>
	void Writer::write(const float& value)
	{
		new(mBuffer.allocate(sizeof(Data::Float))) Data::Float(value);
	}
	
	template <>
	void Writer::write(const bool& value)
	{
		new(mBuffer.allocate(sizeof(Data::Boolean))) Data::Boolean(value);
	}
	
	template <>
	void Writer::write(const std::string& value)
	{
		new(mBuffer.allocate(Data::String::Size(value.size()))) Data::String(value);
	}
	
	template <>
	void Writer::write(const char* value)
	{
		SizeT length = strlen(value);
		new(mBuffer.allocate(Data::String::Size(length))) Data::String(value, length);
	}
	
};//namespace Exil
