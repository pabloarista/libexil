#ifndef ExilDataStream_h__
#define ExilDataStream_h__

namespace Exil
{
	struct DataStream
	{
		DataStream(std::ostream& stream)
			: mStream(stream)
		{
		}

		virtual DataStream& operator<<(Value* value) = 0;

		std::ostream& mStream;
	};

};
#endif // ExilDataStream_h__
