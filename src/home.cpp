#include "home.hpp"
#include <iostream>
#include <string>
#include <toml11/toml.hpp>
#include <memory>
#include <algorithm>

Home::Home(toml::value rawHome)
{
    name = rawHome.at("name").as_string();
    const double price = rawHome.at("price").as_integer();
    value_ = price;
    initial_value_ = price;
    const auto &mortgage = toml::get<toml::table>(rawHome).at("mortgage");
    const double rate = mortgage.at("rate").as_floating();
    const int term = mortgage.at("term").as_integer();
    const double down = mortgage.at("down").as_floating();
    mortgage_ = std::make_shared<Mortgage>(price, rate, term, down);
    equity_ = mortgage_->getDownPaymentSize();
};

double Home::getValue() const
{
    return value_;
};

// Represented as a decimal, e.g. 0.1 is 10%
double Home::getPercentPaid() const
{
    return (initial_value_ - mortgage_->getBalance()) / initial_value_;
};

double Home::getRemainingDebt() const
{
    return mortgage_->getBalance();
};

double Home::getEquity() const
{
    return (equity_ / initial_value_) * value_;
};

int Home::yearsTillPaid() const
{
    if (!mortgage_)
    {
        return 0;
    }
    return mortgage_->term_in_years - year_;
}

void Home::makePayment(const double amount)
{
    // Keep it simple for now by just assuming we always pay an exact multiple of the total monthly payment
    double num_months = amount / getMonthlyPayment();
    double tax = num_months * computeMonthlyPropertyTax();
    mortgage_->makePayment(amount - tax);
    equity_ += (num_months * mortgage_->computeMonthlyPrincipalPayment());
    equity_ = std::min(equity_, initial_value_);
}

void Home::incrementYear(double appreciationPercent)
{
    mortgage_->incrementYear();
    value_ *= (1.0 + appreciationPercent);
    year_++;
}

double Home::getMonthlyPayment() const
{
    return computeMonthlyPropertyTax() + mortgage_->getMonthlyPayment();
}

double Home::computeMonthlyPropertyTax() const
{
    // TODO: get this from a config file
    const double TAX_RATE = 0.0095;
    return (TAX_RATE / 12.0) * value_;
};
