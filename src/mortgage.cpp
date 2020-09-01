#include "mortgage.hpp"

const double Mortgage::getDownPaymentSize()
{
    return down_payment_;
};

const double Mortgage::getMonthlyPayment()
{
    return computeMonthlyPrivateMortgageInsurance() +
           computeMonthlyInterestPayment() +
           computeMonthlyBalancePayment();
};

const double Mortgage::getBalance()
{
    return balance_;
};

void Mortgage::incrementYear(){
    //TODO
};

void Mortgage::makePayment(const double amount){
    //TODO
};

const double Mortgage::computeMonthlyPrivateMortgageInsurance()
{
    if ((balance_ / initial_value_) >= 0.8)
    {
        return 0.0;
    }
    // TODO: Get this from a config file
    float PMI_RATE = 0.01;
    return (PMI_RATE / 12.0) * (initial_value_ - down_payment_);
};

const double Mortgage::computeMonthlyInterestPayment()
{
    // This isn't quite accurate since I think the annual interest payment is calculated
    // based on the year-start balance and then divided by 12, but it's close enough.
    return (interest_rate_ / 12.0) * balance_;
};

const double Mortgage::computeMonthlyBalancePayment()
{
    return (initial_value_ / (12.0 * term_in_years_));
};