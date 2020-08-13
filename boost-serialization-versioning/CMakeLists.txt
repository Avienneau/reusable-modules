cmake_minimum_required( VERSION 3.0 )
project(boost-serialization-versioning)

find_package( Boost COMPONENTS system REQUIRED )
find_package( Threads )

include_directories( ${Boost_INCLUDE_DIR} . )

set(CMAKE_CXX_STANDARD_17)
add_compile_options(-Wall -std=c++17)
set(SRCS
	main.cpp
	)

add_executable(boost-serialization-versioning ${SRCS})
target_link_libraries(boost-serialization-versioning LINK_PUBLIC ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
boost_serialization
boost_filesystem
boost_system)