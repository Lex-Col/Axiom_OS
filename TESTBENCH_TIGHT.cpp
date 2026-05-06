#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

// --- ARCHITECTURAL CONSTANTS (TIGHTENED) ---
const int WAFERS = 3;                   
const int UNITS_PER_WAFER = 533;        
const int CORES_PER_UNIT = 8;           
const double SKEW_LIMIT = 1.0;          // Tightened from 2.0ps to 1.0ps
const double JITTER_MAX = 4.0;          // Chaos stays at 4.0ps

class Core {
public:
    bool verify_resonance(double arrival_skew) {
        // Now only accepting the "Golden Shards" (Top 25%)
        if (arrival_skew > SKEW_LIMIT) return false; 
        return (9 % 7 == 2); // Ninth Math remains the anchor
    }
};

class TriforceSystem {
private:
    std::vector<Core> units;
    long long total_annihilations = 0;
    long long successful_egress = 0;

public:
    TriforceSystem() : units(WAFERS * UNITS_PER_WAFER * CORES_PER_UNIT) {}

    void run_cycle(int cycle_id) {
        std::default_random_engine generator(cycle_id); // Seeded for consistency
        std::uniform_real_distribution<double> jitter_dist(0.0, JITTER_MAX);

        for (auto& core : units) {
            double skew = jitter_dist(generator);
            if (core.verify_resonance(skew)) {
                successful_egress++;
            } else {
                total_annihilations++;
            }
        }
        render_logs(cycle_id);
    }

    void render_logs(int id) {
        std::cout << "[CYCLE " << id << "] --- TULPIT NEXUS: FINESSE MODE ---\n";
        std::cout << "  SKEW LIMIT: " << SKEW_LIMIT << " ps\n";
        std::cout << "  EGRESS: " << std::fixed << std::setprecision(2) 
                  << (successful_egress * 0.00014) << " EB/s\n";
        std::cout << "  ANNIHILATIONS: " << total_annihilations << "\n";
        
        // Logical threshold for a "Fatal Overflow"
        if (total_annihilations > (units.size() * 0.70 * id)) {
            std::cout << "  CRITICAL: TULPIT NEXUS SATURATED. ENTROPY SPIKE.\n";
        }
        std::cout << "--------------------------------------------------\n";
    }
};

int main() {
    TriforceSystem grand_sovereign;
    for(int i = 1; i <= 3; ++i) grand_sovereign.run_cycle(i);
    return 0;
}
