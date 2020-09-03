#include "home.hpp"
#include <iostream>
#include <string>
#include <toml11/toml.hpp>
#include <memory>

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

double Home::getPercentPaid() const
{
    return 100.0 * ((initial_value_ - mortgage_->getBalance()) / initial_value_);
};

double Home::getRemainingDebt() const
{
    return mortgage_->getBalance();
};

double Home::getEquity() const
{
    return equity_;
};

int Home::yearsTillPaid() const
{
    if (!mortgage_)
    {
        return 0;
    }
    return mortgage_->term_in_years - year_;
}

double Home::computeMonthlyPropertyTax() const
{
    // TODO: get this from a config file
    const double TAX_RATE = 0.0095;
    return (TAX_RATE / 12.0) * value_;
};
