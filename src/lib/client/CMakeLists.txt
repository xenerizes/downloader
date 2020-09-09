include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(socket
    socket/AddrInfo.cpp
    socket/Socket.cpp)

target_link_libraries(socket buffer)

add_library(client
    url/Scheme.cpp
    url/UrlParser.cpp
    http/HttpClient.cpp
    http/Response.cpp
    http/HttpHeader.cpp
    http/header/PropertyIterator.cpp
    http/header/HeaderProperty.cpp
    http/header/CodeProperty.cpp
    http/header/ContentLengthProperty.cpp
    http/header/EmptyProperty.cpp
    )

target_link_libraries(client socket writer)
