#pragma once

#include <boost/asio.hpp>
#include <iostream>

namespace server {
class connection_base {
 public:
  using socket_type = boost::asio::ip::tcp::socket;
  using close_handler = std::function<void()>;

  template <typename T>
  void write(const T& output) {
    *m_output_stream_pointer << output;
    write_to_socket();
  }

  template <typename T>
  std::ostream& operator<<(const T& output) {
    write(output);
    m_pending_writes = true;
    return *m_output_stream_pointer;
  }

  std::ostream& get_output_stream() {
    write_to_socket();
    m_pending_writes = true;
    return *m_output_stream_pointer;
  }

  socket_type& get_socket() { return m_socket; }

  template <typename Handler>
  void set_close_handler(Handler&& closeHandler) {
    m_close_handler = std::forward<Handler>(closeHandler);
  }

  void close() { m_socket.shutdown(socket_type::shutdown_receive); }

 protected:
  explicit connection_base(socket_type&& socket)
      : m_socket{std::move(socket)},
        m_output_buffer{},
        m_write_buffer{},
        m_output_stream{&m_output_buffer},
        m_write_stream{&m_write_buffer},
        m_output_stream_pointer{&m_output_stream},
        m_write_stream_pointer{&m_write_stream},
        m_output_buffer_pointer{&m_output_buffer},
        m_write_buffer_pointer{&m_write_buffer},
        m_reading{true},
        m_awaiting_write{false},
        m_pending_writes{false},
        m_close_handler{} {}

  void done_reading() {
    m_reading = false;
    write_to_socket();
  }

  socket_type m_socket;

 private:
  void write_to_socket();

  boost::asio::streambuf m_output_buffer;
  boost::asio::streambuf m_write_buffer;

  std::ostream m_output_stream;
  std::ostream m_write_stream;

  std::ostream* m_output_stream_pointer;
  std::ostream* m_write_stream_pointer;

  boost::asio::streambuf* m_output_buffer_pointer;
  boost::asio::streambuf* m_write_buffer_pointer;

  bool m_reading;
  bool m_awaiting_write;
  bool m_pending_writes;

  close_handler m_close_handler;
};
}  // namespace server

