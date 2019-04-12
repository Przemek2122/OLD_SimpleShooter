#pragma once
#include <string>
#include "SDL_net.h"

class Socket
{
public:
	Socket(std::string tag) : SocketTag(tag) {}
	~Socket();

	std::string SocketTag;

	IPaddress IpAddress;

};

