#include "parser.hpp"
#include "home.hpp"
#include "toml.hpp"
#include <vector>

Simulation Parser::parse(std::string filepath)
{
    auto data = toml::parse(filepath);
    auto homes = std::vector<Home>();
    return Simulation(homes);

    // TODO
};
