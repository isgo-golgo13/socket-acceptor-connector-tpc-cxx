#include "socket-acceptor.hpp"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

SocketAcceptor::SocketAcceptor(const SocketAddr& addr) {
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = inet_addr(addr.getIp().c_str());
    serverAddr_.sin_port = htons(addr.getPort());
}

SocketAcceptor::~SocketAcceptor() {
    close(serverSocket_);
}

void SocketAcceptor::bind() {
    if (::bind(serverSocket_, (sockaddr*)&serverAddr_, sizeof(serverAddr_)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SocketAcceptor::listen() {
    if (::listen(serverSocket_, 10) < 0) {
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

int SocketAcceptor::acceptConnection() {
    return accept(serverSocket_, nullptr, nullptr);
}
