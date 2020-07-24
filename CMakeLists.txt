cmake_minimum_required(VERSION 3.3)
project(downloader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE CLI_SRC src/cli/*.cpp)
add_library(cli ${CLI_SRC})

file(GLOB_RECURSE LIB_SRC src/lib/*.cpp)
add_library(lib ${LIB_SRC})

add_executable(downloader-cli src/cli/main.cpp)
target_link_libraries(downloader-cli cli lib)

# Tests
add_executable(downloader-test test/main.cpp)
target_link_libraries(downloader-test gtest lib)
target_include_directories(downloader-test PRIVATE
    third-party/googletest/googletest/include)
add_subdirectory(third-party/googletest)
