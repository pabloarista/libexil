#ifndef ExilReader_h__
#define ExilReader_h__

#include "Exil.h"

namespace Exil
{
	class Reader
	{
	public:
		Reader(Buffer& buffer);
	
		Data::Object& CreateObject();

		Data::Array& CreateArray();

		template <typename T>
		void read(T& value);
	
	private:
		Buffer& mBuffer;
	};

};//namespace Exil

#endif // ExilReader_h__
