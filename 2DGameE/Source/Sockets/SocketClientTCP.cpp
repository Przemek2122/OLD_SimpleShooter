#include "SocketClientTCP.h"
#include "SocketDataParser.h"
#include <boost/array.hpp>
#include "Util.h"

using boost::asio::ip::tcp;



SocketClientTCP::SocketClientTCP(std::string tag) : SocketClient(tag)
{

}

SocketClientTCP::~SocketClientTCP()
{}

bool SocketClientTCP::Connect(const char * domain, unsigned short port)
{
	try
	{
		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints =
			resolver.resolve(domain, "daytime");

		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}

		return true;
	}
	catch (std::exception& e)
	{
		Util::Debug(e.what());
		//std::cerr << e.what() << std::endl;
		return false;
	}
}

void SocketClientTCP::Send(const char * data)
{
	
}

char * SocketClientTCP::Recive()
{
	return nullptr;
}
