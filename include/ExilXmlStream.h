#ifndef ExilXmlStream_h__
#define ExilXmlStream_h__

#include <Exil.h>
#include <ExilDataStream.h>

namespace Exil
{
	struct XmlStream : public DataStream
	{
		XmlStream(std::ostream& stream)
			: DataStream(stream)
		{
		}

		virtual XmlStream& operator<<(Value* value)
		{


			return *this;
		}
	};

};
#endif // ExilXmlStream_h__