#include "socket-connector.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

constexpr int THREAD_COUNT = 100;  // Number of threads/connections
constexpr auto PAYLOAD = "000000000-1010-Payload";  // Data buffer to send
constexpr int PORT = 8080;

void connectAndSend() {
    SocketAddr addr("127.0.0.1", PORT);
    auto connector = std::make_unique<SocketConnector>(addr);
    
    connector->connect();
    connector->sendData(PAYLOAD);
}

int main() {
    std::vector<std::thread> threads;
    threads.reserve(THREAD_COUNT);

    // Launch 100 threads/connections
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.emplace_back(connectAndSend);
    }

    // Join all threads
    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
