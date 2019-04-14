#pragma once
#include "Sockets/SocketClient.h"


class SocketClientTCP : public SocketClient
{
public:
	SocketClientTCP(std::string tag);
	~SocketClientTCP();

	TCPsocket tcpSock;

public:
	static int SocketThread(void * ptr);

	bool Connect(const char * domain, Uint16 port);

	void Send(char * data);

	char * Recive();

	//void TestPing();


};

