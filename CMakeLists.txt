cmake_minimum_required(VERSION 3.6)
project(downloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
set(SOURCE_DIR src)

add_executable(downloader ${SOURCE_DIR}/main.cpp)
