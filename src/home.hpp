#pragma once
#include "mortgage.hpp"
#include <iostream>
#include <string>
#include <toml11/toml.hpp>
#include <memory>

class Home
{
public:
    std::string name;
    Home(std::string name, double price, Mortgage &&mortgage) : name(name), initial_value_(price), value_(price), mortgage_(&mortgage)
    {
        equity_ = mortgage.getDownPaymentSize();
    };
    Home(toml::value rawHome);
    friend std::ostream &operator<<(std::ostream &output, Home &H)
    {
        output << "Home: {value: " << H.getValue() << ", paid : " << H.getPercentPaid() << "% , remainingDebt: "
               << H.getRemainingDebt() << ", equity: " << H.getEquity() << "}";
        return output;
    };
    const double getValue();
    const double getPercentPaid();
    const double getRemainingDebt();
    const double getEquity();
    const double getMonthlyPayment();
    void incrementYear(double appreciationPercent);

private:
    double initial_value_;
    double value_;
    double equity_;
    int year_ = 0;
    std::shared_ptr<Mortgage> mortgage_;
    const double computeMonthlyPropertyTax();
};
