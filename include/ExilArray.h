#ifndef ExilArray_h__
#define ExilArray_h__

#include <Exil.h>
#include <ExilValue.h>
#include <ExilWriter.h>
#include <ExilReader.h>

namespace Exil
{
	class Array
	{
	public:
		Array(Reader* reader)
		{
			if(mType != Types::Array)
				throw "Not an Array";
			mSystem = reader;
		}

		Array(Writer* writer)
			: mType(Types::Array), mNumItems(0)
		{
			mSystem = writer;
		}

		template <typename T>
		Array& add(T& value)
		{
			Writer* writer = static_cast<Writer*>(mSystem);
			++mNumItems;
			ConvertType<T>::To(value, *writer);
			return *this;
		}

		template <typename T>
		void set(std::list<T>& list)
		{
			for(std::list<T>::iterator iter = list.begin();
				iter != list.end();
				++iter)
			{
				add(*iter);
			}
		}

		template <typename T>
		Array& get(std::list<T>& list)
		{
			Reader* reader = static_cast<Reader*>(mSystem);

			for(SizeT i = 0; i < mNumItems; ++i)
			{
				T value;
				ConvertType<T>::From(value, *reader);
				list.push_back(value);
			}
			return *this;
		}

		SizeT getValue()
		{
			return mNumItems;
		}

		static SizeT Size(SizeT len)
		{
			return sizeof(Array);
		}

	private:
		InternalType mType;
		SizeT mNumItems;
		void* mSystem;
	};


#pragma region Conversion Methods
	template <typename T>
	struct ConvertType<std::list<T> >
	{
		static void To(std::list<T>& list, Writer& writer)
		{
			writer.CreateArray()
				.set(list);
		}

		static void From(std::list<T>& list, Reader& reader)
		{
			reader.CreateArray()
				.get(list);
		}
	};

#pragma endregion Conversion Methods

};
#endif // ExilArray_h__
