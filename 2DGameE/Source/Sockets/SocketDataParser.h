#pragma once
#include <string>


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

	/* Parses data to send over network
	 * Prepares to recive data on following object */
	static const char * ParseDataIn(SocketObjectType objType, std::string objTag, const char * data);


	static ReturnParserData ParseDataOut(const char * data);


};

