#include "gtest/gtest.h"
#include "parser.hpp"
#include "mortgage.hpp"
#include "home.hpp"
#include <string>
#include <iostream>

TEST(mortgageTest, makePayment)
{
    auto mortgage = Mortgage(10000, 0.03, 20, 0.1);
    EXPECT_EQ(mortgage.getBalance(), 9000.0);

    const double downpayment = mortgage.getDownPaymentSize();
    EXPECT_EQ(downpayment, 1000.0);

    const double interest = mortgage.computeMonthlyInterestPayment();
    // 3% of 9000, divided by 12 months
    EXPECT_EQ(interest, 22.5);

    const double principal = mortgage.computeMonthlyPrincipalPayment();
    // 9000 / (20 years * 12 months)
    EXPECT_EQ(principal, 37.5);

    const double PMI = mortgage.computeMonthlyPrivateMortgageInsurance();
    // 1% of 9000, divided by 12 months
    EXPECT_NEAR(PMI, 7.5, 0.0001);

    mortgage.makePayment(principal + interest + PMI);
    // Only the principal payment is deducted from the balance
    EXPECT_EQ(mortgage.getBalance(), 8962.5);
}

TEST(mortgageTest, incrementYear)
{
    auto mortgage = Mortgage(10000, 0.03, 20, 0.1);
    EXPECT_EQ(mortgage.getBalance(), 9000.0);
    mortgage.incrementYear();
    EXPECT_EQ(mortgage.getBalance(), 9270.0);
    mortgage.incrementYear();
    EXPECT_EQ(mortgage.getBalance(), 9548.1);
}
