#include "SocketServerTCP.h"
#include "Util.h"

int SocketServerTCP::SocketThread(void *ptr)
{
	Util::Debug("Thread is running.");

	return 1;
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

void SocketServerTCP::Send(char * data)
{
	int len, result;

	len = strlen(data) + 1; // Add one for the terminating NULL
	result = SDLNet_TCP_Send(tcpSock, data, len);
	if (result < len)
	{
		Util::Debug("SDLNet_TCP_Send: " + (std::string)SDLNet_GetError());
		// It may be good to disconnect sock because it is likely invalid now.
	}
}

char * SocketServerTCP::Recive()
{
#define MAXLEN 1024
	int result;
	char msg[MAXLEN];

	result = SDLNet_TCP_Recv(tcpSock, msg, MAXLEN);
	if (result <= 0)
	{
		// An error may have occured, but sometimes you can just ignore it
		// It may be good to disconnect sock because it is likely invalid now.
	}

	Util::Debug("Received: " + (std::string)msg);

	return msg;
}
