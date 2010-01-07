#ifndef ExilObject_h__
#define ExilObject_h__

#include <Exil.h>
#include <ExilBuffer.h>
#include <ExilReader.h>
#include <ExilWriter.h>

namespace Exil
{
	class Object
	{
	private:
		// not implemented
		Object(const Object&);

	public:
		Object(Reader* reader);

		Object(Writer* writer);

		inline SizeT getNumItems()
		{
			return mNumItems;
		}

		static inline SizeT Size(SizeT len)
		{
			return sizeof(Object);
		}

		template <typename T>
		Object& set(const char* str, T& value)
		{
			++mNumItems;
			Writer* writer = static_cast<Writer*>(mSystem);
			ConvertType<const char*>::To(str, *writer);
			ConvertType<T>::To(value, *writer);
			return *this;
		}

		template <typename T>
		Object& get(const char* str, T& value)
		{
			Reader* reader = static_cast<Reader*>(mSystem);

			std::string s;
			ConvertType<std::string>::From(s, *reader);
			if(strcmp(str, s.c_str()) != 0)
				throw "Incorrect key name";

			ConvertType<T>::From(value, *reader);
			return *this;
		}

	private:
		InternalType mType;
		SizeT mNumItems;
		void* mSystem;
	};

};//namespace Exil

#endif // ExilObject_h__