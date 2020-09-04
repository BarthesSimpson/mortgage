#include "parser.hpp"
#include "home.hpp"
#include <toml11/toml.hpp>
#include <vector>
#include <iostream>
#include <string>

Simulation Parser::parse(std::string filepath)
{
    auto data = toml::parse(filepath);
    std::cout << data << std::endl;
    const auto rawHomes = toml::find<std::vector<toml::table>>(data, "houses");
    auto homes = std::vector<Home>();

    for (auto h : rawHomes)
    {
        std::cout << "Processing " << h.at("name") << std::endl;
        try
        {
            homes.emplace_back(Home(h));
        }
        catch (const std::exception &e)
        {
            std::cerr << "FAILED: " << e.what() << std::endl;
        }
    }
    return Simulation(homes);
};
