#pragma once
#include "SocketServer.h"
class SocketServerUDP :
	public SocketServer
{
public:
	SocketServerUDP(std::string tag);
	~SocketServerUDP();


};

