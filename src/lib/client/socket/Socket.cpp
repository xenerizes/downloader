#include "lib/client/socket/Socket.hh"

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

constexpr int PROTOCOL = 0; // IP
constexpr int RECV_FLAGS = 0;
constexpr int SEND_FLAGS = 0;

Socket::Socket(std::string hostname, std::string port)
    : descr_(-1)
    , host_(std::move(hostname))
    , port_(std::move(port))
    , info_(host_, port_)
{
    descr_ = socket(info_.info->ai_family,
                    info_.info->ai_socktype,
                    info_.info->ai_protocol);
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
    AddrInfo info(host_, port_);

    int connect_res =
        connect(descr_, info.info->ai_addr, info.info->ai_addrlen);

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
