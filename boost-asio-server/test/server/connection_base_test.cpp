#include <gtest/gtest.h>

#include "connection.hpp"

using namespace ::testing;



class connection_suite : public Test {
 protected:
  connection_suite() : m_io_service{}, m_socket{m_io_service}, m_sut{std::move(m_socket)} {}
  boost::asio::io_service m_io_service;
  boost::asio::ip::tcp::socket m_socket;
  server::connection m_sut;
};

TEST_F(connection_suite, set_close_handler) {
  m_sut.set_close_handler([]() { });
}

