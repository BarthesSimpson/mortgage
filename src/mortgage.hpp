#pragma once

class Mortgage
{
public:
    Mortgage(int price, double rate, int term, double down_payment_percent) : interest_rate_(rate), term_in_years_(term)
    {
        down_payment_ = down_payment_percent * price;
        balance_ = price - down_payment_;
    }

    double downPaymentSize();
    double monthlyPayment();

private:
    double balance_;
    double interest_rate_;
    int term_in_years_;
    double down_payment_;
};
