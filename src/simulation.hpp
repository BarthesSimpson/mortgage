#pragma once
#include "home.hpp"
#include <vector>

class Simulation
{
public:
    Simulation(std::vector<Home> homes)
    {
        homes_ = move(homes);
    }
    void run();

private:
    std::vector<Home> homes_;
};
