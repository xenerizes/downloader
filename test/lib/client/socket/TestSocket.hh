#pragma once

#include "lib/client/socket/Socket.hh"
#include "server/Server.hh"

#include <unistd.h>


TEST(Socket, SendAndReceiveMessage) {
    Server server;
    Buffer message = { "Privet!" };

    auto pid = fork();
    if (pid == 0 ) {
        server.accept_(message);
    }
    if (pid > 0) {
        Socket client_socket("localhost", "6323");
        Buffer request = {"Hello"};
        client_socket.send_data(request);

        auto received = client_socket.read_data();
        ASSERT_EQ(message, received);
    }
}
