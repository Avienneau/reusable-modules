project(tcp_server VERSION 1.0.0.0)

add_executable(tcp_server main_server.cpp)
target_link_libraries(tcp_server PRIVATE server_lib)
