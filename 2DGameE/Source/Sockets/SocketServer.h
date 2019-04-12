#pragma once
#include "Socket.h"
#include "SDL_net.h"

class SocketServer : public Socket
{
public:
	SocketServer(std::string tag);
	~SocketServer();

	SDL_Thread *sockThread;


};

