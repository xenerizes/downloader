#pragma once

#include "lib/data/Buffer.hh"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdexcept>


constexpr int PROTOCOL = 0; // IP
constexpr int BIND_PORT = 6323;
constexpr int CONNECTIONS = 1;
constexpr int RECV_FLAGS = 0;
constexpr int SEND_FLAGS = 0;


class Server {
public:
    Server() : listen_descr_(-1)
             , accept_descr_(-1)
    {
        listen_addr_.sin_family = AF_INET;
        listen_addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        listen_addr_.sin_port = htons(BIND_PORT);

        listen_();
    }

    void accept_(const Buffer& reply) {
        accept_descr_ = accept(listen_descr_, NULL, NULL);

        ssize_t byte_count = 0;
        Buffer buf;
        do {
            byte_count = recv(accept_descr_,
                              (void*) buf.data(),
                              buf.max_size(),
                              RECV_FLAGS);
            send(accept_descr_, reply.data(), reply.size(), SEND_FLAGS);
        } while (byte_count > 0);

        close(accept_descr_);
        close(listen_descr_);
    }

private:
    int listen_descr_;
    int accept_descr_;
    struct sockaddr_in listen_addr_;

    void listen_() {
        listen_descr_ = socket(AF_INET, SOCK_STREAM, PROTOCOL);
        if (listen_descr_ < 0) {
            throw std::runtime_error("Error creating listening socket");
        }

        int bind_result = bind(listen_descr_,
                               (struct sockaddr*) &listen_addr_,
                               sizeof(struct sockaddr_in));

        if (bind_result < 0) {
            close(listen_descr_);
            throw std::runtime_error("Listening socket bind error");
        }

        listen(listen_descr_, CONNECTIONS);
    }
};
