cmake_minimum_required(VERSION 3.6)
project(downloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE CLI_SRC src/cli/*.cpp)
add_library(cli ${CLI_SRC})

file(GLOB_RECURSE LIB_SRC src/lib/*.cpp)
add_library(lib ${LIB_SRC})

add_executable(downloader-cli src/cli/main.cpp)
target_link_libraries(downloader-cli lib cli)

# Tests
add_executable(downloader-test test/main.cpp)
target_link_libraries(downloader-test gtest)
add_subdirectory(third-party/googletest)
