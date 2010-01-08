#include "ExilBuffer.h"

namespace Exil
{
	Buffer::Buffer( Buffer& other )
	{
		mChunkSize = other.mChunkSize;
		for(ChunkList::iterator iter = other.mChunks.begin();
			iter != other.mChunks.end();
			++iter)
		{
			mChunks.push_back(new Chunk(**iter));
		}
		mReadChunk = mChunks.begin();
	}

	Buffer::Buffer( char* buff, size_t size )
	{
		mChunkSize = size;
		mChunks.push_back(new Chunk(buff, mChunkSize));
		mReadChunk = mChunks.begin();
	}

	Buffer::Buffer( SizeT size /*= DefaultChunkSize*/ )
	{
		mChunkSize = size;
		addChunk();
		mReadChunk = mChunks.begin();
	}

	Buffer::~Buffer()
	{
		while(mChunks.size() > 0)
		{
			Chunk* chunk = mChunks.back();
			delete chunk;
			mChunks.pop_back();
		}
	}

	RawBuffer* Buffer::toString()
	{
		size_t totalSize = 0;

		for(ChunkList::iterator iter = mChunks.begin();
			iter != mChunks.end();
			++iter)
		{
			Chunk* chunk = *iter;
			size_t size = chunk->ptr - chunk->buffer;
			totalSize += size;
		}

		RawBuffer* buff = new RawBuffer;
		buff->size = totalSize;
		buff->buffer = new char[totalSize];
		char* dest = buff->buffer;

		for(ChunkList::iterator iter = mChunks.begin();
			iter != mChunks.end();
			++iter)
		{
			Chunk* chunk = *iter;
			size_t size = chunk->ptr - chunk->buffer;

			memcpy(dest, chunk->buffer, size);
			dest += size;
		}

		return buff;
	}

	Chunk& Buffer::getChunk()
	{
		return *(mChunks.back());
	}

	Chunk& Buffer::addChunk()
	{
		mChunks.push_back(new Chunk(mChunkSize));
		return getChunk();
	}

	char* Buffer::allocate( SizeT size )
	{
		if(size > mChunkSize)
			return NULL;

		Chunk& chunk = getChunk();

		if(chunk.ptr + size + sizeof(SizeT)> chunk.end)
		{
			addChunk();
			return allocate(size);
		}

		// store the size of the chunk in the array, and leave room for the data after
		SizeT* sizePtr = reinterpret_cast<SizeT*>(chunk.ptr);
		*sizePtr = size;
		char* ptr = chunk.ptr + sizeof(SizeT);
		chunk.ptr += size + sizeof(SizeT);

		return ptr;
	}

	char* Buffer::reallocate( SizeT size )
	{
		if(size> mChunkSize)
			return NULL;

		Chunk& chunk = *(*mReadChunk);

		if(*chunk.readPtr == 0 || chunk.readPtr == chunk.end)
		{
			mReadChunk++;
			if(mReadChunk == mChunks.end())
				throw "Invalid allocation. Out of memory.";
			return reallocate(size);
		}

		SizeT* sizePtr = reinterpret_cast<SizeT*>(chunk.readPtr);
		char* ptr = chunk.readPtr + sizeof(SizeT);
		chunk.readPtr += *sizePtr + sizeof(SizeT);

		return ptr;
	}

	size_t Buffer::getSize() const
	{
		return mChunks.size() * mChunkSize;
	}
}
