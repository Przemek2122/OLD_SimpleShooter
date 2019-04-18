#pragma once
#include "SocketServer.h"
#include <iostream>

class SocketServerTCP : public SocketServer
{
public:
	SocketServerTCP(std::string tag);
	~SocketServerTCP();


	bool Listen(unsigned short port);

	void Send(char * data);

	char * Recive();



};

