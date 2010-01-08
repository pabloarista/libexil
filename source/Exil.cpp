#include <Exil.h>

namespace Exil
{

	Exil::SizeT GetSize( const char* ptr )
	{
		return *reinterpret_cast<const SizeT*>(ptr - sizeof(SizeT));
	}

	Exil::Type GetType( const char* ptr )
	{
		InternalType it = *reinterpret_cast<const InternalType*>(ptr);
		return static_cast<Type>(it);
	}

	Exception::Exception(const String& message)
		: std::runtime_error(message)
	{}

	ConversionException::ConversionException()
		: Exception("Could not convert between types")
	{}

};//namespace Exil
