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
           computeMonthlyPrincipalPayment();
};

// Should probably handle interest balance and principal balance separately to allow more realistic payment apportionment, 
// but this is ok for now.
double Mortgage::getBalance() const
{
    return balance_;
};

void Mortgage::incrementYear()
{
    balance_ *= (1.0 + interest_rate_);
    year_++;
};

void Mortgage::makePayment(const double amount)
{
    // For simplicity, we assume we only ever make a payment that is an exact multiple of the monthly required payment
    double num_months = amount / (computeMonthlyPrivateMortgageInsurance() + computeMonthlyInterestPayment() + computeMonthlyPrincipalPayment());
    balance_ = std::max(0.0, balance_ - (num_months * (computeMonthlyInterestPayment() + computeMonthlyPrincipalPayment())));
};

double Mortgage::computeMonthlyPrivateMortgageInsurance() const
{
    if ((balance_ / initial_value_) < 0.8)
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
    return (interest_rate_ * balance_) / 12.0;
};

double Mortgage::computeMonthlyPrincipalPayment() const
{
    return ((initial_value_ - down_payment_) / (12.0 * term_in_years));
};
