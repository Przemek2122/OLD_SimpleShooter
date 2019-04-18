#include "SocketDataParser.h"
#include "Util.h"


SocketDataParser::SocketDataParser()
{}

SocketDataParser::~SocketDataParser()
{}

const char * SocketDataParser::ParseDataIn(SocketObjectType objType, std::string objTag, const char * data)
{
	// Convert to int
	int type = static_cast<int>(objType);
	
	// Prepare
	std::string dataToSend = (char)"A" + (char)type + "_" + *data;

	// Debug
	Util::Debug(dataToSend);

	return dataToSend.c_str();
}

ReturnParserData SocketDataParser::ParseDataOut(const char * data)
{
	// Not parsed by SocketDataParser if true
	if (data[0] != (char)"A")
	{
		ReturnParserData returnError;
		returnError.parsed = false, returnError.objType = SocketObjectType(0), returnError.data = data;
		return returnError;
	}

	// Get SocketObjectType data
	std::string objTypeData = "";
	int i = 1; // data[0] must be A then start from 1
	while (data[i] != (char)"_")
	{
		objTypeData += data[i];
	}

	// Convert a objTypeData to int and make SocketObjectType
	SocketObjectType objType = SocketObjectType(atoi(objTypeData.c_str()));
	switch (objType)
	{
	case SOCKETOBJECT_INITIAL:
		Util::Debug("Found SOCKETOBJECT_INITIAL!");
		break;

	default:
		Util::Debug("Unable to find SocketObjectType: " + objType + (std::string)" With data: " + objTypeData);
		break;
	}

	// Should never happend but...
	ReturnParserData returnError;
	returnError.parsed = false, returnError.objType = SocketObjectType(0), returnError.data = data;

	return returnError;
}
