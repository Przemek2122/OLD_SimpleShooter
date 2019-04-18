#pragma once
#include <string>
#include <map>
#include "Util.h"
#include "game.h"
#include "Sockets/SocketClientTCP.h"
#include "Sockets/SocketServerTCP.h"


class SocketsManager
{
public:
	SocketsManager(Game * mGame);
	~SocketsManager();

	Game * game;


#ifndef _DEDICATED
	/* TCP socket
	 * Local socket used to connect and use later
	 * Only used on client
	 * Doesn't exists on dedicated */
	SocketClientTCP * localSocketTCP;
#endif 

	/* Server listener socket.
	 * Only used on server */
	SocketServerTCP * socketServerTCP;

	/* Connected clients sockets:
	 * Clients connected in map
	 * With @names as string. */
	std::map < char*, std::string > clientSocketsTCP;

	/* Check for incoming connections etc... */
	void Update();

	/* Attempts to connect with
	 * server at @domain with @port
	 * return true on success false otherwise. */
	bool Connect(const char * domain, int port);

	/* Creates listener socket.
	 * Default tag is "server". */
	bool Listen(int port);

	/* Check if there is a player with
	that name on server (clientSocketsTCP) */
	bool HasThatName(std::string name);

	///* Assuming this is not server.
	// * Will return socket with error on dedicated
	// * Inline for performance. */
	//inline SocketClientTCP& GetLocalSocketTCP();

};
