project(server_lib VERSION 1.0.0.0)

find_package(Boost COMPONENTS system REQUIRED)

add_library(server_lib connection_base.cpp connection.cpp tcp_server.cpp)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(server_lib PRIVATE --coverage)
  target_link_options(server_lib PUBLIC --coverage)
  add_custom_command(TARGET server_lib PRE_BUILD COMMAND
                     find ${CMAKE_BINARY_DIR} -type f
                     -name '*.gcda' -exec rm {} +)
endif()

target_link_libraries(server_lib PUBLIC ${Boost_LIBRARIES})
target_include_directories(server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})
target_compile_features(server_lib PUBLIC cxx_std_17)
