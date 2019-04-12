#pragma once
#include <string>
#include <map>
#include "game.h"
#include "Sockets/SocketClientTCP.h"
#include "Sockets/SocketServer.h"


class SocketsManager
{
public:
	SocketsManager(Game * mGame);
	~SocketsManager();

	Game * game;

	SocketClientTCP * localSocket;
	SocketServer * serverSocket;

	bool Connect(const char * domain, Uint16 port, std::string tag)
	{
		if (!localSocket)
			localSocket = new SocketClientTCP("s_tcp");

		return localSocket->Connect(domain, port);
	}

	bool Listen(Uint16 port, std::string tag)
	{
		return false;
	}

	//SocketServer& Listen(Uint16 port, std::string tag)
	//{
	//	SocketServer* sock = new SocketServer(port, tag);
	//	socketsServer.emplace(sock, tag);
	//	return *sock;
	//}

	///* Creates socket for client (will connect to server)
	// * Uses sdl net. */
	//template <typename S, typename... SArgs>
	//S& CreateClientSocket(SArgs&&... sArgs)
	//{
	//	S* s = new S(sArgs);
	//	socketsClient.emplace(s, s->SocketTag);
	//	return *s;
	//}

	///* Creates socket for server (listening)
	// * Uses sdl net. */
	//template <typename S, typename... SArgs>
	//S& CreateServerSocket(SArgs&&... sArgs)
	//{
	//	S* s = new S(sArgs);
	//	socketsServer.emplace(s, s->SocketTag);
	//	return *s;
	//}

	/* Assuming this is not server.
	 * Probably crash if called on server.
	 * Because it will return empty variable.
 	 * There will be only one socket in here.
	 * Will simply return first element from socketsClient
	 * Inline for performance. */
	//template <typename S>
	//inline S& GetLocalSocket()
	//{
	//	return socketsClient[0];
	//}

};
