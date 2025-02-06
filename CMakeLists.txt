cmake_minimum_required(VERSION 3.31)
project(SdlHelloWorld)

set(CMAKE_C_STANDARD 11)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL2)


include_directories(SdlHelloWorld ${SDL2_INCLUDE_DIRS})
include_directories(headers)

add_executable(SdlHelloWorld src/main.c)

target_link_libraries(SdlHelloWorld PRIVATE SDL2::SDL2)
