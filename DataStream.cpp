// disable exception handler warning
#pragma warning(disable:4530)

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

typedef std::string String;
const String BLANK_STRING;
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;


class DataStream
{
public:
	class Block;
	class List;
	
	DataStream() : mBlockCount(0), mFreshBlock(true)
	{}

	virtual Block createBlock(const String& name);
	virtual List createList(const String& name, uint32_t count);
	
	virtual String getString() const = 0;
	
protected:
	virtual void _startBlock(const String& name) = 0;
	virtual void _endBlock() = 0;
	
	virtual void _startList(const String& name, uint32_t count) = 0;
	virtual void _endList() = 0;

	inline void write(const String& name, bool val) {writeBool(name, val);}
	virtual void writeBool(const String& name, bool val) = 0;
	
	inline void write(const String& name, int8_t val) {writeInt8(name, val);}
	virtual void writeInt8 (const String& name, int8_t val) = 0;
	
	inline void write(const String& name, int16_t val) {writeInt16(name, val);}
	virtual void writeInt16(const String& name, int16_t val) = 0;
	
	inline void write(const String& name, int32_t val) {writeInt32(name, val);}
	virtual void writeInt32(const String& name, int32_t val) = 0;
	
	inline void write(const String& name, uint8_t val) {writeUInt8(name, val);}
	virtual void writeUInt8 (const String& name, uint8_t val) = 0;
	
	inline void write(const String& name, uint16_t val) {writeUInt16(name, val);}
	virtual void writeUInt16(const String& name, uint16_t val) = 0;
	
	inline void write(const String& name, uint32_t val) {writeUInt32(name, val);}
	virtual void writeUInt32(const String& name, uint32_t val) = 0;
	
	inline void write(const String& name, float val) {writeFloat(name, val);}
	virtual void writeFloat(const String& name, float val) = 0;
	
	inline void write(const String& name, const String& val) {writeString(name, val);}
	virtual void writeString(const String& name, const String& val) = 0;

	inline void _write(bool val) {_writeBool(val);}
	virtual void _writeBool(bool val) = 0;
	inline void _write(int8_t val) {_writeInt8(val);}
	virtual void _writeInt8 (int8_t val) = 0;
	inline void _write(int16_t val) {_writeInt16(val);}
	virtual void _writeInt16(int16_t val) = 0;
	inline void _write(int32_t val) {_writeInt32(val);}
	virtual void _writeInt32(int32_t val) = 0;
	inline void _write(uint8_t val) {_writeUInt8(val);}
	virtual void _writeUInt8 (uint8_t val) = 0;
	inline void _write(uint16_t val) {_writeUInt16(val);}
	virtual void _writeUInt16(uint16_t val) = 0;
	inline void _write(uint32_t val) {_writeUInt32(val);}
	virtual void _writeUInt32(uint32_t val) = 0;
	inline void _write(float val) {_writeFloat(val);}
	virtual void _writeFloat(float val) = 0;
	inline void _write(const String& val) {_writeString(val);}
	virtual void _writeString(const String& val) = 0;

	
	virtual void readBool(bool& val) = 0;
	virtual void readInt8 (int8_t& val) = 0;
	virtual void readInt16(int16_t& val) = 0;
	virtual void readInt32(int32_t& val) = 0;
	virtual void readUInt8 (uint8_t& val) = 0;
	virtual void readUInt16(uint16_t& val) = 0;
	virtual void readUInt32(uint32_t& val) = 0;
	virtual void readFloat(float& val) = 0;
	virtual void readString(String& val) = 0;
	
	uint32_t mBlockCount;
	bool mFreshBlock;
	
	friend class DataStream::Block;
	friend class DataStream::List;
};

class DataStream::Block
{
public:
	Block(const String& name, DataStream& ds)
		: mName(name), mDS(ds)
	{
		mDS._startBlock(name);
		++(mDS.mBlockCount);
		mDS.mFreshBlock = true;
	}
	
	virtual ~Block()
	{
		--(mDS.mBlockCount);
		mDS._endBlock();
	}
	
	inline void write(const String& name, bool val) {mDS.writeBool(name, val);}
	
	inline void write(const String& name, int8_t val) {mDS.writeInt8(name, val);}
	
	inline void write(const String& name, int16_t val) {mDS.writeInt16(name, val);}
	
	inline void write(const String& name, int32_t val) {mDS.writeInt32(name, val);}
	
	inline void write(const String& name, uint8_t val) {mDS.writeUInt8(name, val);}
	
	inline void write(const String& name, uint16_t val) {mDS.writeUInt16(name, val);}
	
	inline void write(const String& name, uint32_t val) {mDS.writeUInt32(name, val);}
	
	inline void write(const String& name, float val) {mDS.writeFloat(name, val);}
	
	inline void write(const String& name, const String& val) {mDS.writeString(name, val);}
	
	String mName;
	DataStream& mDS;
};

class DataStream::List
{
public:
	List(const String& name, DataStream& ds, uint32_t count)
		: mName(name), mDS(ds)
	{
		mDS._startList(name, count);
		++(mDS.mBlockCount);
		mDS.mFreshBlock = true;
	}
	
	virtual ~List()
	{
		--(mDS.mBlockCount);
		mDS._endList();
	}
	
	inline void write(bool val) {writeBool(val);}
	virtual void writeBool(bool val) {mDS._writeBool(val);}
	
	inline void write(int8_t val) {writeInt8(val);}
	virtual void writeInt8 (int8_t val) {mDS._writeInt8(val);}
	
	inline void write(int16_t val) {writeInt16(val);}
	virtual void writeInt16(int16_t val) {mDS._writeInt16(val);}
	
	inline void write(int32_t val) {writeInt32(val);}
	virtual void writeInt32(int32_t val) {mDS._writeInt32(val);}
	
	inline void write(uint8_t val) {writeUInt8(val);}
	virtual void writeUInt8 (uint8_t val) {mDS._writeUInt8(val);}
	
	inline void write(uint16_t val) {writeUInt16(val);}
	virtual void writeUInt16(uint16_t val) {mDS._writeUInt16(val);}
	
	inline void write(uint32_t val) {writeUInt32(val);}
	virtual void writeUInt32(uint32_t val) {mDS._writeUInt32(val);}
	
	inline void write(float val) {writeFloat(val);}
	virtual void writeFloat(float val) {mDS._writeFloat(val);}
	
	inline void write(const String& val) {writeString(val);}
	virtual void writeString(const String& val) {mDS._writeString(val);}
	
	
	String mName;
	DataStream& mDS;
};

DataStream::Block DataStream::createBlock(const String& name)
{
	return Block(name, *this);
}
	
DataStream::List DataStream::createList(const String& name, uint32_t count)
{
	return List(name, *this, count);
}
	
	
class XmlStream : public DataStream
{
public:
	XmlStream(bool pretty = true)
		: mPretty(pretty)
	{
	}
	
	virtual void _startBlock(const String& name)
	{
		mSS << (mPretty ? String(mBlockCount , '\t') : BLANK_STRING) 
			<< "<block name=\"" << name << "\">";
		if(mPretty)
			mSS << '\n';
	}
	
	virtual void _endBlock()
	{
		mSS << (mPretty ? String(mBlockCount , '\t') : BLANK_STRING) 
			<< "</block>" << (mPretty ? '\n' : ' ');
		if(mPretty)
			mSS << '\n';
	}
	
	virtual void _startList(const String& name, uint32_t count)
	{
		mSS << (mPretty ? String(mBlockCount , '\t') : BLANK_STRING) 
			<< "<list name=\"" << name << "\" count=\"" << count << "\">";
		if(mPretty)
			mSS << '\n';
	}
	
	virtual void _endList()
	{
		mSS << (mPretty ? String(mBlockCount , '\t') : BLANK_STRING) 
			<< "</list>" << (mPretty ? '\n' : ' ');
		if(mPretty)
			mSS << '\n';
	}
	
	template <typename T>
	inline void _writeValue(const String& name, const String& tagName, T val)
	{
		// write out pretty formatting
		if(mPretty)
			mSS << String(mBlockCount, '\t');
			
		// write out tag name
		mSS << "<" << tagName << " ";
		
		// write out name if available
		if(!name.empty())
			mSS << "name=\"" << name << "\" ";
			
		// write out value and close
		mSS << "value=\"" << val << "\" />";
		
		// write out more pretty formatting
		if(mPretty)
			mSS << '\n';
	}
	
	virtual void _writeBool(bool val)
	{
		_writeValue(BLANK_STRING, "bool", (val ? "true" : "false"));
	}
	virtual void writeBool(const String& name, bool val)
	{
		_writeValue(name, "bool", (val ? "true" : "false"));
	}
	
	virtual void _writeInt8 (int8_t val)
	{
		_writeValue(BLANK_STRING, "int8", static_cast<int>(val));
	}
	virtual void writeInt8 (const String& name, int8_t val)
	{
		_writeValue(name, "int8", static_cast<int>(val));
	}

	virtual void _writeInt16(int16_t val)
	{
		_writeValue(BLANK_STRING, "int16", val);
	}
	virtual void writeInt16(const String& name, int16_t val)
	{
		_writeValue(name, "int16", val);
	}

	virtual void _writeInt32(int32_t val)
	{
		_writeValue(BLANK_STRING, "int32", val);
	}
	virtual void writeInt32(const String& name, int32_t val)
	{
		_writeValue(name, "int32", val);
	}

	virtual void _writeUInt8 (uint8_t val)
	{
		_writeValue(BLANK_STRING, "uint8", static_cast<unsigned int>(val));
	}
	virtual void writeUInt8 (const String& name, uint8_t val)
	{
		_writeValue(name, "uint8", static_cast<unsigned int>(val));
	}

	virtual void _writeUInt16(uint16_t val)
	{
		_writeValue(BLANK_STRING, "uint16", val);
	}
	virtual void writeUInt16(const String& name, uint16_t val)
	{
		_writeValue(name, "uint16", val);
	}

	virtual void _writeUInt32(uint32_t val)
	{
		_writeValue(BLANK_STRING, "uint32", val);
	}
	virtual void writeUInt32(const String& name, uint32_t val)
	{
		_writeValue(name, "uint32", val);
	}

	virtual void _writeFloat(float val)
	{
		_writeValue(BLANK_STRING, "float", val);
	}
	virtual void writeFloat(const String& name, float val)
	{
		_writeValue(name, "float", val);
	}

	virtual void _writeString(const String& val)
	{
		_writeValue(BLANK_STRING, "string", val);
	}
	virtual void writeString(const String& name, const String& val)
	{
		_writeValue(name, "string", val);
	}

	
	virtual void readBool(bool& val)
	{
	}

	virtual void readInt8 (int8_t& val)
	{
	}

	virtual void readInt16(int16_t& val)
	{
	}

	virtual void readInt32(int32_t& val)
	{
	}

	virtual void readUInt8 (uint8_t& val)
	{
	}

	virtual void readUInt16(uint16_t& val)
	{
	}

	virtual void readUInt32(uint32_t& val)
	{
	}

	virtual void readFloat(float& val)
	{
	}

	virtual void readString(String& val)
	{
	}
	
	String getString() const
	{
		return mSS.str();
	}
	
private:
	std::stringstream mSS;
	bool mPretty;
	
};

class JSONStream : public DataStream
{
public:
	JSONStream(bool pretty = true)
		: mPretty(pretty)
	{
	}
	
	virtual void _startBlock(const String& name)
	{
		if(!mFreshBlock)
			mSS << ",";
		if(mPretty)
			mSS << '\n' << String(mBlockCount , '\t');
		mSS << "\"" << name << "\" : {";
	}
	
	virtual void _endBlock()
	{
		if(mPretty)
			mSS << '\n' << String(mBlockCount, '\t');
		mSS << "}";
	}
	
	virtual void _startList(const String& name, uint32_t count)
	{
		if(!mFreshBlock)
			mSS << ",";
		if(mPretty)
			mSS << '\n' << String(mBlockCount , '\t');
		mSS << "\"" << name << "\" : [";
	}
	
	virtual void _endList()
	{
		if(mPretty)
			mSS << '\n' << String(mBlockCount, '\t');
		mSS << "]";
	}
	
	template <typename T>
	inline void _writeValue(const String& name, const String& tagName, T val)
	{
		if(!mFreshBlock)
			mSS << ",";
		// write out pretty formatting
		if(mPretty)
			mSS << '\n' << String(mBlockCount, '\t');
			
		// write out name if available
		if(!name.empty())
			mSS << "\"" << name << "\" : ";
			
		// write out value and close
		mSS << val;
		
		mFreshBlock = false;
	}
	
	virtual void _writeBool(bool val)
	{
		_writeValue(BLANK_STRING, "bool", (val ? "true" : "false"));
	}
	virtual void writeBool(const String& name, bool val)
	{
		_writeValue(name, "bool", (val ? "true" : "false"));
	}
	
	virtual void _writeInt8 (int8_t val)
	{
		_writeValue(BLANK_STRING, "int8", static_cast<int>(val));
	}
	virtual void writeInt8 (const String& name, int8_t val)
	{
		_writeValue(name, "int8", static_cast<int>(val));
	}

	virtual void _writeInt16(int16_t val)
	{
		_writeValue(BLANK_STRING, "int16", val);
	}
	virtual void writeInt16(const String& name, int16_t val)
	{
		_writeValue(name, "int16", val);
	}

	virtual void _writeInt32(int32_t val)
	{
		_writeValue(BLANK_STRING, "int32", val);
	}
	virtual void writeInt32(const String& name, int32_t val)
	{
		_writeValue(name, "int32", val);
	}

	virtual void _writeUInt8 (uint8_t val)
	{
		_writeValue(BLANK_STRING, "uint8", static_cast<unsigned int>(val));
	}
	virtual void writeUInt8 (const String& name, uint8_t val)
	{
		_writeValue(name, "uint8", static_cast<unsigned int>(val));
	}

	virtual void _writeUInt16(uint16_t val)
	{
		_writeValue(BLANK_STRING, "uint16", val);
	}
	virtual void writeUInt16(const String& name, uint16_t val)
	{
		_writeValue(name, "uint16", val);
	}

	virtual void _writeUInt32(uint32_t val)
	{
		_writeValue(BLANK_STRING, "uint32", val);
	}
	virtual void writeUInt32(const String& name, uint32_t val)
	{
		_writeValue(name, "uint32", val);
	}

	virtual void _writeFloat(float val)
	{
		_writeValue(BLANK_STRING, "float", val);
	}
	virtual void writeFloat(const String& name, float val)
	{
		_writeValue(name, "float", val);
	}

	virtual void _writeString(const String& val)
	{
		_writeValue(BLANK_STRING, "string", "\"" + val + "\"");
	}
	virtual void writeString(const String& name, const String& val)
	{
		_writeValue(name, "string", "\"" + val + "\"");
	}

	
	virtual void readBool(bool& val)
	{
	}

	virtual void readInt8 (int8_t& val)
	{
	}

	virtual void readInt16(int16_t& val)
	{
	}

	virtual void readInt32(int32_t& val)
	{
	}

	virtual void readUInt8 (uint8_t& val)
	{
	}

	virtual void readUInt16(uint16_t& val)
	{
	}

	virtual void readUInt32(uint32_t& val)
	{
	}

	virtual void readFloat(float& val)
	{
	}

	virtual void readString(String& val)
	{
	}
	
	String getString() const
	{
		return mSS.str();
	}
	
private:
	std::stringstream mSS;
	bool mPretty;
	
};


typedef std::vector<uint32_t> IntVector;

class Vector3f
{
public:
	Vector3f(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{}
	float x;
	float y;
	float z;
};

DataStream& operator<<(DataStream& ds, Vector3f& vec)
{
	DataStream::Block block = ds.createBlock("Vectof3f");
	block.write("x", vec.x);
	block.write("y", vec.y);
	block.write("z", vec.z);
	
	return ds;
}

class GameStruct
{
public:
	GameStruct(int i, float f, const String& s, bool b, Vector3f& vec)
		: mI8(i), mF(f), mS(s), mB(b), mVector3f(vec)
	{
		mI8 = i;
		mI16 = i;
		mI32 = i;
		mU8 = i;
		mU16 = i;
		mU32 = i;
	}
	
	int8_t mI8;
	int16_t mI16;
	int32_t mI32;
	uint8_t mU8;
	uint16_t mU16;
	uint32_t mU32;
	float mF;
	String mS;
	bool mB;
	IntVector mInts;
	Vector3f mVector3f;
};

DataStream& operator<<(DataStream& ds, GameStruct& gs)
{
	DataStream::Block block = ds.createBlock("GameStruct");
	block.write("mI8", gs.mI8);
	block.write("mI16", gs.mI16);
	block.write("mI32", gs.mI32);
	block.write("mU8", gs.mU8);
	block.write("mU16", gs.mU16);
	block.write("mU32", gs.mU32);
	
	ds << gs.mVector3f;
	
	{
		DataStream::List list = ds.createList("Ints", gs.mInts.size());
		for(IntVector::iterator iter = gs.mInts.begin(); iter != gs.mInts.end(); ++iter)
			list.write(*iter);
	}
	
	block.write("mF", gs.mF);
	block.write("mS", gs.mS);
	block.write("mB", gs.mB);
	
	return ds;
}

DataStream& operator<<(DataStream& ds, GameStruct* gs)
{
	return ds << *gs;
}

template <typename NameType, typename MapType>
DataStream& operator<<(DataStream& ds, std::pair<NameType, std::map<String, MapType> >& mapPair)
{
	std::map<String, MapType>& map = mapPair.second;
	DataStream::Block block = ds.createBlock(mapPair.first);
	
	for(std::map<String, MapType>::iterator iter = map.begin();
		iter != map.end();
		++iter)
		ds << *iter;
	
	return ds;
}

template <typename ValueType, typename NameType>
DataStream& operator<<(DataStream::Block& block, std::pair<NameType, ValueType>& pair)
{
	//block.write(
	return ds;
}

template <typename ListType, typename NameType>
DataStream& operator<<(DataStream& ds, std::pair<NameType, ListType>& vecPair)
{
	ListType& vec = vecPair.second;
	DataStream::List list = ds.createList(vecPair.first, vec.size());
	
	for(ListType::iterator iter = vec.begin();
		iter != vec.end();
		++iter)
		list << *iter;
	
	return ds;
}

std::ostream& operator<<(std::ostream& os, DataStream& ds)
{
	return os << ds.getString();
}
/*
int main()
{
	GameStruct gs(100, 3.14159, "Test String", false, Vector3f(1.0, 2.0, 3.0));
	gs.mInts.push_back(1);
	gs.mInts.push_back(2);
	gs.mInts.push_back(3);
	gs.mInts.push_back(4);
	gs.mInts.push_back(5);
	
	XmlStream xds(false);
	xds << gs;
	std::cout << xds << std::endl;
	
	JSONStream jds;
	jds << gs;
	std::cout << jds << std::endl;
	
	std::list<GameStruct> structs;
	structs.push_back(gs);
	structs.push_back(gs);
	structs.push_back(gs);
	structs.push_back(gs);
	
	std::map<String, int> map;
	map["One"] = 1;
	map["Two"] = 2;
	map["Three"] = 3;
	map["Four"] = 4;
	
	JSONStream mapStream;
	mapStream << std::make_pair("map", map);
	std::cout << mapStream << std::endl;
	
	JSONStream structsStream(false);
	structsStream << std::make_pair("structs", structs);
	std::cout << structsStream << std::endl;

}
*/

/*
// XML
<block name="GameStruct">
	<uint32 name="mI32" value="100" />
	<float name="mF" value="3.14159" />
	<string name="mS" value="test string" />
	<bool name="mB" value="true" />
	<list name="Ints">
		<uint32 value="1" />
		<uint32 value="2" />
		<uint32 value="3" />
		<uint32 value="4" />
		<uint32 value="5" />
	</list>
</block>


// JSON
"GameStruct : {
	"mI32" : 100,
	"mF" : 3.14159,
	"mS" : "test string"
	"mB" : true,
	"Ints" : [
		1,
		2,
		3,
		4,
		5
	]
	
}

















*/