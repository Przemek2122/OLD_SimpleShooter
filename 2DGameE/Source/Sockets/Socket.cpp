#include "Socket.h"

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
	Util::Debug("Error for non windows not implemented.")
#endif
}
