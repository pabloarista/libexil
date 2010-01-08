#include "ExilChunk.h"

namespace Exil
{
	Chunk::Chunk( char* buff, size_t size )
	{
		mSize = size;
		buffer = new char[mSize];
		ptr = buffer;
		readPtr = buffer;
		end = buffer + mSize;
		memcpy(buffer, buff, mSize);
	}

	Chunk::Chunk( size_t size )
	{
		mSize = size;
		buffer = new char[mSize];
		ptr = buffer;
		readPtr = buffer;
		end = buffer + mSize;
		memset(buffer, 0, mSize);
	}

	Chunk::Chunk( Chunk& other )
	{
		mSize = other.mSize;
		buffer = new char[mSize];
		memcpy(buffer, other.buffer, mSize);
		ptr = buffer;
		end = buffer + mSize;
		readPtr = buffer;
	}

	Chunk::~Chunk()
	{
		memset(buffer, 0, mSize);
		delete buffer;
		ptr = readPtr = 0;
		end = 0;
	}
}
