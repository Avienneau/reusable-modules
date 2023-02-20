#include "connection.hpp"

#include <iostream>

using namespace server;

void connection::read_from_socket() {
  async_read_until(m_socket, m_input_buffer, '\n',
                   [this](boost::system::error_code error, std::size_t bytes) {
                     if (error) {
                       std::cout << "async_read_until returned an error."
                                 << std::endl;
                     } else {
                       std::string line;
                       getline(m_input_stream, line);
                       // m_proxyService.handleLine(line);
                       std::cout << line << std::endl;
                       read_from_socket();
                       return;
                     }
                     done_reading();
                   });
}
