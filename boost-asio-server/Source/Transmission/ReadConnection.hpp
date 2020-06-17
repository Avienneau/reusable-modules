#ifndef READ_CONNECTION_HPP
#define READ_CONNECTION_HPP

#include "WriteConnection.hpp"

namespace Transmission
{
	class ReadConnection : public WriteConnection
	{
	public:
		ReadConnection(SocketType&& socket)
		: WriteConnection{std::move(socket)},
			m_inputBuffer{},
			m_inputStream{&m_inputBuffer}
		{
			write("Connection is open.\n");
			readFromSocket();
		}

	private:
		void readFromSocket();

		boost::asio::streambuf m_inputBuffer;
		std::istream m_inputStream;
	};
}

#endif