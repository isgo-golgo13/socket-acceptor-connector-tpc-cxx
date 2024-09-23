#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <thread>
#include <string>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

void handleClient(int clientSocket, SocketAcceptor& acceptor) {
    std::vector<char> buffer(BUFFER_SIZE);

    // Receive data from the client
    acceptor.recvData(clientSocket, buffer);
    std::cout << "Received: " << std::string(buffer.data(), buffer.size()) << std::endl;

    // Send response using std::string
    std::string response_str = "ACK of received data!";
    std::vector<char> response(response_str.begin(), response_str.end());
    acceptor.sendData(clientSocket, response);

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
