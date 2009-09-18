#ifndef ExilJsonParser_h__
#define ExilJsonParser_h__

#include <Exil.h>

namespace Exil
{
	class JsonParser
	{
		std::istream& mStream;

	public:
		JsonParser(std::istream& stream);

		String parseString();

		float parseNumber(char ch);

		Pair parsePair(char ch);

		Object* parseObject();

		Array* parseArray();

		Value* parseValue(char ch = 0);

		inline bool isWhiteSpace(char ch)
		{
			return ch == '\t' || ch == ' ' || ch == '\n' || ch == '\r';
		}

		inline bool isNumber(char ch)
		{
			return ch > 47 && ch < 58;
		}

		inline float toNumber(char ch)
		{
			return static_cast<float>(ch - 48);
		}
	};
};//namespace Exil

#endif // ExilJsonParser_h__