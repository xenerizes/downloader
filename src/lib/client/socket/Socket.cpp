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

    int res = connect(descr_, info.info->ai_addr, info.info->ai_addrlen);

    if (-1 == res) {
        close_connection();
        throw std::runtime_error("Error connecting to the socket: " +
                                 socket_error_str(res));
    }
}

void Socket::close_connection()
{
    if (descr_ > 0) {
        close(descr_);
    }
    descr_ = -1;
}

void Socket::send_data(const Buffer& data)
{
    auto res = send(descr_, data.data(), BUFFER_SIZE, SEND_FLAGS);
    if (-1 == res) {
        close_connection();
        throw std::runtime_error("Error sending the data to server: " +
                                 socket_error_str(res));
    }
}

Buffer Socket::read_data()
{
    Buffer buf;
    auto res = recv(descr_, buf.data(), BUFFER_SIZE, RECV_FLAGS);
    if (-1 == res) {
        close_connection();
        throw std::runtime_error("Error receiving the data from server: " +
                                 socket_error_str(res));
    }
    buf.size(res);
    return buf;
}

std::string socket_error_str(ssize_t sock_err)
{
    switch (sock_err) {
        case EACCES:
            return "Permission denied";
        case EAFNOSUPPORT:
            return "Address family or connection type is not supported";
        case ECONNRESET:
            return "Connection reset by peer";
        case ECONNREFUSED:
            return "Connection refused";
        case EINTR:
            return "Interrupted";
        case EINVAL:
            return "Unknown protocol or address family";
        case EMFILE:
        case ENFILE:
            return "The limit on the number of open files reached";
        case ENOBUFS:
            return "Output queue for a network interface is full";
        case ENOMEM:
            return "Could not allocate memory";
        case EPROTONOSUPPORT:
            return "Requested protocol is not supported within domain";
        default:
            return "Error " + std::to_string(sock_err);
    }
}
