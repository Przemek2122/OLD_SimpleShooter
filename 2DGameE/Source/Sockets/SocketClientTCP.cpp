#include "Sockets/SocketClientTCP.h"
#include "Util.h"

int SocketClientTCP::SocketThread(void *ptr)
{
	Util::Debug("Thread is running.");

	return 1;
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

void SocketClientTCP::Send(char * data)
{
	int len, result;

	len = strlen(data) + 1; // add one for the terminating NULL
	result = SDLNet_TCP_Send(tcpSock, data, len);
	if (result < len) 
	{
		Util::Debug("SDLNet_TCP_Send: " + (std::string)SDLNet_GetError());
		// It may be good to disconnect sock because it is likely invalid now.
	}
}

char * SocketClientTCP::Recive()
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
