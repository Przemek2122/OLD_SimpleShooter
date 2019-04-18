#include "SocketServerTCP.h"
#include "Util.h"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


using boost::asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

SocketServerTCP::SocketServerTCP(std::string tag) : SocketServer(tag)
{}

SocketServerTCP::~SocketServerTCP()
{

}

bool SocketServerTCP::Listen(unsigned short port)
{
	try
	{
		Util::Debug("Should start listening at port: " + std::to_string(port));

		boost::asio::io_context io_context;

		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

		for (;;)
		{
			tcp::socket socket(io_context);
			acceptor.accept(socket);

			std::string message = make_daytime_string();

			Util::Debug("Something accepted.");

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}

		return true;
	}
	catch (std::exception& e)
	{
		Util::Error(e.what());
		//std::cerr << e.what() << std::endl;
		return false;
	}
	
	return false;
}

void SocketServerTCP::Send(char * data)
{
	
}

char * SocketServerTCP::Recive()
{


	return nullptr;
}
