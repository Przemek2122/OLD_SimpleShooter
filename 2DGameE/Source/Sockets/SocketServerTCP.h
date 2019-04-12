#pragma once
#include "SocketServer.h"
class SocketServerTCP : public SocketServer
{
public:
	SocketServerTCP(std::string tag);
	~SocketServerTCP();

	TCPsocket tcpSock;

	static int SocketThread(void * ptr);

	bool Listen(Uint16 port);


};

