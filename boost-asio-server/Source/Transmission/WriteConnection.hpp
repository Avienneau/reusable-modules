#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <boost/asio.hpp>

namespace Transmission
{
	class WriteConnection
	{
	public:
		using SocketType = boost::asio::ip::tcp::socket;
		using CloseHandler = std::function<void()>;

		template<typename T>
		void write(const T& output)
		{
			*m_outputStreamPointer << output;
			writeToSocket();
		}

		template<typename T>
		std::ostream& operator<<(const T& output)
		{
			write(output);
			m_pendingWrites = true;
			return *m_outputStreamPointer;
		}

		std::ostream& getOutputStream()
		{
			writeToSocket();
			m_pendingWrites = true;
			return *m_outputStreamPointer;
		}

		SocketType& getSocket() { return m_socket; }

		template<typename Handler>
		void setCloseHandler(Handler&& closeHandler)
		{
			m_closeHandler = std::forward<Handler>(closeHandler);
		}

		void close()
		{
			m_socket.shutdown(SocketType::shutdown_receive);
		}
	protected:
		explicit WriteConnection(SocketType&& socket)
		: m_socket{std::move(socket)},
			m_outputBuffer{},
			m_writeBuffer{},
			m_outputStream{&m_outputBuffer},
			m_writeStream{&m_writeBuffer},
			m_outputStreamPointer{&m_outputStream},
			m_writeStreamPointer{&m_writeStream},
			m_outputBufferPointer{&m_outputBuffer},
			m_writeBufferPointer{&m_writeBuffer},
			m_reading{true},
			m_awaitingWrite{false},
			m_pendingWrites{false},
			m_closeHandler{}
		{

		}

		void doneReading()
		{
			m_reading = false;
			writeToSocket();
		}

		SocketType m_socket;

	private:
		void writeToSocket();

		boost::asio::streambuf m_outputBuffer;
		boost::asio::streambuf m_writeBuffer;

		std::ostream m_outputStream;
		std::ostream m_writeStream;

		std::ostream* m_outputStreamPointer;
		std::ostream* m_writeStreamPointer;

		boost::asio::streambuf* m_outputBufferPointer;
		boost::asio::streambuf* m_writeBufferPointer;

		bool m_reading;
		bool m_awaitingWrite;
		bool m_pendingWrites;

		CloseHandler m_closeHandler;
	};
}

#endif