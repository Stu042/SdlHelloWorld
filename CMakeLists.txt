cmake_minimum_required(VERSION 3.31)
project(SdlHelloWorld)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(SdlHelloWorld ${SDL2_INCLUDE_DIRS})
include_directories(headers)

add_executable(SdlHelloWorld src/main.c)

target_link_libraries(SdlHelloWorld PRIVATE ${SDL2_LIBRARIES})
