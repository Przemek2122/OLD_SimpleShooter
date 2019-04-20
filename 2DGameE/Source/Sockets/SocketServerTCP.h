#pragma once
#include "SocketServer.h"
#include "SDL.h"
#include <atomic>
#include <vector>
#include <map>

class TCPAcceptManager;

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

class SocketServerTCP;

/* Class for handling tcp connection to client. 
 * Send / Recive data etc.
 * General operation on socket.
 * Everything in separate thread. */
class TCPHandler
{
	TCPHandler(SocketServerTCP * srvTCP, SOCKET * accptSock);
	~TCPHandler();

	static int Thread(void * ptr);

	SocketServerTCP * sockSrvTCP;
	SOCKET * sock;

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
 * Call Listen to start listening on thread. */
class SocketServerTCP : public SocketServer
{
public:
	SocketServerTCP(std::string tag);
	~SocketServerTCP();

	TCPAcceptManager * tcpAccept;

	/* Vector with connected sockets. */
	std::vector < std::unique_ptr < SOCKET > > sockets;

	//std::map < TCPHandler, std::string > clientSocketsTCP;


	static int AcceptThread(void * ptr);

	/* Starts listening */
	bool Listen(const char * domain, unsigned short port, bool allAdresses);

	void Send(char * data);

	char * Recive();

private:
	SDL_Thread *thread;

};

