#pragma once
#include "mortgage.hpp"
#include <string>

class Home
{
public:
    std::string name;
    Home(std::string name, double price, Mortgage mortgage) : name(name), value_(price), mortgage_(mortgage){};
    void appreciate(double percent);
    double getValue();
    double getPercentPaid();
    double getRemainingDebt();
    double getEquity();

private:
    double value_;
    Mortgage mortgage_;
};
