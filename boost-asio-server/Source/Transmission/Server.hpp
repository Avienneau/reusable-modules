#ifndef SERVER_HPP
#define SERVER_HPP

#include <list>
#include <boost/asio.hpp>
#include "Connection.hpp"

namespace Transmission
{
	class Server
	{
	public:
		Server(int port);
		void run();
		void shutdown();

	private:
		void accept();

		int m_port;
		boost::asio::io_service m_io_service;
		boost::asio::signal_set m_signal_set;
		boost::asio::ip::tcp::acceptor m_acceptor;
		boost::asio::ip::tcp::socket m_nextSocket;
		
		std::list<Connection> m_connections;
	};
}

#endif