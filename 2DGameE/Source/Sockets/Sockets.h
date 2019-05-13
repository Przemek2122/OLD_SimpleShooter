#pragma once
#include <string>
#include <map>
#include "Util.h"
#include "game.h"
#include "Sockets/SocketClientUDP.h"
#include "Sockets/SocketServerUDP.h"
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
	std::map < SocketClientTCP, std::string > clientSocketsTCP;

	/* Check for incoming connections etc... */
	void update();

	/* Attempts to connect with
	 * server at @domain with @port
	 * return true on success false otherwise. */
	bool Connect(const char * domain, int port);

	/* Creates listener socket.
	 * Default tag is "server".
	 * You can allow only specific address on port 
	 * or all with setting allAdresses to true. */
	bool Listen(const char * domain, unsigned short port, bool allAdresses);

	/* Check if there is a player with
	that name on server (clientSocketsTCP) */
	inline bool HasThatName(std::string name);

	///* Assuming this is not server.
	// * Will return socket with error on dedicated
	// * Inline for performance. */
	//inline SocketClientTCP& GetLocalSocketTCP();

};
