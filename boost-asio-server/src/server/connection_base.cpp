#include "connection_base.hpp"

using namespace server;

void connection_base::write_to_socket() {
  // If a write is currently happening...
  if (m_awaiting_write) {
    // Alert the async_write's completion handler
    // that write_to_socket was called while async_write was busy
    // and that there is more to be written to the socket.
    m_pending_writes = true;
    return;
  }

  // Otherwise, notify subsequent calls to this function that we're writing
  m_awaiting_write = true;

  // Swap the buffers and stream pointers, so that subsequent write_to_sockets
  // go into the clear/old/unused buffer
  std::swap(m_output_buffer_pointer, m_write_buffer_pointer);
  std::swap(m_output_stream_pointer, m_write_stream_pointer);

  // Kick off your async write, sending the front buffer.
  async_write(
      m_socket, *m_write_buffer_pointer,
      [this](boost::system::error_code error, std::size_t) {
        // The write has completed
        m_awaiting_write = false;

        // If there was an error, report it.
        if (error) {
          std::cout << "Async write returned an error." << std::endl;
        } else if (m_pending_writes)  // If there are more pending writes
        {
          // Write them
          write_to_socket();
          m_pending_writes = false;
          return;
        }

        if (!m_reading) {
          m_close_handler();
        }
      });

  return;
}
