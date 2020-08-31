#include "home.hpp"
#include <iostream>
#include <string>
#include <toml11/toml.hpp>
#include <memory>

Home::Home(toml::value rawHome)
{
    name = rawHome.at("name").as_string();
    const double price = rawHome.at("price").as_integer();
    initial_value_ = price;
    const auto &mortgage = toml::get<toml::table>(rawHome).at("mortgage");
    const double rate = mortgage.at("rate").as_floating();
    const int term = mortgage.at("term").as_integer();
    const double down = mortgage.at("down").as_floating();
    mortgage_ = std::make_shared<Mortgage>(price, rate, term, down);
};

const double Home::getValue()
{
    return value_;
};
const double Home::getPercentPaid()
{
    return 100.0 * ((initial_value_ - mortgage_->getBalance()) / initial_value_);
};
const double Home::getRemainingDebt()
{
    return mortgage_->getBalance();
};
const double Home::getEquity()
{
    return equity_;
};