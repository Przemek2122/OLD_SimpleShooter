#include "Sockets.h"
#include "SocketDataParser.h"


SocketsManager::SocketsManager(Game * mGame) : game(mGame)
{
	Socket::sockInit();
}

SocketsManager::~SocketsManager()
{
	Socket::sockQuit();
}

void SocketsManager::update()
{
	
}

bool SocketsManager::Connect(const char * domain, int port)
{
	// Create new if invalid
	if (!localSocketTCP)
		localSocketTCP = new SocketClientTCP("local");

	// Connect
	return localSocketTCP->Connect(domain, port);
}

bool SocketsManager::Listen(const char * domain, unsigned short port, bool allAdresses)
{
	// Create new if invalid
	if (!socketServerTCP)
		socketServerTCP = new SocketServerTCP("server", game);

	// Start listening
	return socketServerTCP->Listen(domain, port, allAdresses);
}

bool SocketsManager::HasThatName(std::string name)
{
	// False if not found
	return false;
}

