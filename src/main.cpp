#include "home.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Welcome" << std::endl;

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path to file>" << std::endl;
        return 1;
    }

    try
    {
        Simulation simulation = Parser::parse(argv[1]);
        simulation.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Done" << std::endl;
}