#pragma once
#include <string>

// Socket data start sequence
#define SocketDataStart "AA"
// Socket data end sequence
#define SocketDataEnd NULL 
// Socket data for separating in automated parsing.
#define SocketDataSeparator '#~'

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
	SOCKETOBJECT_CUSTOM = 0,
	SOCKETOBJECT_INITIAL = 1,
	SOCKETOBJECT_ENTITY = 2,
	SOCKETOBJECT_COMPONENT = 3,
};

struct InitialData
{
	char * nick;
};

struct ReturnParserData
{
	bool parsed;
	SocketObjectType objType;
	const char * data;
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
	static const char * ParseDataIn(SocketObjectType objType, std::string objTag, const char * data);

	/* Parses data back to what it was before parsing. */
	static ReturnParserData ParseDataOut(const char * data);

	/* As normal parsing but just for initial data send 
	 * when connecting to server from client. */
	static const char * ParseDataInitalIn(InitialData initialData);

	/* Parses back to what was before ParseDataInitalIn(). */
	static InitialData ParseDataInitalOut(const char * data);

};

