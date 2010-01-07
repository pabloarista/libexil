#include <ExilObject.h>

namespace Exil
{
	Object::Object(Reader* reader)
	{
		if(mType != Types::Object)
			throw "Not an Object";

		mSystem = reader;
	}

	Object::Object(Writer* writer)
	{
		mType = Types::Object;
		mNumItems = 0;
		mSystem = writer;
	}

};//namespace Exil
