#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include "thread.hpp"
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>

constexpr int PORT = 8080;  // Port for server to listen on
constexpr int BUFFER_SIZE = 1024;  // Buffer size for receiving data

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        std::cout << "Received data: " << std::string(buffer, bytesRead) << std::endl;
    }

    close(clientSocket);
}

int main() {
    SocketAddr addr("127.0.0.1", PORT);
    auto acceptor = std::make_unique<SocketAcceptor>(addr);

    acceptor->bind();
    acceptor->listen();

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        int clientSocket = acceptor->acceptConnection();
        
        // Create a thread to handle the client
        auto thread = std::make_unique<Thread>([clientSocket]() {
            handleClient(clientSocket);
        });
        
        thread->start();
        thread->join();  // Join immediately to avoid race conditions
    }

    return 0;
}
