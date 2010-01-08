#ifndef ExilChunk_h__
#define ExilChunk_h__

#include <Exil.h>

namespace Exil
{
	struct Chunk
	{
		Chunk(char* buff, size_t size);
	
		Chunk(size_t size);
	
		Chunk(Chunk& other);
	
		~Chunk();
	
		char* buffer;
		char* ptr;
		char* readPtr;
		const char* end;
		size_t mSize;
	};

};//namespace Exil

#endif // ExilChunk_h__
