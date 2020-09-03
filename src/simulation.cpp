#include "simulation.hpp"
#include <algorithm>
#include <iostream>

void Simulation::run()
{
    auto h = std::max_element(
        homes_.begin(),
        homes_.end(),
        [](const Home l, const Home r) {
            return r.yearsTillPaid() > l.yearsTillPaid();
        });
    auto term = h->yearsTillPaid();
    std::cout << term << std::endl;
}