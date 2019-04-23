#include "SocketServerTCP.h"
#include "Util.h"
#include "SocketDataParser.h"
#include <memory>




InAcceptData::InAcceptData() {}

InAcceptData::InAcceptData(TCPAcceptManager * mTcpAcceptManager, unsigned int mPort, char * mAddress, bool anyAddr)
	: tcpAcceptManager(mTcpAcceptManager), port(mPort), address(mAddress), anyAddress(anyAddr) {}


TCPHandler::TCPHandler(SocketServerTCP * srvTCP, SOCKET * accptSock) : sockSrvTCP(srvTCP), sock(*accptSock)
{
	keepReciving = true;
}

TCPHandler::~TCPHandler()
{
	keepReciving = false;
	SDL_DetachThread(thread);
}

int TCPHandler::TCPHandle(void * ptr)
{
	TCPHandler * tcpHandler = (TCPHandler *)ptr;

#ifdef _DEBUG
	if (ptr == NULL)
		Util::Debug("TCPHandle(): ptr is NULL.");

	if (tcpHandler == NULL)
		Util::Debug("TCPHandle(): tcpHandler is NULL.");

	if (!tcpHandler->sock)
		Util::Debug("TCPHandle(): tcpHandler->sock is invalid.");
#endif

	// Delay alive checks
	long long lastMS;
	long delayMS = 2000;
	Util::startDelay(lastMS);

	// Loop
	while (/*tcpHandler->tcpHandler->keepReciving*/ true)
	{
		if (Util::isDelayed(lastMS, delayMS))
		{
			// Debug errors
			/*tcpHandler->tcpHandler->HandleErrors();*/

			int error = SocketServerTCP::getSockError();

			Util::Info("Socket error: " + std::to_string(error));

			// Delay next check
			Util::startDelay(lastMS);
		}

		/*const char * recivedData = tcpHandler->tcpHandler.get()->Recive();
		if (recivedData != "")
		{
			ReturnParserData parserData = SocketDataParser::ParseDataOut(recivedData);
			if (parserData.parsed)
			{
				switch (parserData.objType)
				{
				case SOCKETOBJECT_INITIAL:
					Util::Info(parserData.data);
					break;

				default:
					Util::Error("TCPHandler::TCPHandle(): switch: Unknown data type.");
					break;
				}
			}
			else
			{
				Util::Error("TCPHandler::TCPHandle(): Data is not parsed.");
				Util::Error("Got: " + (std::string)recivedData);
			}
		}*/

		int bytesRecv = SOCKET_ERROR;
		char recvbuf[128] = "";

		bytesRecv = recv(tcpHandler->sock, recvbuf, 128, 0);
		if (bytesRecv > 0)
		{
			Util::Debug("Bytes received: " + bytesRecv);
			Util::Debug("Received text: " + (std::string)recvbuf);
		}

		SDL_Delay(100);
	}

	return 0;
}

void TCPHandler::Stop()
{
	keepReciving = false;
	SDL_DetachThread(thread);
}

void TCPHandler::Send(char * data, std::string client)
{
	int bytesSent;

	bytesSent = send((SOCKET)sock, data, strlen(data), 0);

	Util::Debug("Send: " + bytesSent);
}

char * TCPHandler::Recive()
{
#ifdef _DEBUG
	if (this == NULL) // seriously was null and function almost worked.
	{
		Util::Debug("TCPHandler::ReciveLoop(): this is NULL.");
		return (char *)"error";
	}
	if ((SOCKET)&sock == NULL)
	{
		Util::Debug("TCPHandler::ReciveLoop(): (SOCKET)&sock is NULL.");
		return (char *)"error";
	}
	if (!(SOCKET)&sock)
	{
		Util::Debug("TCPHandler::ReciveLoop(): (SOCKET)&sock is not valid.");
		return (char *)"error";
	}
#endif

	// Buffer for recived data.
	int bytesRecv = SOCKET_ERROR;
	char recvbuf[SOCKETDATABUFFER];

	bool run = true;
	
	// Buffer for total recived data. 
	// Recived as long as there is something to recive.
	char * newData = (char *)"";

	while (run)
	{
		bytesRecv = recv((SOCKET)&sock, recvbuf, SOCKETDATABUFFER, 0);

		// If there is at least one byte
		// otherwise there is no point on doing anything
		// as no data was recived
		if (bytesRecv <= 0)
		{
			return (char *)"";
		}

		// For each character in recvbuf
		unsigned int size = sizeof(recvbuf);
		for (int i = 0; i < size; i++)
		{
			// If socket data end is not reached
			if (recvbuf[i] != SocketDataEnd)
			{
				// Add data to new data
				newData += recvbuf[i];
			}
			else
			{
				// Stop checking for new data as end of data was found
				run = false;

				// Log as debug recived text
				std::cerr << "Recived text: " << newData << std::endl;

				// Return recived data
				return newData;
			}
		}
	}
}

bool TCPHandler::HandleErrors()
{
	int error = SocketServerTCP::getSockError();

	Util::Info("Socket error: " + std::to_string(error));

	return false;
}


TCPAcceptManager::TCPAcceptManager(SocketServerTCP * srvTCP) : SockSrvTCP(srvTCP)
{
	running = true;
}

TCPAcceptManager::~TCPAcceptManager()
{}


SocketServerTCP::SocketServerTCP(std::string tag) : SocketServer(tag)
{}

SocketServerTCP::~SocketServerTCP()
{
	Stop();
}

int SocketServerTCP::AcceptThread(void * ptr)
{
	/* Initial data sent to thread */
	InAcceptData * acceptData = (InAcceptData *)ptr;
	/* New clas for managing this thread */
	TCPAcceptManager * TcpAcceptManager = acceptData->tcpAcceptManager;

#ifdef _DEBUG
	if (ptr == NULL)
		Util::Debug("AcceptThread(): ptr is NULL.");

	if (acceptData == NULL)
		Util::Debug("AcceptThread(): acceptData is NULL.");

	if (TcpAcceptManager == NULL)
		Util::Debug("AcceptThread(): TcpAcceptManager is NULLL.");
#endif

	/* Setting up listening on socket
	 * @see (PL) http://cpp0x.pl/kursy/Kurs-WinAPI-C++/Zaawansowane/Winsock/371 */ 
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
	if (acceptData->anyAddress) // Any adress
		service.sin_addr.s_addr = inet_addr("0.0.0.0");
	else // Only one specified address
		service.sin_addr.s_addr = inet_addr(acceptData->address);
	service.sin_port = htons(acceptData->port);

	// Bind
	if (bind(TcpAcceptManager->SockSrvTCP->mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		Util::Error("bind() failed." + std::to_string(getSockError()));
		closesocket(TcpAcceptManager->SockSrvTCP->mainSocket);
		return false;
	}

	// Start listening
	if (listen(TcpAcceptManager->SockSrvTCP->mainSocket, 1) == SOCKET_ERROR)
		Util::Error("Error listening on socket.");

	Util::Info("Waiting for a client to connect...");

	if (acceptData->anyAddress)
		Util::Info("(PORT: " + std::to_string(acceptData->port) +
			(std::string)", Bound all IP Adresses) \n");
	else
		Util::Info("(PORT: " + std::to_string(acceptData->port) +
			(std::string)", Bound IP: " + acceptData->address + ") \n");

	// Listen & accept loop
	while (TcpAcceptManager->running)
	{
		SOCKET acceptSocket = SOCKET_ERROR;

		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);

		// Wait until client connects
		while (acceptSocket == SOCKET_ERROR && TcpAcceptManager->running)
		{
			acceptSocket = accept(TcpAcceptManager->SockSrvTCP->mainSocket, (SOCKADDR*)&addr, &addrlen);
		}

		// Log incoming connection.
		char *ip = inet_ntoa(addr.sin_addr);
		Util::Info("Found incoming connection from: " + (std::string)ip);

#ifdef _DEBUG
		if (!acceptSocket)
			Util::Debug("SocketServerTCP::AcceptThread(): acceptSocket is invalid.");
#endif

		// Connection handler
		TCPHandler * tcpHandler = new TCPHandler(TcpAcceptManager->SockSrvTCP, &acceptSocket);

		// Add to clientTCPHandlers
		TcpAcceptManager->SockSrvTCP->clientTCPHandlers.emplace(tcpHandler, "test");

		// Create thread
		// @TODO Check if thread with name "TCPHandle" doesn't exist already
		tcpHandler->thread = SDL_CreateThread(TCPHandler::TCPHandle, "TCPHandle", tcpHandler);

		// Log successfully connected client.
		Util::Info("Client connected succesfully.");

		//while (true)
		//{
		//	int bytesRecv = SOCKET_ERROR;
		//	char recvbuf[128] = "";

		//	bytesRecv = recv(acceptSocket, recvbuf, 128, 0);
		//	if (bytesRecv > 0 && recvbuf[0] != NULL)
		//	{
		//		Util::Debug("Bytes received: " + bytesRecv);
		//		Util::Debug("Received text: " + (std::string)recvbuf);
		//	}
		//}
	}

	return false;
}

bool SocketServerTCP::Listen(const char * domain, unsigned short port, bool allAdresses)
{
	tcpAccept = new TCPAcceptManager(this);

	InAcceptData * acceptData;

	acceptData = new InAcceptData(tcpAccept, port, (char *)domain, allAdresses);

	thread = SDL_CreateThread(SocketServerTCP::AcceptThread, "TCPAccept", acceptData);

	return true;
}

void SocketServerTCP::Stop()
{
	// Stop accept thread
	tcpAccept->running = false;
	SDL_DetachThread(thread);

	// Stop all threads handling tcp
	for (auto & c : clientTCPHandlers)
	{
		c.first->Stop();
	}
}

// @Todo move to thread
void SocketServerTCP::Send(char * data, std::string client)
{
	int bytesSent;

	bytesSent = send(mainSocket, data, strlen(data), 0);
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

	return (char *)bytesRecv;
}

