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

/* For keeping connection
 * @see https://stackoverflow.com/questions/21867723/socket-keepalive-not-working */
struct KeepConfig 
{
	/** The time (in seconds) the connection needs to remain
	 * idle before TCP starts sending keepalive probes (TCP_KEEPIDLE socket option)  */
	unsigned int keepidle;
	/** The maximum number of keepalive probes TCP should
	 * send before dropping the connection. (TCP_KEEPCNT socket option)  */
	unsigned int keepcnt;

	/** The time (in seconds) between individual keepalive probes.
	 *  (TCP_KEEPINTVL socket option) */
	unsigned int keepintvl;
};

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

	/* Get socket error code.
	 * See platform specific code definition.
	 * For windows @see 
	 * https://docs.microsoft.com/en-us/windows/desktop/winsock/windows-sockets-error-codes-2 */
	static int getSockError();

	/** Enable TCP keepalive on the socket.
	  * Use setTcpKeepaliveCfg() to set keep alive with settings.
	  * @param sock socket to be used.
	  * @return 0 on success -1 on failure */
	static int setTcpKeepalive(SOCKET & sock);

	/** Set the keepalive options on the socket.
	  * This also enables TCP keepalive on the socket.
	  * @param sock socket to be used.
	  * @return 0 on success -1 on failure. */
	static int setTcpKeepaliveCfg(SOCKET & sock, const struct KeepConfig *cfg);

};
