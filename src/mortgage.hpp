#pragma once

class Mortgage
{
public:
    Mortgage(int price, double rate, int term, double down_payment_percent) : interest_rate_(rate), term_in_years_(term)
    {
        down_payment_ = down_payment_percent * price;
        balance_ = price - down_payment_;
        year_ = 0;
    }

    const double getDownPaymentSize();
    const double getMonthlyPayment();
    const double getBalance();
    void incrementYear();
    void makePayment(const double amount);

private:
    double year_;
    double balance_;
    double interest_rate_;
    int term_in_years_;
    double down_payment_;
};
