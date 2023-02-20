cmake_minimum_required( VERSION 3.24 )
project(boost-asio-server)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In source builds are not allowed. Please use: cmake -B <build-tree> -S <source-tree>")
endif()

add_subdirectory(src)
