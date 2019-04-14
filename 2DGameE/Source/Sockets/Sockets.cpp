#include "Sockets.h"


SocketsManager::SocketsManager(Game * mGame) : game(mGame)
{}

SocketsManager::~SocketsManager()
{}

void SocketsManager::Update()
{
	// If there is server socket (valid)
	if (socketServer)
	{
		// Then check connection and accept if there is any.
		TCPsocket new_tcpsock;
		new_tcpsock = SDLNet_TCP_Accept(socketServer->tcpSock);
		if (new_tcpsock)
		{
			// Communicate over new_tcpsock
			

			// Add to map - (TCP socket, ip, name)
			std::string name = "sock_name";
			clientSocketsTCP.emplace(&new_tcpsock, name); // @TODO FIX ERROR

			// Log accepted socket
			Util::Info("Accepted socket! " + name);
		}
		else 
		{
			std::string error = SDLNet_GetError();

			if (error != "accept() failed")
			{
				Util::Error("SDLNet_TCP_Accept: " + error);
			}
		}
	}
}

bool SocketsManager::Connect(const char * domain, Uint16 port, std::string tag)
{
	// Create new if invalid
	if (!localSocket)
		localSocket = new SocketClientTCP(tag);

	// Connect
	return localSocket->Connect(domain, port);
}

bool SocketsManager::Listen(Uint16 port, std::string tag)
{
	// Create new if invalid
	if (!socketServer)
		socketServer = new SocketServerTCP(tag);

	// Start listening
	return socketServer->Listen(port);
}

bool SocketsManager::HasThatName(std::string name)
{
	// Go through all socket names.
	for (auto& sock : clientSocketsTCP)
	{
		// True if found
		if (sock.second == name) return true;
	}

	// False if not found
	return false;
}

inline SocketClientTCP & SocketsManager::GetLocalSocketTCP()
{
#ifndef _DEDICATED
	// Simply return socket reference
	return *localSocket;
#else
	// Log error.
	Util::Error("Called GetLocalSocketTCP on dedicated.");
	// Return new socket with tag noticing error.
	return SocketClientTCP("Error. Called on server.");
#endif
}

