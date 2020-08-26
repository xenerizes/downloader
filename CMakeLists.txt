cmake_minimum_required(VERSION 3.3)
project(downloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories(include)

file(GLOB_RECURSE CLI_SRC src/cli/*.cpp)
add_library(cli ${CLI_SRC})

file(GLOB_RECURSE LIB_SRC src/lib/*.cpp)
add_library(lib ${LIB_SRC})

add_executable(downloader-cli src/cli/main.cpp)
target_link_libraries(downloader-cli cli lib)

find_program(GCOVR_EXECUTABLE gcovr)
if(GCOVR_EXECUTABLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage -fPIC -O0")
  add_custom_target(cov
      COMMAND
      ${GCOVR_EXECUTABLE}
      --root=${PROJECT_SOURCE_DIR}
      --filter=${PROJECT_SOURCE_DIR}/include
      --filter=${PROJECT_SOURCE_DIR}/src
      --object-directory=${PROJECT_BINARY_DIR}
      --delete
      --html
      --html-details
      --output=${PROJECT_BINARY_DIR}/coverage.html
      --print-summary
      )
endif()

# Tests
add_subdirectory(test)
add_subdirectory(third-party/googletest)
