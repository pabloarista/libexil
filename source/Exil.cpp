#include <Exil.h>
#include <ExilJsonFormatter.h>

namespace Exil
{
	Exception::Exception(const String& message)
		: std::runtime_error(message)
	{}

	ConversionException::ConversionException()
		: Exception("Could not convert between types")
	{}

};//namespace Exil
