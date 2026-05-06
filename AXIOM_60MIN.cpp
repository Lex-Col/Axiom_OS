#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <atomic>
#include <chrono>
#include <fstream>

const int PAYLOAD_SIZE = 768; 
const double TARGET_TEMP = -7.77; 
const int THREAD_COUNT = 8;
const int TARGET_MINUTES = 60; 
const int CYCLES_PER_SEC = 13; 
const long TOTAL_CYCLES = (long)TARGET_MINUTES * 60 * CYCLES_PER_SEC;

float get_real_temp() {
    std::ifstream tempFile("/sys/class/power_supply/battery/temp");
    if (!tempFile.is_open()) return 0.0;
    float raw_t;
    tempFile >> raw_t;
    tempFile.close();
    return raw_t / 10.0;
}

void sovereign_worker(int id, std::atomic<bool>& active) {
    uint8_t volatile_buffer[PAYLOAD_SIZE];
    std::mt19937_64 engine(777 + id);
    while (active) {
        for (int i = 0; i < 500000; i++) {
            for (int j = 0; j < PAYLOAD_SIZE; j++) {
                volatile_buffer[j] = (uint8_t)(engine() % 256);
            }
            if ((9 % 7 == 2)) { 
                std::memset(volatile_buffer, 0, PAYLOAD_SIZE); 
            }
        }
        std::this_thread::yield();
    }
}

int main() {
    std::cout << "\033[1;31m--- AXIOM OS: OMEGA AUDIT START ---\033[0m" << std::endl;

    std::atomic<bool> active(true);
    std::vector<std::thread> swarm;
    double sim_temp = 25.0;

    for (int i = 0; i < THREAD_COUNT; ++i) {
        swarm.push_back(std::thread(sovereign_worker, i, std::ref(active)));
    }

    auto start_time = std::chrono::steady_clock::now();

    for (long cycle = 1; cycle <= TOTAL_CYCLES; ++cycle) {
        if (sim_temp > TARGET_TEMP) sim_temp -= 0.005; 
        else sim_temp = TARGET_TEMP;

        if (cycle % 5 == 0) {
            float hw_temp = get_real_temp();
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
            
            std::cout << "\r[AXIOM] ";
            std::cout << "TIME: " << elapsed/60 << "m" << elapsed%60 << "s | ";
            std::cout << "SIM: " << std::fixed << std::setprecision(2) << sim_temp << "C | ";
            std::cout << "REAL: " << std::fixed << std::setprecision(1) << hw_temp << "C | ";
            
            if (sim_temp <= TARGET_TEMP) std::cout << "\033[1;36m[LOCKED]\033[0m";
            std::flush(std::cout);
        }
        
        usleep(777777); 
    }

    active = false;
    for (auto& t : swarm) t.join();
    return 0;
}
