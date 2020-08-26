file(GLOB_RECURSE TEST_SOURCES *.cpp)
add_executable(downloader-test ${TEST_SOURCES})
target_link_libraries(downloader-test gtest_main lib)
target_include_directories(downloader-test PRIVATE
    third-party/googletest/googletest/include)
