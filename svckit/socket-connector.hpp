#pragma once

#include "socket-addr.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>

class SocketConnector {
public:
    explicit SocketConnector(const SocketAddr& addr);
    SocketConnector() = delete;
    SocketConnector(const SocketConnector& other) = delete;
    SocketConnector(SocketConnector&& other) noexcept = default;
    SocketConnector& operator=(const SocketConnector& other) = delete;
    SocketConnector& operator=(SocketConnector&& other) noexcept = default;
    ~SocketConnector();

    void connect();
    void sendData(const std::string& data);

private:
    int clientSocket_;
    sockaddr_in serverAddr_;
};
