#include "tcp_server.hpp"

using namespace server;

tcp_server::tcp_server(int port)
: m_port{port},
	m_io_service{},
	m_signal_set(m_io_service, SIGINT, SIGTERM),
	m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v6(), port)),
	m_next_socket{m_io_service},
	m_connections{}
{

}

void tcp_server::run()
{			
	m_signal_set.async_wait([this](boost::system::error_code error, int signal) {
		if(error != boost::asio::error::operation_aborted)
		{
			std::cout << "tcp_server received signal (" << signal << ") requesting shutdown." << std::endl;
			shutdown();
		}
	});

	accept();
	std::cout << "tcp_server started. Listening for connections on port " << m_port << "." << std::endl;
	m_io_service.run();
}

void tcp_server::shutdown()
{
	m_acceptor.cancel();
	m_signal_set.cancel();

	for (auto& connection : m_connections)
	{
		connection.close();
	}
}

void tcp_server::accept()
{
	m_acceptor.async_accept(m_next_socket,
		[this](boost::system::error_code error)
		{
			if(!error)
			{
				m_connections.emplace_front(std::move(m_next_socket));
				auto connection = m_connections.begin();

				connection->set_close_handler([this, connection]() {
					m_connections.erase(connection);
					std::cout << "Connection closed. Connection list size: " << m_connections.size() << "." << std::endl;
				});

				std::cout << "Connection accepted. Connection list size: " << m_connections.size() << "." << std::endl;
				accept();
			}

			if(error)
			{
				std::cout << "Error in async_accept. Error code: " << error << ". Error message: " << error.message() << "." << std::endl;
			}
		}
	);
}
