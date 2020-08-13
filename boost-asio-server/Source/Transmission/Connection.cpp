#include "Connection.hpp"

#include <iostream>

using namespace Transmission;

void Connection::readFromSocket()
{
	async_read_until(m_socket, m_inputBuffer, '\n', [this](boost::system::error_code error, std::size_t bytes) {
		if(error)
		{
			std::cout << "async_read_until returned an error." << std::endl;
		}
		else
		{
			std::string line;
			getline(m_inputStream, line);
			//m_proxyService.handleLine(line);
			std::cout << line << std::endl;
			readFromSocket();
			return;
		}
		doneReading();
	});
}