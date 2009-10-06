#include <ExilDataStream.h>

namespace Exil
{
	NullIStream NullIn;
	NullOStream NullOut;
	DSOutType dsout(std::cout, Exil::NullIn);
}