#pragma once

#include <vector>
#include <random>

struct TrialResult {
    int steps;
    int final_position;
};

struct SimulationResult {
    int N;
    int M;
    std::vector<TrialResult> trials;
};

class RandomWalk {
private:
    std::mt19937 rng;
    
public:
    RandomWalk();
    
    bool flipCoin();
    
    int runTrial(int N);
    
    SimulationResult runSimulation(int N, int M);
    
    void printResults(const SimulationResult& result);
};