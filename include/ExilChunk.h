#ifndef ExilChunk_h__
#define ExilChunk_h__

#include <Exil.h>

namespace Exil
{
	struct Chunk
	{
		Chunk(char* buff, size_t size)
		{
			mSize = size;
			buffer = new char[mSize];
			ptr = buffer;
			readPtr = buffer;
			end = buffer + mSize;
			memcpy(buffer, buff, mSize);
		}
	
		Chunk(size_t size)
		{
			mSize = size;
			buffer = new char[mSize];
			ptr = buffer;
			readPtr = buffer;
			end = buffer + mSize;
			memset(buffer, 0, mSize);
		}
	
		Chunk(Chunk& other)
		{
			mSize = other.mSize;
			buffer = new char[mSize];
			memcpy(buffer, other.buffer, mSize);
			ptr = buffer;
			end = buffer + mSize;
			readPtr = buffer;
		}
	
		~Chunk()
		{
			memset(buffer, 0, mSize);
			delete buffer;
			ptr = readPtr = 0;
			end = 0;
		}
	
		char* buffer;
		char* ptr;
		char* readPtr;
		const char* end;
		size_t mSize;
	};

};//namespace Exil

#endif // ExilChunk_h__
