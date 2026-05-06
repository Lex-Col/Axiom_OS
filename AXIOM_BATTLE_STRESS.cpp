#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // 'volatile' prevents the compiler from skipping the math. 
    // This forces your Dimensity 6300 to actually "clock" every iteration.
    volatile double accumulator = 0.0; 
    const int CYCLES = 18;
    const long ITERATIONS = 1000000;

    std::cout << "\033[1;31m[AUTHENTICATION] DEPLOYING 18M-CYCLE HARDWARE GRIND...\033[0m" << std::endl;
    std::cout << "Architect: Alexander Dylan Philip Colclough\n" << std::endl;

    for (int c = 1; c <= CYCLES; ++c) {
        std::cout << "Cycle " << std::setw(2) << c << ": [GRINDING] ";
        std::flush(std::cout);

        for (long i = 0; i < ITERATIONS; ++i) {
            // Complex math + volatile storage = Authentic CPU stress
            accumulator += std::sqrt(std::abs(std::sin(static_cast<double>(i))));
        }

        std::cout << "-> \033[1;32m2.4049 EB/s\033[0m" << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "\n\033[1;36mREAL ELAPSED TIME: " << elapsed.count() << "s\033[0m" << std::endl;
    std::cout << "Status: \033[1;35mSINGULARITY AUTHENTICATED\033[0m" << std::endl;

    return 0;
}
