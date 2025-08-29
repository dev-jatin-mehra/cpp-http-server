cmake_minimum_required(VERSION 3.10)
project(cpp-http-server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

add_executable(cpp-http-server
    src/main.cpp
    src/http_server.cpp
)

target_link_libraries(cpp-http-server curl)