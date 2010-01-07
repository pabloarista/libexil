#ifndef ExilXmlParser_h__
#define ExilXmlParser_h__

#include <Exil.h>
#ifdef UPGRADE_COMPLETE

namespace Exil
{
	class XmlParser
	{
	public:
		typedef std::pair<String, String> StringPair;

	public:
		XmlParser(std::istream& stream);

		Value* parseValue();

		Pair parseValuePair();

		StringPair parseTagPair(char& ch);

		void getTagName(String& tagName, char& ch);

		Value* toNumber(const String& str);

		Value* toBool(const String& str);

		Object* parseObject();

		Array* parseArray();

		inline float toNumber(char ch)
		{
			return static_cast<float>(ch - 48);
		}

		std::istream& mStream;
	};

};//namespace Exil
#endif
#endif // ExilXmlParser_h__