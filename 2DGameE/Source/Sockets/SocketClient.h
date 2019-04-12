#pragma once
#include "Socket.h"

class SocketClient : public Socket
{
public:
	SocketClient(std::string tag);
	~SocketClient();

	SDL_Thread *sockThread;

};

