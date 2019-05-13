#pragma once
#include "SocketServer.h"
#include "SDL.h"
#include <atomic>
#include <map>


#define SOCKETDATABUFFER 256

class Game;
class TCPHandler;
class TCPAcceptManager;
class SocketServerTCP;


/* Used when creating thread to pass data. */
struct InAcceptData
{
	InAcceptData();
	InAcceptData(TCPAcceptManager * mTcpAcceptManager, unsigned int mPort, char * mAddress, bool anyAddr);

	TCPAcceptManager * tcpAcceptManager;
	unsigned int port;
	char * address;
	bool anyAddress;
};

/* Class for handling tcp connection to client. 
 * Send / Recive data etc.
 * General operation on socket.
 * Everything in separate thread. */
class TCPHandler
{
public:
	TCPHandler(SocketServerTCP * srvTCP, SOCKET * accptSock, Game * mGame);
	~TCPHandler();

	static int TCPHandle(void * ptr);

	void Stop();

	void Send(char * data, std::string client);

	/* Reads data (As long as there is any)
	 * Skips any data before SocketDataStart chars sequence and
	 * Skips any data after SocketDataEnd.
	 * It shouldn't happen usualy but if there is some kind of error then that may happen. */
	std::string Recive();

	int HandleErrors();

	bool keepReciving;

	SocketServerTCP * sockSrvTCP;

	SOCKET sock;

	SDL_Thread *thread;

	Game * game;

};

/* Class for accepting incoming connections.
 * Accepts socket creates TCPHandler for new sock etc. */
class TCPAcceptManager
{
public:
	TCPAcceptManager(SocketServerTCP * srvTCP);
	~TCPAcceptManager();

	bool running;

	SocketServerTCP * SockSrvTCP;

private:

};

/* Class manages TCP on server.
 * Call Listen() to start listening on thread. */
class SocketServerTCP : public SocketServer
{
public:
	SocketServerTCP(std::string tag, Game * mGame);
	~SocketServerTCP();

	Game * game;

	/* Class for thread accepting new connections. */
	TCPAcceptManager * tcpAccept;

	/* Map with classes containg tcp handling class. */
	std::map< TCPHandler*, std::string > clientTCPHandlers;

	/* Thread for accepting new connection */
	static int AcceptThread(void * ptr);

	/* Starts listening */
	bool Listen(const char * domain, unsigned short port, bool allAdresses);

	/* Stops listening (accepting)
	 * Then disable all threads handling tcp connections. */
	void Stop();

	/* Send data over */
	void Send(char * data, std::string client);

	/* Recive data */ 
	char * Recive();

private:
	/* Thread for accept (listen) */
	SDL_Thread *thread;

};

