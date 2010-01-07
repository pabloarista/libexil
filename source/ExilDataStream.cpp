#include <ExilDataStream.h>
#ifdef UPGRADE_COMPLETE
namespace Exil
{
	NullIStream NullIn;
	NullOStream NullOut;
	DSOutType dsout(std::cout, Exil::NullIn);
}
#endif