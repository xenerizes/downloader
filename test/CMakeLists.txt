add_executable(downloader-test
    lib/TestBuffer.cpp
    lib/TestCLI.cpp
    lib/TestDownload.cpp
    lib/TestHeader.cpp
    lib/TestUrlParser.cpp
    lib/TestWriter.cpp
    )

target_link_libraries(downloader-test gtest_main cli client)
target_include_directories(downloader-test PRIVATE
    ${PROJECT_SOURCE_DIR}/third-party/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/include
    )

add_test(downloader-test downloader-test)
