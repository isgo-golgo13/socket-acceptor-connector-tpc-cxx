#pragma once

#include "socket-addr.hpp"
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>

class SocketAcceptor {
public:
    explicit SocketAcceptor(const SocketAddr& addr);
    SocketAcceptor() = delete;
    SocketAcceptor(const SocketAcceptor& other) = delete;
    SocketAcceptor(SocketAcceptor&& other) noexcept = default;
    SocketAcceptor& operator=(const SocketAcceptor& other) = delete;
    SocketAcceptor& operator=(SocketAcceptor&& other) noexcept = default;
    ~SocketAcceptor();

    void bind();
    void listen();
    int acceptConnection();

private:
    int serverSocket_;
    sockaddr_in serverAddr_;
};
