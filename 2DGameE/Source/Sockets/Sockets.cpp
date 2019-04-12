#include "Sockets.h"


SocketsManager::SocketsManager(Game * mGame) : game(mGame)
{}

SocketsManager::~SocketsManager()
{}

bool SocketsManager::Connect(const char * domain, Uint16 port, std::string tag)
{
	if (!localSocket)
		localSocket = new SocketClientTCP(tag);

	return localSocket->Connect(domain, port);
}

bool SocketsManager::Listen(Uint16 port, std::string tag)
{
	if (!socketsServer)
		socketsServer = new SocketServerTCP(tag);

	return socketsServer->Listen(port);
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

