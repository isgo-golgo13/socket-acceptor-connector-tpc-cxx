#pragma once

#include "socket-addr.hpp"
#include "socket.hpp"
#include <sys/socket.h>

class SocketConnector {
public:
    explicit SocketConnector(const SocketAddr& addr);
    SocketConnector() = delete;
    SocketConnector(const SocketConnector& other) = delete;
    SocketConnector(SocketConnector&& other) noexcept = default;
    SocketConnector& operator=(const SocketConnector& other) = delete;
    SocketConnector& operator=(SocketConnector&& other) noexcept = default;
    ~SocketConnector() = default;

    void connect();
    std::unique_ptr<Socket> getSocket();
    void sendData(const void* buffer, size_t length);
    void recvData(void* buffer, size_t length);

private:
    int clientSocket_;
    SocketAddr serverAddr_;
    std::unique_ptr<Socket> socket_;  // Use Socket class
};
