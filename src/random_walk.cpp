#include "random_walk.hpp"
#include <random>
#include <iostream>
#include <iomanip>

RandomWalk::RandomWalk() : rng(std::random_device{}()) {}

bool RandomWalk::flipCoin() {
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(rng) == 1;
}

int RandomWalk::runTrial(int N) {
    int currentPosition = 0;
    
    for (int i = 0; i < N; ++i) {
        if (flipCoin()) {
            currentPosition++;
        } else {
            currentPosition--;
        }
    }
    
    return currentPosition;
}


SimulationResult RandomWalk::runSimulation(int N, int M) {
    SimulationResult result;
    result.N = N;
    result.M = M;
    result.trials.reserve(M);
    
    for (int trial = 0; trial < M; ++trial) {
        int finalPosition = runTrial(N);
        result.trials.push_back(TrialResult{N, finalPosition});
    }
    
    return result;
}

void RandomWalk::printResults(const SimulationResult& result) {
    std::cout << "\n=== Simulation Results ===" << std::endl;
    std::cout << "Number of steps (N): " << result.N << std::endl;
    std::cout << "Number of trials (M): " << result.M << std::endl;
    
    std::cout << "\nTrial Results:" << std::endl;
    std::cout << std::setw(8) << "Trial" << std::setw(12) << "Final Pos" << std::endl;
    std::cout << std::string(20, '-') << std::endl;
    
    for (size_t i = 0; i < result.trials.size(); ++i) {
        const auto& trial = result.trials[i];
        std::cout << std::setw(8) << (i + 1) 
                  << std::setw(12) << trial.final_position << std::endl;
    }
    
    int sum = 0;
    for (const auto& trial : result.trials) {
        sum += trial.final_position;
    }
    double average = static_cast<double>(sum) / result.trials.size();
    
    std::cout << "\nStatistics:" << std::endl;
    std::cout << "Average final position: " << std::fixed << std::setprecision(2) 
              << average << std::endl;
}