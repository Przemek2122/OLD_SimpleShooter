#include "Sockets.h"
#include "SocketDataParser.h"


SocketsManager::SocketsManager(Game * mGame) : game(mGame)
{}

SocketsManager::~SocketsManager()
{}

void SocketsManager::Update()
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

bool SocketsManager::Listen(int port)
{
	// Create new if invalid
	if (!socketServerTCP)
		socketServerTCP = new SocketServerTCP("server");

	socketServerTCP->Listen(port);

	// Start listening
	return true;
}

bool SocketsManager::HasThatName(std::string name)
{
	// False if not found
	return false;
}

