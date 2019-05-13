#pragma once
#include <string>



// Socket data start sequence
#define SocketDataStart "[B%}"
// Socket data end sequence
#define SocketDataEnd "[E%}"

// Socket data
#define SocketDataAuto "[A}" 
// Socket data for separating in automated parsing.
#define SocketDataSeparator "[|}" 

//// Max ammount of data send
//#define SocketDataMax 512

/* Here is as follows:
Any custom data:
* SOCKETOBJECT_CUSTOM = 0
Send on first connection:
* SOCKETOBJECT_INITIAL = 1
ECS System entity:
* SOCKETOBJECT_ENTITY = 2
ECS System component:
* SOCKETOBJECT_COMPONENT = 3 */
enum SocketObjectType
{
	SOCKETOBJECT_ERROR = -1,
	SOCKETOBJECT_CUSTOM = 0,
	SOCKETOBJECT_INITIAL = 1,
	SOCKETOBJECT_ENTITY = 2,
	SOCKETOBJECT_COMPONENT = 3,
};

struct InitialData
{
	InitialData();
	InitialData(char * mNick);

	char * nick;
};

struct ReturnParserData
{
	ReturnParserData();
	ReturnParserData(bool mParsed, SocketObjectType mObjectType, std::string mData);

	bool parsed;
	SocketObjectType objType;
	std::string data;
};

/* Class used for automatic updating.
 * Thing like position, rotation etc 
 * mostly will be updated here. */
static class SocketDataParser
{
public:
	SocketDataParser();
	~SocketDataParser();

	/* Parses data to send over network.
	 * Prepares to recive data on following object. */
	static std::string ParseDataIn(SocketObjectType objType, std::string objTag, const char * data);

	/* Parses data back to what it was before parsing. */
	static ReturnParserData ParseDataOut(const char * data);

	/* As normal parsing but just for initial data send 
	 * when connecting to server from client. */
	static std::string ParseDataInitalIn(InitialData initialData);

	/* Parses back to what was before ParseDataInitalIn(). */
	static InitialData ParseDataInitalOut(const char * data);

};

