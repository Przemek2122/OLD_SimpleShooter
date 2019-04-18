#pragma once
#include <string>
#include <boost/asio.hpp>
#ifdef _DEBUG
#define BOOST_ASIO_ENABLE_BUFFER_DEBUGGING
#else
#define BOOST_ASIO_DISABLE_BUFFER_DEBUGGING
#endif

class Socket
{
public:
	Socket(std::string tag) : SocketTag(tag) {}
	~Socket();

	std::string SocketTag;

};
