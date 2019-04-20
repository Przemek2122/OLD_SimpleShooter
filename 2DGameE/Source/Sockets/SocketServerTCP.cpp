#include "SocketServerTCP.h"
#include "Util.h"
#include "SocketDataParser.h"
#include <memory>


InAcceptData::InAcceptData() {}

InAcceptData::InAcceptData(TCPAcceptManager * mTcpAcceptManager, unsigned int mPort, char * mAddress, bool anyAddr)
	: tcpAcceptManager(mTcpAcceptManager), port(mPort), address(mAddress), anyAddress(anyAddr)
{}


TCPHandler::TCPHandler(SocketServerTCP * srvTCP, SOCKET * accptSock) : sockSrvTCP(srvTCP), sock(accptSock){}

TCPHandler::~TCPHandler(){}

int TCPHandler::Thread(void * ptr)
{
	return 0;
}


TCPAcceptManager::TCPAcceptManager(SocketServerTCP * srvTCP) : SockSrvTCP(srvTCP)
{
	running = true;
}

TCPAcceptManager::~TCPAcceptManager()
{}


SocketServerTCP::SocketServerTCP(std::string tag) : SocketServer(tag){}

SocketServerTCP::~SocketServerTCP(){}

int SocketServerTCP::AcceptThread(void * ptr)
{
	InAcceptData * acceptData = (InAcceptData *)ptr;
	TCPAcceptManager * TcpAcceptManager = acceptData->tcpAcceptManager;

	TcpAcceptManager->SockSrvTCP->mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TcpAcceptManager->SockSrvTCP->mainSocket == INVALID_SOCKET)
	{
		Util::Debug((std::string)"Error creating socket: " + std::to_string(getSockError()));
		closesocket(TcpAcceptManager->SockSrvTCP->mainSocket);

		return false;
	}

	sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	if (acceptData->anyAddress)
		service.sin_addr.s_addr = inet_addr("0.0.0.0");
	else
		service.sin_addr.s_addr = inet_addr(acceptData->address);
	service.sin_port = htons(acceptData->port);

	if (bind(TcpAcceptManager->SockSrvTCP->mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		Util::Error("bind() failed." + std::to_string(getSockError()));
		closesocket(TcpAcceptManager->SockSrvTCP->mainSocket);
		return false;
	}

	if (listen(TcpAcceptManager->SockSrvTCP->mainSocket, 1) == SOCKET_ERROR)
		Util::Error("Error listening on socket.");

	Util::Info("Waiting for a client to connect... /n");
	if (acceptData->anyAddress)
		Util::Info("(PORT: " + std::to_string(acceptData->port) +
			(std::string)", Bound all IP Adresses) \n");
	else
		Util::Info("(PORT: " + std::to_string(acceptData->port) +
			(std::string)", Bound IP: " + acceptData->address + ") \n");

	while (TcpAcceptManager->running)
	{
		SOCKET acceptSocket = SOCKET_ERROR;

		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);

		while (acceptSocket == SOCKET_ERROR)
		{
			acceptSocket = accept(TcpAcceptManager->SockSrvTCP->mainSocket, (SOCKADDR*)&addr, &addrlen);
		}

		char *ip = inet_ntoa(addr.sin_addr);
		Util::Info("Found incoming connection from: " + (std::string)ip);

		std::unique_ptr <SOCKET> uSockPtr{ &acceptSocket };

		TcpAcceptManager->SockSrvTCP->sockets.emplace_back(std::move(uSockPtr));

		Util::Info("Client connected.");
	}

	return false;
}

bool SocketServerTCP::Listen(const char * domain, unsigned short port, bool allAdresses)
{
	tcpAccept = new TCPAcceptManager(this);

	InAcceptData * acceptData;

	acceptData = new InAcceptData(tcpAccept, port, (char *)domain, allAdresses);

	thread = SDL_CreateThread(SocketServerTCP::AcceptThread, "TCPAccept", acceptData);

	Recive();

	return true;
}

// @Todo move to thread
void SocketServerTCP::Send(char * data)
{
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[32] = "Client says hello!";

	bytesSent = send(mainSocket, sendbuf, strlen(sendbuf), 0);
	Util::Debug("Send: " + bytesSent);
}

// @Todo move to thread
char * SocketServerTCP::Recive()
{
	int bytesRecv = SOCKET_ERROR;
	char recvbuf[32] = "";

	bytesRecv = recv(mainSocket, recvbuf, 32, 0);
	Util::Debug("Bytes received: " + bytesRecv);
	Util::Debug("Received text: " + (std::string)recvbuf);

	return nullptr;
}
