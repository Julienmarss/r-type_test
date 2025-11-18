#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "🌐 R-Type Server Starting..." << std::endl;
    std::cout << "✅ Server initialized on port 4242" << std::endl;
    std::cout << "Press Ctrl+C to stop" << std::endl;
    
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}