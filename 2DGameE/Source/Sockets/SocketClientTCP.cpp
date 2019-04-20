#include "SocketClientTCP.h"
#include "SocketDataParser.h"
#include "Util.h"


AsyncConnection::AsyncConnection(SocketClientTCP * mClientTCP) : clientTCP(mClientTCP)
{
	shouldCheck = false;
	connected = false;
}

AsyncConnection::~AsyncConnection() {}

int SocketClientTCP::ConnectionThread(void * ptr)
{
	ConnectionData * connectionData = (ConnectionData *)ptr;

	connectionData->asyncConnection->clientTCP->mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connectionData->asyncConnection->clientTCP->mainSocket == INVALID_SOCKET)
	{
		Util::Debug("Error creating socket: " + getSockError());
		closesocket(connectionData->asyncConnection->clientTCP->mainSocket);

		return false;
	}

	sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(connectionData->domain);
	service.sin_port = htons(connectionData->port);

	// Probably should be in thread
	if (connect(connectionData->asyncConnection->clientTCP->mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		Util::Warning("Failed to connect.");
		sockClose(connectionData->asyncConnection->clientTCP->mainSocket);
		return false;
	}
}

SocketClientTCP::SocketClientTCP(std::string tag) : SocketClient(tag){}

SocketClientTCP::~SocketClientTCP(){}

bool SocketClientTCP::Connect(const char * domain, unsigned short port)
{
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		Util::Debug("Error creating socket: " + getSockError());
		closesocket(mainSocket);

		return false;
	}

	sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(domain);
	service.sin_port = htons(port);

	// Probably should be in thread
	if (connect(mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		Util::Warning("Failed to connect.");
		sockClose(mainSocket);
		return false;
	}

	return true;
}

void SocketClientTCP::AsyncConnect(const char * domain, unsigned short port)
{
	asyncConnect = new AsyncConnection(this);

	ConnectionData * connectionData = new ConnectionData();

	thread = SDL_CreateThread(SocketClientTCP::ConnectionThread, "AsyncConnect", connectionData);

}

bool SocketClientTCP::IsAsyncReady()
{
	return asyncConnect->shouldCheck;
}

bool SocketClientTCP::IsAsyncConnected()
{
	return asyncConnect->connected;
}

// @Todo move to thread
void SocketClientTCP::Send(const char * data)
{
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[32] = "Client says hello!";

	bytesSent = send(mainSocket, sendbuf, strlen(sendbuf), 0);
	Util::Debug("Send: " + bytesSent);
}

// @Todo move to thread
char * SocketClientTCP::Recive()
{
	int bytesRecv = SOCKET_ERROR;
	char recvbuf[32] = "";

	bytesRecv = recv(mainSocket, recvbuf, 32, 0);
	Util::Debug("Bytes received: " + bytesRecv);
	Util::Debug("Received text: " + (std::string)recvbuf);

	return nullptr;
}
