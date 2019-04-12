#include "Sockets/SocketClientTCP.h"
#include "Util.h"

int SocketClientTCP::SocketThread(void *ptr)
{
	int cnt;

	for (cnt = 0; cnt < 10; ++cnt) {
		printf("Thread counter: %d\n", cnt);
		SDL_Delay(50);
	}

	return cnt;
}

SocketClientTCP::SocketClientTCP(std::string tag) : SocketClient(tag)
{}

SocketClientTCP::~SocketClientTCP()
{
	// Terminate thread
	int * status = 0;
	SDL_WaitThread(sockThread, status);

	// Close the connection on sock
	SDLNet_TCP_Close(tcpSock);
}

bool SocketClientTCP::Connect(const char * domain, Uint16 port)
{
	sockThread = SDL_CreateThread(SocketClientTCP::SocketThread, SocketTag.c_str(), (void *)NULL);

	//SDLNet_ResolveHost(&IpAddress, domain, port);

	// Connect to localhost at port using TCP (client)
	if (SDLNet_ResolveHost(&IpAddress, domain, port) == -1)
	{
		Util::Error("SDLNet_ResolveHost: " + (std::string)SDLNet_GetError());
		return false;
	}

	tcpSock = SDLNet_TCP_Open(&IpAddress);
	if (!tcpSock)
	{
		Util::Error("SDLNet_TCP_Open: " + (std::string)SDLNet_GetError());
		return false;
	}

	return true;
}