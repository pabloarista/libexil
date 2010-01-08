#ifndef ExilData_h__
#define ExilData_h__

#include "Exil.h"

namespace Exil
{
	namespace Data
	{

#pragma pack(push,1)

		class Object
		{
		private:
			Object(const Object&);
		public:
			Object(Reader* reader);

			Object(Writer* writer);

			SizeT getNumItems();

			static SizeT Size(SizeT len);

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

		class Array
		{
		public:
			Array(Reader* reader);

			Array(Writer* writer);

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

			SizeT getValue();

			static SizeT Size(SizeT len);

		private:
			InternalType mType;
			SizeT mNumItems;
			void* mSystem;
		};

		class String
		{
		public:
			String();

			String(const char* str, SizeT len);

			String(const std::string& str);

			const char* getValue();

			SizeT getLength();

			static SizeT Size(SizeT len);

		private:
			InternalType mType;
		};

		class Float
		{
		public:
			Float();
			Float(float f);

			inline float getValue()
			{
				return mValue;
			}

		private:
			InternalType mType;
			float mValue;
		};

		class Integer
		{
		public:
			Integer();

			Integer(int i);

			inline int getValue()
			{
				return mValue;
			}

		private:
			InternalType mType;
			int mValue;
		};

		class Boolean
		{
		public:
			Boolean();

			Boolean(bool b);

			inline bool getValue()
			{
				return mValue;
			}

		private:
			InternalType mType;
			bool mValue;
		};

#pragma pack(pop)

	};//namespace Data

};//namespace Exil

#endif // ExilData_h__
