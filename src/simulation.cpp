#include "simulation.hpp"
#include "home.hpp"
#include <algorithm>
#include <iostream>

void Simulation::run()
{
    int numYears = getDuration();
    std::cout << "Initial state" << std::endl;
    printState();
    for (int y = 0; y < numYears; y++)
    {
        std::cout << "Year " << y + 1 << std::endl;

        for (Home &home : homes_)
        {
            home.incrementYear(0.0);
            std::cout << "For home <" << home.name << " monthly payment is " << home.getMonthlyPayment() << std::endl;
            const double annual_payment = home.getMonthlyPayment() * 12.0;
            home.makePayment(annual_payment);
        };
        printState();
    }
}

void Simulation::printState()
{
    std::cout << DIVIDER << std::endl;
    for (auto &home : homes_)
    {
        std::cout << home << std::endl;
    };
    std::cout << DIVIDER << std::endl;
}

int Simulation::getDuration() const
{
    if (!homes_.size())
    {
        return 0;
    }
    auto h = std::max_element(
        homes_.begin(),
        homes_.end(),
        [](const Home l, const Home r) {
            return r.yearsTillPaid() > l.yearsTillPaid();
        });
    return h->yearsTillPaid();
}
