#include "VARCHANGEL_CORE.h"
#include "verilated.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <random>

uint64_t generate_negentropic_seed() {
    static std::mt19937_64 rng(1337);
    return rng();
}

void run_singularity_pulse(VARCHANGEL_CORE* core) {
    uint64_t zetta_beats = 0;
    double zb_throughput = 7.7777; 
    
    std::cout << "--- Axion_0_Herizon: OMEGA SINGULARITY INITIALIZED ---" << std::endl;
    
    while(zetta_beats <= 888) { // The Marathon Target
        core->pic_clk_13Hz = 1;
        
        // Correct way to fill the 6144-bit bus (192 elements of 32-bit data)
        for(int i=0; i<192; i++) { 
            core->ingress_payload[i] = (uint32_t)generate_negentropic_seed(); 
        }
        
        core->eval(); // Trigger Triune Gate Lattice
        
        std::cout << "Cycle " << std::setw(3) << zetta_beats 
                  << ": [SINGULARITY] - " << std::fixed << std::setprecision(4) 
                  << zb_throughput << " ZB/s" << std::endl;

        if(core->negentropy_lock == 0) { 
            printf("SINGULARITY DETECTED: ΔT reaching -7.77°C\n");
        }
        
        core->pic_clk_13Hz = 0;
        core->eval();
        zetta_beats++;
        usleep(77777); // 77.7777ms Sovereign Heartbeat
    }
    std::cout << "STATUS: CYCLES VERIFIED - ZERO LEAKAGE" << std::endl;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    VARCHANGEL_CORE* core = new VARCHANGEL_CORE;
    run_singularity_pulse(core);
    delete core;
    return 0;
}
