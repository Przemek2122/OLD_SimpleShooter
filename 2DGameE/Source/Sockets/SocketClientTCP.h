#pragma once
#include "SocketClient.h"


class SocketClientTCP : public SocketClient
{
public:
	SocketClientTCP(std::string tag);
	~SocketClientTCP();

public:

public:
	bool Connect(const char * domain, unsigned short port);

	void Send(const char * data);

	char * Recive();


};

