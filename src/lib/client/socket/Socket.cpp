#include "lib/client/socket/Socket.hh"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

constexpr int PROTOCOL = 0; // IP
constexpr int RECV_FLAGS = 0;
constexpr int SEND_FLAGS = 0;

Socket::Socket(const std::string& hostname, int port)
    : descr_(-1)
    , host_(hostname)
    , port_(port)
{
    descr_ = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    if (descr_ < 0) {
        throw std::runtime_error("Error creating socket");
    }

    make_connection();
}

Socket::~Socket()
{
    close(descr_);
}

void Socket::make_connection()
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(port_);

    int connect_res =
        connect(descr_, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if (connect_res < 0) {
        throw std::runtime_error("Error connecting to given socket");
    }
}

void Socket::send_data(const Buffer& data)
{
    send(descr_, data.data(), data.size(), SEND_FLAGS);
}

Buffer Socket::read_data()
{
    Buffer buf;
    recv(descr_, buf.data(), BUFFER_SIZE, RECV_FLAGS);
    return buf;
}
