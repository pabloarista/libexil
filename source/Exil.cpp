#include <Exil.h>
#include <ExilJsonFormatter.h>

namespace Exil
{
	Exception::Exception(const std::string& message)
		: std::runtime_error(message)
	{}

	ConversionException::ConversionException()
		: Exception("Could not convert between types")
	{}

	SizeT GetSize(const char* ptr)
	{
		return *reinterpret_cast<const SizeT*>(ptr - sizeof(SizeT));
	}

	Type GetType(const char* ptr)
	{
		InternalType it = *reinterpret_cast<const InternalType*>(ptr);
		return static_cast<Type>(it);
	}

};//namespace Exil
