#pragma once
#include "Socket.h"

class SocketClient : public Socket
{
public:
	SocketClient(const char * domain, Uint16 port, std::string tag);
	~SocketClient();

	bool Connect();

	TCPsocket tcpSock;

	SDL_Thread *sockThread;

};

