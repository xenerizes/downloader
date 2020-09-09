add_library(test-helpers helpers.cpp)

add_executable(downloader-test
    cli/TestCLI.cpp
    lib/TestBuffer.cpp
    lib/TestDownload.cpp
    lib/TestHeader.cpp
    lib/TestUrlParser.cpp
    lib/TestWriter.cpp
    )

target_link_libraries(downloader-test gtest_main test-helpers cli client)
target_include_directories(downloader-test PRIVATE
    ${PROJECT_SOURCE_DIR}/third-party/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/test
    )

add_test(downloader-test downloader-test)
