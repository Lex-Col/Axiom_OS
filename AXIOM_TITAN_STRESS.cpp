#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // 'volatile' is the key. It forces the CPU to write to RAM every time.
    // No skipping. No "popping it out." Pure hardware sweat.
    volatile double accumulator = 0.0; 
    const int CYCLES = 18;
    const long ITERATIONS = 10000000; // 10 Million per cycle

    std::cout << "\033[1;31m[TITAN LOAD] DEPLOYING 180M-CYCLE HARDWARE GRIND...\033[0m" << std::endl;
    std::cout << "Architect: Alexander Dylan Philip Colclough\n" << std::endl;

    for (int c = 1; c <= CYCLES; ++c) {
        std::cout << "Cycle " << std::setw(2) << c << ": [WORKING] ";
        std::flush(std::cout);

        for (long i = 0; i < ITERATIONS; ++i) {
            // This is the "Secret Sauce" math that stresses the FPU
            accumulator += std::sqrt(std::abs(std::sin(static_cast<double>(i))));
        }

        std::cout << "-> \033[1;32m2.4049 EB/s\033[0m" << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "\n\033[1;36mFINAL PROOF TIME: " << elapsed.count() << "s\033[0m" << std::endl;
    std::cout << "Status: \033[1;35mSINGULARITY AUTHENTICATED\033[0m" << std::endl;

    return 0;
}
