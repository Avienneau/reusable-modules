#include <iostream>

#include "Transmission/Server.hpp"

using namespace Transmission;

namespace
{
	const int SERVER_PORT = 5000;
}

int main()
{
	Server server(SERVER_PORT);
	server.run();

	std::cout << "Program terminated normally." << std::endl;

	return 0;
}