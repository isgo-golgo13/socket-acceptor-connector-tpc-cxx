#include "socket-connector.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <memory>

constexpr int SESSION_COUNT = 1;  // Number of connections
constexpr auto PAYLOAD = "Payload-00000000000000001";  // Data to send
constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;

int main() {
    for (int i = 0; i < SESSION_COUNT; ++i) {
        // Create and connect SocketConnector
        SocketAddr addr("127.0.0.1", PORT);
        SocketConnector connector(addr);
        connector.connect();

        // Send data
        connector.sendData(PAYLOAD, strlen(PAYLOAD));

        // Receive response
        char buffer[BUFFER_SIZE];
        connector.recvData(buffer, sizeof(buffer));
        std::cout << "Received from server: " << buffer << std::endl;
    }

    return 0;
}
