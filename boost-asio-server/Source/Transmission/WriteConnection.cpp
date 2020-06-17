#include "WriteConnection.hpp"

using namespace Transmission;

void WriteConnection::writeToSocket()
{
	// If a write is currently happening...
	if(m_awaitingWrite)
	{
		// Alert the async_write's completion handler
		// that writeToSocket was called while async_write was busy
		// and that there is more to be written to the socket.
		m_pendingWrites = true;
		return;
	}

	// Otherwise, notify subsequent calls to this function that we're writing
	m_awaitingWrite = true;

	// Swap the buffers and stream pointers, so that subsequent writeToSockets
	// go into the clear/old/unused buffer
	std::swap(m_outputBufferPointer, m_writeBufferPointer);
	std::swap(m_outputStreamPointer, m_writeStreamPointer);


	// Kick off your async write, sending the front buffer.
	async_write(m_socket, *m_writeBufferPointer, [this](boost::system::error_code error, std::size_t){

		// The write has completed
		m_awaitingWrite = false;

		// If there was an error, report it.
		if(error)
		{
			std::cout << "Async write returned an error." << std::endl;
		}
		else if(m_pendingWrites) // If there are more pending writes
		{
			// Write them
			writeToSocket();
			m_pendingWrites = false;
			return;
		}

		if(!m_reading)
		{
			m_closeHandler();
		}
	});

	return;
}