#pragma once
#include "home.hpp"
#include <vector>

class Simulation
{
public:
    const std::vector<Home> homes_;
    Simulation(std::vector<Home> homes) : homes_(homes){};
    void run();
};
