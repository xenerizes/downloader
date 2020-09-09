add_library(cli
    Application.cpp
    Logger.cpp
    Settings.cpp
    )

include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(cli client)

add_executable(downloader main.cpp)
target_link_libraries(downloader cli)
