cmake_minimum_required(VERSION 3.3)
project(downloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE CLI_SRC src/cli/*.cpp)
add_library(cli ${CLI_SRC})

file(GLOB_RECURSE LIB_SRC src/lib/*.cpp)
add_library(lib ${LIB_SRC})

add_executable(downloader-cli src/cli/main.cpp)
target_link_libraries(downloader-cli cli lib)

# Tests
add_subdirectory(test)
add_subdirectory(third-party/googletest)
