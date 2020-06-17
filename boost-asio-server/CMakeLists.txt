cmake_minimum_required( VERSION 3.0 )
project(boost-asio-server)

find_package( Boost COMPONENTS system REQUIRED )
find_package( Threads )

include_directories( ${Boost_INCLUDE_DIR} . )

set(CMAKE_CXX_STANDARD_17)
add_compile_options(-Wall -std=c++17)
set(SRCS
	Source/main.cpp
	Source/Transmission/WriteConnection.cpp
	Source/Transmission/ReadConnection.cpp
	Source/Transmission/Server.cpp
	)

add_executable(boost-asio-server ${SRCS})
target_link_libraries(boost-asio-server LINK_PUBLIC ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})