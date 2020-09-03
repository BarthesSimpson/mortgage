#include "mortgage.hpp"
#include <algorithm>

double Mortgage::getDownPaymentSize() const
{
    return down_payment_;
};

double Mortgage::getMonthlyPayment() const
{
    return computeMonthlyPrivateMortgageInsurance() +
           computeMonthlyInterestPayment() +
           computeMonthlyBalancePayment();
};

double Mortgage::getBalance() const
{
    return balance_;
};

void Mortgage::incrementYear()
{
    balance_ = balance_ * (1.0 + interest_rate_);
    year_++;
};

void Mortgage::makePayment(const double amount)
{
    balance_ = std::max(0.0, balance_ - amount);
};

double Mortgage::computeMonthlyPrivateMortgageInsurance() const
{
    if ((balance_ / initial_value_) >= 0.8)
    {
        return 0.0;
    }
    // TODO: Get this from a config file
    float PMI_RATE = 0.01;
    return (PMI_RATE / 12.0) * (initial_value_ - down_payment_);
};

double Mortgage::computeMonthlyInterestPayment() const
{
    // This isn't quite accurate since I think the annual interest payment is calculated
    // based on the year-start balance and then divided by 12, but it's close enough.
    return (interest_rate_ / 12.0) * balance_;
};

double Mortgage::computeMonthlyBalancePayment() const
{
    return (initial_value_ / (12.0 * term_in_years));
};