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
    mortgage.makePayment(1000.0);
    EXPECT_EQ(mortgage.getBalance(), 8000.0);
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