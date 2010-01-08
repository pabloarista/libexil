#ifndef ExilWriter_h__
#define ExilWriter_h__

#include "Exil.h"

namespace Exil
{
	class Writer
	{
	public:
		Writer(Buffer& buffer);

		Data::Object& CreateObject();

		Data::Array& CreateArray();

		template <typename T>
		void write(const T& value);

		template <typename T>
		void write(const T* value);

		size_t getSize() const;

	private:
		Buffer& mBuffer;
	};

};//namespace Exil

#endif // ExilWriter_h__
