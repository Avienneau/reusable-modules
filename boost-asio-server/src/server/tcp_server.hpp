#pragma once

#include <boost/asio.hpp>
#include <list>

#include "connection.hpp"

namespace server {
class tcp_server {
 public:
  tcp_server(int port);
  void run();
  void shutdown();

 private:
  void accept();

  int m_port;
  boost::asio::io_service m_io_service;
  boost::asio::signal_set m_signal_set;
  boost::asio::ip::tcp::acceptor m_acceptor;
  boost::asio::ip::tcp::socket m_next_socket;

  std::list<connection> m_connections;
};
}  // namespace server

