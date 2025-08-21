#ifndef RANDOM_WALK_HPP
#define RANDOM_WALK_HPP

#include <vector>
#include <random>
#include <iostream>
#include <climits>
#include <cmath>

struct SimulationResult {
    int steps;
    int trials;
    std::vector<int> finalPositions;
    double meanPosition;
    double meanSquareDisplacement;
    double standardDeviation;
    int maxPosition;
    int minPosition;
};

class RandomWalk {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    RandomWalk() : gen(rd()), dis(0, 1) {}

    SimulationResult runSimulation(int steps, int trials) {
        SimulationResult result;
        result.steps = steps;
        result.trials = trials;
        result.finalPositions.reserve(trials);

        double sumPositions = 0.0;
        double sumSquarePositions = 0.0;
        int maxPos = INT_MIN;
        int minPos = INT_MAX;

        for (int trial = 0; trial < trials; ++trial) {
            int position = 0;
            
            for (int step = 0; step < steps; ++step) {
                position += (dis(gen) == 0) ? -1 : 1;
            }
            
            result.finalPositions.push_back(position);
            sumPositions += position;
            sumSquarePositions += position * position;
            
            maxPos = std::max(maxPos, position);
            minPos = std::min(minPos, position);
        }

        result.meanPosition = sumPositions / trials;
        result.meanSquareDisplacement = sumSquarePositions / trials;
        result.maxPosition = maxPos;
        result.minPosition = minPos;
        
        double variance = result.meanSquareDisplacement - (result.meanPosition * result.meanPosition);
        result.standardDeviation = std::sqrt(variance);

        return result;
    }

    void printResults(const SimulationResult& result) {
        std::cout << "Results for N=" << result.steps << " steps, M=" << result.trials << " trials:" << std::endl;
        std::cout << "  Mean final position: " << result.meanPosition << std::endl;
        std::cout << "  Mean square displacement: " << result.meanSquareDisplacement << std::endl;
        std::cout << "  Standard deviation: " << result.standardDeviation << std::endl;
        std::cout << "  Range: [" << result.minPosition << ", " << result.maxPosition << "]" << std::endl;
        std::cout << "  Theoretical std dev: " << std::sqrt(result.steps) << std::endl;
    }
};

#endif // RANDOM_WALK_HPP