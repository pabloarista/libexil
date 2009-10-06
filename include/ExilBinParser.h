#ifndef ExilBinParser_h__
#define ExilBinParser_h__

#include <Exil.h>

namespace Exil
{
	class BinParser
	{
		std::istream& mStream;

	public:
		BinParser(std::istream& stream);

		Value* parseValue();

		Value* parseObject();
		Value* parseArray();
		Value* parseNumber();
		String parseString();
		Value* parseBool();
		int parseInt();

	};//class BinParser

};//namespace Exil

#endif // ExilBinParser_h__