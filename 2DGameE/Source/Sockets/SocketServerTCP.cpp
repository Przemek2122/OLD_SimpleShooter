#include "SocketServerTCP.h"
#include "Util.h"
#include "SocketDataParser.h"
#include <memory>
#include "Game.h"
#include "Components/ECS.h"


InAcceptData::InAcceptData() {}

InAcceptData::InAcceptData(TCPAcceptManager * mTcpAcceptManager, unsigned int mPort, char * mAddress, bool anyAddr)
	: tcpAcceptManager(mTcpAcceptManager), port(mPort), address(mAddress), anyAddress(anyAddr) {}


TCPHandler::TCPHandler(SocketServerTCP * srvTCP, SOCKET * accptSock, Game * mGame)
	: sockSrvTCP(srvTCP), sock(*accptSock), game(mGame)
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
	while (tcpHandler->keepReciving)
	{
		if (Util::isDelayed(lastMS, delayMS))
		{
			// Debug errors
			tcpHandler->HandleErrors();

			// Delay next check
			Util::startDelay(lastMS);
		}

		std::string recived = tcpHandler->Recive();
		if (recived != "")
		{
			ReturnParserData rData = SocketDataParser::ParseDataOut(recived.c_str());
			if (rData.parsed)
			{
				switch (rData.objType)
				{
				case SOCKETOBJECT_INITIAL:
					Util::Info("Initial data: " + (std::string)rData.data);
					break;

				default:
					Util::Warning("Got sth parsed. But unhandled yet.");
					break;
				}
			}
			else
			{
				Util::Warning("Unparsed. Got: " + recived);
			}
		}

#ifdef _DEBUG
		if (tcpHandler->game->ECSManager == NULL)
			Util::Debug("TCPHandle(): tcpHandler->game->ECSManager is NULL.");
		if (tcpHandler->game == NULL)
			Util::Debug("TCPHandle(): tcpHandler->game is NULL.");
#endif

		//for (auto & e : tcpHandler->game->ECSManager->entities)
		//{
		//	if (e->considerNetwork)
		//	{
		//		Util::Debug("Found network considered.");
		//	}
		//}

		SDL_Delay(50);
	}

	return 0;
}

void TCPHandler::Stop()
{
	keepReciving = false;
	SocketServerTCP::sockClose(sock);
	SDL_DetachThread(thread);
}

void TCPHandler::Send(char * data, std::string client)
{
#ifdef _DEBUG
	if (!sock || sock == NULL)
	{
		Util::Error("SocketClientTCP::Send(): mainSocket is invalid or NULL.");
		Util::Error("No data was send. - Debug only.");
		return;
	}

	if (data == NULL)
	{
		Util::Error("SocketClientTCP::Send(const char * data): data pointer is NULL.");
		Util::Error("No data was send. - Debug only.");
		return;
	}
#endif 

	// Add start and end to the data
	std::string dataString;
	dataString.append(SocketDataStart);
	dataString.append(data);
	dataString.append(SocketDataEnd);

#ifdef _DEBUG
	// Log debug data. (Characters which will be attempted to send.)
	Util::Debug("Attempting to send: " + dataString);
#endif

	// Send data
	int bytesSent = send(sock, dataString.c_str(), strlen(dataString.c_str()), 0);

#ifdef _DEBUG
	// Log debug data. (Ammount of send bytes.)
	Util::Debug("Send: " + std::to_string(bytesSent) + " bytes.");
#endif
}

std::string TCPHandler::Recive()
{
#ifdef _DEBUG
	if (!sock)
	{
		Util::Debug("TCPHandler::ReciveLoop(): sock is not valid.");
		return (char *)"Error. sock invalid";
	}
#endif

	// Total data
	int * totalRecv = 0;
	std::string totalbuf = "";

	// Is running loop?
	bool readNewData = true;

	// Recive loop
	while (readNewData)
	{
		// Current recv data
		int bytesRecv = SOCKET_ERROR;
		char recvbuf[SOCKETDATABUFFER];

		// Get
		bytesRecv = recv(sock, recvbuf, SOCKETDATABUFFER, 0);

		// Is there any data?
		// If condition is true then there isn't and there is no point of doing anything
		if (bytesRecv <= 0)
		{
#ifdef _DEBUG
			Util::Debug("No data recived in recv.");
#endif
			return "";
		}

		// Start char buffer index
		size_t i = 0;

		bool keepStartFinding = true;

		// Find start (Seems complicated but it's not)
		size_t dartStartSize = strlen(SocketDataStart);
		while (i < SOCKETDATABUFFER && keepStartFinding)
		{
			// If SocketDataStart first char
			if (recvbuf[i] == SocketDataStart[0])
			{
				// Check rest
				for (int t = 1; t <= dartStartSize; t++)
				{
					// For each socket data start sequence chars
					if (recvbuf[i + t] != SocketDataStart[t] || recvbuf[i + t] > SOCKETDATABUFFER)
					{
						// Stop checking if it's different
						keepStartFinding = false;
						i += dartStartSize - 1;
						break;
					}
				}
			}

			i++;
		}

		// For each character (Also seems complicated but it's not)
		for (i; i < SOCKETDATABUFFER; i++)
		{
			// If SocketDataEnd first char
			if (recvbuf[i] == SocketDataEnd[0])
			{
				// Check rest
				for (int t = 1; t <= strlen(SocketDataEnd); t++)
				{
					// For each socket data end sequence chars
					if (recvbuf[i + t] != SocketDataEnd[t] || recvbuf[i + t] > SOCKETDATABUFFER)
					{
						// Stop checking if it's different
						break;
					}
					else
					{
						// Stop
						readNewData = false;
#ifdef _DEBUG
						// Log
						Util::Debug("Recived text: " + totalbuf);
#endif
						// Return what's recived
						return totalbuf.c_str();
					}
				}
			}

			// If not ended
			std::string s (1, recvbuf[i]);
			totalbuf.append(s); 
		}
	}
}

int TCPHandler::HandleErrors()
{
	// Get error
	int error = SocketServerTCP::getSockError();

	// No error
	if (error == 0) return error;

	// Handle errors
	switch (error)
	{
	case 10054:
		Util::Info("Socket 10054: Socket disconnected. Stopping.");
		Stop();
		break;

	case 10038:
		Util::Info("Socket 10038: Some operation was attempted on invalid socket.");
		break;

	default:
		Util::Info("Unhandled socket error: " + std::to_string(error));
		return error;
	}
}


TCPAcceptManager::TCPAcceptManager(SocketServerTCP * srvTCP) : SockSrvTCP(srvTCP)
{
	running = true;
}

TCPAcceptManager::~TCPAcceptManager()
{}


SocketServerTCP::SocketServerTCP(std::string tag, Game * mGame) 
	: SocketServer(tag), game(mGame) {}

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
		if (TcpAcceptManager->SockSrvTCP->game == NULL)
			Util::Debug("SocketServerTCP::AcceptThread(): TcpAcceptManager->SockSrvTCP->game is NULL.");
#endif

		// Connection handler
		TCPHandler * tcpHandler = new TCPHandler(TcpAcceptManager->SockSrvTCP, &acceptSocket, TcpAcceptManager->SockSrvTCP->game);

		// Add to clientTCPHandlers
		TcpAcceptManager->SockSrvTCP->clientTCPHandlers.emplace(tcpHandler, "test");

		// Create thread
		// @TODO Check if thread with name "TCPHandle" doesn't exist already
		tcpHandler->thread = SDL_CreateThread(TCPHandler::TCPHandle, "TCPHandle", tcpHandler);

		// Log successfully connected client.
		Util::Info("Client connected succesfully.");
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

