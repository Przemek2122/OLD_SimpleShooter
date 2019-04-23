#include "Socket.h"
#include "Util.h"

Socket::Socket(std::string tag) : SocketTag(tag){}

Socket::~Socket(){}

int Socket::sockInit(void)
{
#if defined(_WIN32) || defined(_WIN64)
	WSADATA wsa_data;
	return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
	return 0;
#endif
}

int Socket::sockQuit(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return WSACleanup();
#else
	return 0;
#endif
}

int Socket::sockClose(SOCKET sock)
{
	int status = 0;

#if defined(_WIN32) || defined(_WIN64)
	status = shutdown(sock, SD_BOTH);
	if (status == 0) { status = closesocket(sock); }
#else
	status = shutdown(sock, SHUT_RDWR);
	if (status == 0) { status = close(sock); }
#endif

	return status;
}

int Socket::getSockError()
{
#if defined(_WIN32) || defined(_WIN64)
	return WSAGetLastError();
#else
	Util::Debug("Error for non windows not implemented. Take a look at Socket.cpp.")
#endif
}

int Socket::setTcpKeepalive(SOCKET & sock)
{
	unsigned int optval = 1;

#ifdef _DEBUG
	if (!sock)
		Util::Debug("setTcpKeepalive(SOCKET & sock) sock is invalid.");

	if (sock == NULL)
		Util::Debug("setTcpKeepalive(SOCKET & sock) sock is NULL.");
#endif

	return setsockopt((SOCKET)sock, SOL_SOCKET, SO_KEEPALIVE, (char *)optval, sizeof((char *)optval));
}

int Socket::setTcpKeepaliveCfg(SOCKET & sock, const KeepConfig * cfg)
{
	int rc;

	// First turn on keepalive
	rc = setTcpKeepalive(sock);
	if (rc != 0) return rc;

	// Then set the keepalive options 
	// Warning! 
	// This options should not be used incode intended to be portable.

	rc = setsockopt((SOCKET)sock, IPPROTO_TCP, TCP_KEEPCNT, (char *)cfg->keepcnt, sizeof ((char *)cfg->keepcnt));
	if (rc != 0) return rc;

	rc = setsockopt((SOCKET)sock, IPPROTO_TCP, TCP_KEEPIDLE, (char *)cfg->keepidle, sizeof((char *)cfg->keepidle));
	if (rc != 0) return rc;

	rc = setsockopt((SOCKET)sock, IPPROTO_TCP, TCP_KEEPINTVL, (char *)cfg->keepintvl, sizeof((char *)cfg->keepintvl));
	if (rc != 0) return rc;

	return 0;
}
