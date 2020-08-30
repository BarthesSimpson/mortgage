#pragma once
#include "simulation.hpp"
#include <string>

class Parser
{
public:
    static Simulation parse(std::string filepath);
};
