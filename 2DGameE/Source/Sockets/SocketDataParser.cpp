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
	std::string dataToSend = /*SocketDataStart +*/
		(char *)SocketDataStart
		+ (char)type + SocketDataSeparator
		+ (char)objTag.c_str() + SocketDataSeparator
		+ *data + SocketDataEnd;

	// Debug
	Util::Debug("Parsed data: " + dataToSend);

	return dataToSend.c_str();
}

ReturnParserData SocketDataParser::ParseDataOut(const char * data)
{
	// Not parsed by SocketDataParser if true
	// Warning if true may be not parsed too.
	char * sockDataStart = (char *)SocketDataStart;
	for (int t = 0; t < strlen(sockDataStart); t++)
	{
		// If true anytime then it's not parsed.
		if (data[t] != sockDataStart[t])
		{
			ReturnParserData returnError;
			returnError.parsed = false, returnError.objType = SocketObjectType(0), returnError.data = data;
			return returnError;
		}
	}

	// Get SocketObjectType
	std::string objTypeData = "";
	bool stillObjType = true;
	int i = 1; // data[0] must be A then start from 1
	char * sockDataSepr = (char *)SocketDataSeparator;
	while (stillObjType)
	{
		objTypeData += data[i];

		if (data[i] != sockDataSepr[0] && data[i + 1] != sockDataSepr[1])
			stillObjType = false;

		i++;
	}

	// Get SocketObjectTag
	std::string objTypeTag = "";
	stillObjType = true;
	i = 1; // data[0] must be A then start from 1
	while (stillObjType)
	{
		objTypeData += data[i];

		if (data[i] != sockDataSepr[0] && data[i + 1] != sockDataSepr[1])
			stillObjType = false;

		i++;
	}

	// Convert a objTypeData to int and make SocketObjectType
	SocketObjectType objType = SocketObjectType(atoi(objTypeData.c_str()));
	switch (objType)
	{
	case SOCKETOBJECT_CUSTOM:
		Util::Debug("Found SOCKETOBJECT_CUSTOM!");
		break;

	case SOCKETOBJECT_INITIAL:
		Util::Debug("Found SOCKETOBJECT_INITIAL!");
		ReturnParserData parserData;
		parserData.parsed = true;
		parserData.objType = objType;
		parserData.data = "Not finished.";
		return parserData;
		break;

	case SOCKETOBJECT_ENTITY:
		Util::Debug("Found SOCKETOBJECT_ENTITY!");
		break;

	case SOCKETOBJECT_COMPONENT:
		Util::Debug("Found SOCKETOBJECT_COMPONENT!");
		break;

	default:
		Util::Debug("Unable to find SocketObjectType: " + objType + (std::string)" With data: " + objTypeData);
		break;
	}

	// Should happend only when switch end at default...
	ReturnParserData returnError;
	returnError.parsed = false, returnError.objType = SocketObjectType(0), returnError.data = data;

	return returnError;
}

const char * SocketDataParser::ParseDataInitalIn(InitialData initialData)
{
	char * data;

	data = initialData.nick;

	return ParseDataIn(SOCKETOBJECT_INITIAL, "", data);
}

InitialData SocketDataParser::ParseDataInitalOut(const char * data)
{
	InitialData initialData;
	initialData.nick = (char *)data;

	return initialData;
}
