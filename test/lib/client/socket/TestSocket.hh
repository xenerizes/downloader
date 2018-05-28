#pragma once

#include "lib/client/socket/Socket.hh"
#include "server/Server.hh"

TEST(Socket, SendAndReceiveMessage) {
    Server server;
    Buffer message = { "Privet!" };
    server.accept_(message);

    Socket client_socket("localhost", BIND_PORT);
    Buffer request = { "Hello" };
    client_socket.send(request);

    auto received = client_socket.read();
    ASSERT_EQ(message, received);
}
