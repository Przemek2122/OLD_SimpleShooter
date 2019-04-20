#pragma once
#include "SocketClient.h"
#include "SDL.h"
#include <atomic>


class SocketClientTCP;
class AsyncConnection;

struct ConnectionData
{
	AsyncConnection * asyncConnection;
	char * domain;
	unsigned short port;
};

class AsyncConnection
{
public:
	AsyncConnection(SocketClientTCP * mClientTCP);
	~AsyncConnection();

	std::atomic_bool shouldCheck;
	std::atomic_bool connected;

	SocketClientTCP * clientTCP;

};

class SocketClientTCP : public SocketClient
{
public:
	SocketClientTCP(std::string tag);
	~SocketClientTCP();

	/* Blocking connection.
	 * @see AsyncConnect() for non blocking. */
	bool Connect(const char * domain, unsigned short port);

	/* Non blocking connection. 
	 * Use IsAsyncReady() to check if it's ready then 
	 * IsAsyncConnected() to see if it was succesfull. */
	void AsyncConnect(const char * domain, unsigned short port);

	/* If true you can check with IsAsyncConnected() 
	 * if it's succesfully connected or not*/
	bool IsAsyncReady();

	/* Was async connection sucessfull? Or not? */
	bool IsAsyncConnected();

	void Send(const char * data);

	char * Recive();

private:
	AsyncConnection * asyncConnect;
	SDL_Thread *thread;

private:
	static int ConnectionThread(void * ptr);


};

