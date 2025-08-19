#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "../src/random_walk.hpp"

TEST_CASE("RandomWalk coin flip produces boolean values", "[RandomWalk]") {
    RandomWalk rw;
    
    bool heads = false, tails = false;
    
    for (int i = 0; i < 100; ++i) {
        bool result = rw.flipCoin();
        if (result) {
            heads = true;
        } else {
            tails = true;
        }
        
        if (heads && tails) break;
    }
    
    REQUIRE(heads);
    REQUIRE(tails);
}

TEST_CASE("RandomWalk trial with 0 steps returns position 0", "[RandomWalk]") {
    RandomWalk rw;
    int result = rw.runTrial(0);
    REQUIRE(result == 0);
}

TEST_CASE("RandomWalk trial produces reasonable position values", "[RandomWalk]") {
    RandomWalk rw;
    int steps = 10;
    int position = rw.runTrial(steps);
    
    REQUIRE(position >= -steps);
    REQUIRE(position <= steps);
    REQUIRE((position + steps) % 2 == 0);
}

TEST_CASE("RandomWalk simulation returns correct number of trials", "[RandomWalk]") {
    RandomWalk rw;
    int N = 10;
    int M = 5;
    
    SimulationResult result = rw.runSimulation(N, M);
    
    REQUIRE(result.N == N);
    REQUIRE(result.M == M);
    REQUIRE(result.trials.size() == M);
    
    for (const auto& trial : result.trials) {
        REQUIRE(trial.steps == N);
        REQUIRE(trial.final_position >= -N);
        REQUIRE(trial.final_position <= N);
    }
}

TEST_CASE("RandomWalk benchmarks", "[RandomWalk][benchmark]") {
    RandomWalk rw;
    
    BENCHMARK("10 steps") {
        return rw.runTrial(10);
    };
    
    BENCHMARK("50 steps") {
        return rw.runTrial(50);
    };
    
    BENCHMARK("100 steps") {
        return rw.runTrial(100);
    };
    
    BENCHMARK("500 steps") {
        return rw.runTrial(500);
    };
    
    BENCHMARK("1000 steps") {
        return rw.runTrial(1000);
    };
}