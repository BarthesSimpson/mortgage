#pragma once

class Mortgage
{
public:
    const int term_in_years;
    Mortgage(int price, double rate, int term, double down_payment_percent) : initial_value_(price), interest_rate_(rate), term_in_years(term)
    {
        down_payment_ = down_payment_percent * double(price);
        balance_ = double(price) - down_payment_;
        year_ = 0;
    }

    double getDownPaymentSize() const;
    double getMonthlyPayment() const;
    double getBalance() const;
    void incrementYear();
    void makePayment(const double amount);
    double computeMonthlyPrivateMortgageInsurance() const;
    double computeMonthlyInterestPayment() const;
    double computeMonthlyPrincipalPayment() const;

private:
    double year_;
    double initial_value_;
    double balance_;
    double interest_rate_;
    double down_payment_;
};
