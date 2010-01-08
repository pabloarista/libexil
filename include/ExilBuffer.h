#ifndef ExilBuffer_h__
#define ExilBuffer_h__

#include <Exil.h>

namespace Exil
{
	struct RawBuffer
	{
		size_t size;
		char* buffer;
	};

	class Buffer
	{
	public:
		const static SizeT DefaultChunkSize = 1024;

		typedef std::list<Chunk*> ChunkList;

	public:
		Buffer(Buffer& other);

		Buffer(char* buff, size_t size);

		Buffer(SizeT size = DefaultChunkSize);

		~Buffer();

		RawBuffer* toString();

		Chunk& getChunk();

		Chunk& addChunk();

		char* allocate(SizeT size);

		char* reallocate(SizeT size);

		size_t getSize() const;

	private:
		size_t mChunkSize;
		ChunkList mChunks;
		ChunkList::iterator mReadChunk;
	};

}//namespace Exil

#endif // ExilBuffer_h__
