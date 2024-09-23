#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

void handleClient(int clientSocket, SocketAcceptor& acceptor) {
    char buffer[BUFFER_SIZE];

    // Receive data from the client
    acceptor.recvData(clientSocket, buffer, sizeof(buffer));
    std::cout << "Received: " << buffer << std::endl;

    // Send response to the client
    const char* response = "ACK of received data for Client!";
    acceptor.sendData(clientSocket, response, strlen(response));

    close(clientSocket);  // Close the connection after handling
}

int main() {
    SocketAddr addr("0.0.0.0", PORT);
    SocketAcceptor acceptor(addr);

    acceptor.bind();
    acceptor.listen();

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        int clientSocket = acceptor.acceptConnection();
        if (clientSocket < 0) continue;

        // Handle each client in a separate thread
        std::thread([clientSocket, &acceptor]() {
            handleClient(clientSocket, acceptor);
        }).detach();
    }

    return 0;
}
