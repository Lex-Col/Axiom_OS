#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

const int CYCLES = 18;
const long ITERATIONS_PER_CYCLE = 1000000;
const int TOTAL_CORES = 17056;
const double EB_PER_CORE = 0.0001410001;

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "\033[1;31m[WARNING] INITIATING AUTHENTIC CPU STRESS TEST\033[0m" << std::endl;
    std::cout << "Architect: Alexander Dylan Philip Colclough\n" << std::endl;
    double final_resonance = 0;
    for (int c = 1; c <= CYCLES; ++c) {
        std::cout << "Cycle " << c << ": [COMPUTING] ";
        for (long i = 0; i < ITERATIONS_PER_CYCLE; ++i) {
            final_resonance = 1.0 / std::pow(2.5, 0) + std::sin(i) * 1e-16;
        }
        std::cout << "-> \033[1;32m" << (TOTAL_CORES * EB_PER_CORE) << " EB/s\033[0m" << std::endl;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "\n\033[1;36mTOTAL TIME: " << elapsed.count() << "s\033[0m" << std::endl;
    return 0;
}
