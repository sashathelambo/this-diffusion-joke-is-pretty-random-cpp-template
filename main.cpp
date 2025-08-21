#include <iostream>
#include <vector>

#include "random_walk.hpp"

int main() {
    std::cout << "One-Dimensional Random Walk Simulation" << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "Note: For performance benchmarks, run: ./random_walk_test [benchmark]" << std::endl;
    
    RandomWalk simulator;
    
    std::vector<int> stepValues = {10, 50, 100, 500, 1000};
    const int trials = 10;
    
    for (int N : stepValues) {
        std::cout << "\nRunning simulation with N=" << N << " steps, M=" << trials << " trials..." << std::endl;
        
        SimulationResult result = simulator.runSimulation(N, trials);
        simulator.printResults(result);
        
        std::cout << std::string(50, '=') << std::endl;
    }
    
    return 0;
}
