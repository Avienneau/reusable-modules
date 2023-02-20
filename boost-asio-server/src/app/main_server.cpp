#include <iostream>

#include "tcp_server.hpp"

using namespace server;

namespace
{
	const int SERVER_PORT = 5000;
}

int main()
{
  tcp_server my_server(SERVER_PORT);
  my_server.run();

	std::cout << "Program terminated normally." << std::endl;

	return 0;
}
