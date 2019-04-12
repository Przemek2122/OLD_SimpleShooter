#include "SocketServerTCP.h"
#include "Util.h"

int SocketServerTCP::SocketThread(void *ptr)
{
	int cnt;

	for (cnt = 0; cnt < 10; ++cnt) {
		printf("Thread counter: %d\n", cnt);
		SDL_Delay(50);
	}

	return cnt;
}

SocketServerTCP::SocketServerTCP(std::string tag) : SocketServer(tag)
{}

SocketServerTCP::~SocketServerTCP()
{
	// Terminate thread
	int * status = 0;
	SDL_WaitThread(sockThread, status);

	// Close the connection on sock
	SDLNet_TCP_Close(tcpSock);
}

bool SocketServerTCP::Listen(Uint16 port)
{
	sockThread = SDL_CreateThread(SocketServerTCP::SocketThread, SocketTag.c_str(), (void *)NULL);

	// Create a listening TCP socket on port (server)
	if (SDLNet_ResolveHost(&IpAddress, NULL, port) == -1)
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
}
