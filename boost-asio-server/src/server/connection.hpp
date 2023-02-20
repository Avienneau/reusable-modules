#pragma once
#include "connection_base.hpp"

namespace server {
class connection : public connection_base {
 public:
  connection(socket_type&& socket)
      : connection_base{std::move(socket)},
        m_input_buffer{},
        m_input_stream{&m_input_buffer} {
    write("Connection is open.\n");
    read_from_socket();
  }

 private:
  void read_from_socket();

  boost::asio::streambuf m_input_buffer;
  std::istream m_input_stream;
};
}  // namespace server
