project(server_lib VERSION 1.0.0.0)

find_package(Boost COMPONENTS system REQUIRED)

add_library(server_lib connection_base.cpp connection.cpp tcp_server.cpp)

target_link_libraries(server_lib PRIVATE ${Boost_LIBRARIES})
target_include_directories(server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})
target_compile_features(server_lib PUBLIC cxx_std_17)
