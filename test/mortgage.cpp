#include "gtest/gtest.h"
#include "parser.hpp"
#include "mortgage.hpp"
#include "home.hpp"
#include <string>
#include <iostream>

TEST(mortgageTest, makePayment)
{
    auto mortgage = Mortgage(10000, 0.03, 20, 0.1);
    EXPECT_DOUBLE_EQ(mortgage.getBalance(), 9000.0);

    const double downpayment = mortgage.getDownPaymentSize();
    EXPECT_DOUBLE_EQ(downpayment, 1000.0);

    const double interest = mortgage.computeMonthlyInterestPayment();
    // 3% of 9000, divided by 12 months
    EXPECT_DOUBLE_EQ(interest, 22.5);

    const double principal = mortgage.computeMonthlyPrincipalPayment();
    // 9000 / (20 years * 12 months)
    EXPECT_DOUBLE_EQ(principal, 37.5);

    const double PMI = mortgage.computeMonthlyPrivateMortgageInsurance();
    // 1% of 9000, divided by 12 months
    EXPECT_NEAR(PMI, 7.5, 0.01);

    mortgage.makePayment(principal + interest + PMI);
    // Only the principal and interest payment is deducted from the balance
    EXPECT_DOUBLE_EQ(mortgage.getBalance(), 8940.0);
}

TEST(mortgageTest, incrementYear)
{
    auto mortgage = Mortgage(10000, 0.03, 20, 0.1);
    EXPECT_DOUBLE_EQ(mortgage.getBalance(), 9000.0);
    mortgage.incrementYear();
    EXPECT_DOUBLE_EQ(mortgage.getBalance(), 9270.0);
    mortgage.incrementYear();
    EXPECT_DOUBLE_EQ(mortgage.getBalance(), 9548.1);
}
