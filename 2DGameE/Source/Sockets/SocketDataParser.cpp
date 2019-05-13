#include "SocketDataParser.h"
#include "Util.h"


InitialData::InitialData(){}

InitialData::InitialData(char * mNick)
	: nick(mNick) {}

ReturnParserData::ReturnParserData() {}

ReturnParserData::ReturnParserData(bool mParsed, SocketObjectType mObjectType, std::string mData)
	: parsed(mParsed), objType(mObjectType), data(mData) {}


SocketDataParser::SocketDataParser()
{}

SocketDataParser::~SocketDataParser()
{}

std::string SocketDataParser::ParseDataIn(SocketObjectType objType, std::string objTag, const char * data)
{
	// Prepare
	std::string dataToSend = "";

	dataToSend.append(SocketDataAuto);
	dataToSend.append(std::to_string(objType));
	dataToSend.append(SocketDataSeparator);
	dataToSend.append(objTag);
	dataToSend.append(SocketDataSeparator);
	dataToSend.append(data);

#ifdef _DEBUG
	Util::Debug("Parsed data: " + dataToSend);
#endif 

	return dataToSend;
}

ReturnParserData SocketDataParser::ParseDataOut(const char * data)
{
	// Not parsed by SocketDataParser if true.
	// Warning: If true may be not parsed too.
	int i = 0;
	for (; i < strlen(SocketDataAuto); i++)
	{
		// If true anytime then it's not parsed.
		if (data[i] != SocketDataAuto[i])
		{
			return ReturnParserData(false, SocketObjectType(0), data);
		}
	}

	// Get SocketObjectType
	std::string objTypeData = "";
	bool keepRunning = true;
	while (keepRunning)
	{
		// Check if it's not SocketDataSeparator
		if (data[i] == SocketDataSeparator[0])
		{
			size_t size = strlen(SocketDataSeparator);

			// Then check rest
			for (int t = 1; t <= size; t++)
			{
				if (data[i + t] <= size)
				{
					if (data[i + t] != SocketDataSeparator[t])
					{
						// Stop checking if it's different
						break;
					}
				}
				else
				{
					// Stop objtype
					keepRunning = false;
					// Set current char index to be after SocketDataSeparator
					i += t;
					break;
				}
			}
		}

		// If not then add
		objTypeData += data[i];

		// Next
		i++;
	}

	// Get SocketObjectTag
	std::string objTypeTag = "";
	keepRunning = true;
	while (keepRunning)
	{
		objTypeTag += data[i];

		// Check if it's not SocketDataSeparator
		if (data[i] == SocketDataSeparator[0])
		{
			size_t size = strlen(SocketDataSeparator);

			// Then check rest
			for (int t = 1; t <= size; t++)
			{
				if (data[i + t] <= size)
				{
					if (data[i + t] != SocketDataSeparator[t])
					{
						// Stop checking if it's different
						continue;
					}
				}
				else
				{
					// Stop objtype
					keepRunning = false;
					// Set current char index to be after SocketDataSeparator
					i += t + 1;
					break;
				}
			}
		}

		i++;
	}

	// Convert a objTypeData to int and make SocketObjectType
	SocketObjectType objType = SocketObjectType(atoi(objTypeData.c_str()));

	// @TODO - Remove unwanted part
	std::string newData(data);

	// Return edited.
	return ReturnParserData(true, objType, newData.substr(i));
}

std::string SocketDataParser::ParseDataInitalIn(InitialData initialData)
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

