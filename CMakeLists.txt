cmake_minimum_required(VERSION 3.3)
project(downloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -O0")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
  find_program(GCOVR_EXECUTABLE gcovr)
  if(GCOVR_EXECUTABLE)
    message("-- Found gcovr: ${GCOVR_EXECUTABLE}")
    set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fPIC")
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
endif()

add_subdirectory(src/cli)
add_subdirectory(src/lib)

# Tests
enable_testing()
add_subdirectory(test)
add_subdirectory(third-party/googletest)
