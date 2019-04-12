#pragma once
#include "Sockets/SocketClient.h"
class SocketClientUDP : public SocketClient
{
public:
	SocketClientUDP(std::string tag);
	~SocketClientUDP();
};

