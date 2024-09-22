#include "socket-connector.hpp"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

SocketConnector::SocketConnector(const SocketAddr& addr) {
    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = inet_addr(addr.getIp().c_str());
    serverAddr_.sin_port = htons(addr.getPort());
}

SocketConnector::~SocketConnector() {
    close(clientSocket_);
}

void SocketConnector::connect() {
    if (::connect(clientSocket_, (sockaddr*)&serverAddr_, sizeof(serverAddr_)) < 0) {
        std::cerr << "Connect failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SocketConnector::sendData(const std::string& data) {
    send(clientSocket_, data.c_str(), data.size(), 0);
}
