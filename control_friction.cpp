#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // 1GB block to force massive memory bus saturation
    const size_t size = 1024LL * 1024 * 1024; 
    std::cout << "Control Test Active: Generating Maximum Friction..." << std::endl;

    try {
        std::vector<unsigned char> buffer(size, 0xFF);
        while (true) {
            // Force a full hardware read/write of 1GB every loop
            // This is the "Fire" that Axiom avoids
            std::reverse(buffer.begin(), buffer.end());
            
            // XOR operation to prevent the compiler from optimizing the loop
            buffer[0] ^= buffer[size - 1];
        }
    } catch (...) {
        return 1;
    }
    return 0;
}
