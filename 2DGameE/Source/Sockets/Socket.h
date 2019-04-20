#pragma once
#include <string>

// Network sockets includes
#if defined(_WIN32) || defined(_WIN64)
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib,"WS2_32")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif


class Socket
{
public:
	Socket(std::string tag);
	~Socket();

	/* Tag. Should be usefull on server. */
	std::string SocketTag;

	/* Default socket for both client and server. */
	SOCKET mainSocket;


	/* Initialization of socket. Required on windows. */
	static int sockInit(void);

	/* Quit socket. Required on windows. */
	static int sockQuit(void);

	/* Clse socket for both windows and linux */
	static int sockClose(SOCKET sock);

	static int getSockError();

};
