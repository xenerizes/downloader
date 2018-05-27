cmake_minimum_required(VERSION 3.6)
project(downloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE APP_SRC src/application/*.cpp)
add_library(app ${APP_SRC})

file(GLOB_RECURSE LDR_SRC src/loader/*.cpp)
#add_library(loader ${LDR_SRC})

file(GLOB_RECURSE WRT_SRC src/writer/*.cpp)
#add_library(writer ${WRT_SRC})

add_executable(downloader src/main.cpp)
target_link_libraries(downloader app)