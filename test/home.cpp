#include "gtest/gtest.h"
#include "parser.hpp"
#include "simulation.hpp"
#include "home.hpp"
#include <string>
#include <iostream>

TEST(homeTest, constructFromToml)
{
    std::string testFile = "houses_test.toml";
    Simulation simulation = Parser::parse(testFile);
    auto h1 = simulation.homes_.at(0);
    Home home1 = Home(h1);
    EXPECT_EQ(home1.name, "80/10/10 30 year 2020 Cheap");
    EXPECT_DOUBLE_EQ(home1.getValue(), 900000.0);
    EXPECT_DOUBLE_EQ(home1.getPercentPaid(), 0.1);
    EXPECT_DOUBLE_EQ(home1.getRemainingDebt(), 810000.0);
    EXPECT_DOUBLE_EQ(home1.getEquity(), 90000.0);

    auto h2 = simulation.homes_.at(1);
    Home home2 = Home(h2);
    EXPECT_EQ(home2.name, "20% down 2021 Medium");
    EXPECT_DOUBLE_EQ(home2.getValue(), 1000000.0);
    EXPECT_DOUBLE_EQ(home2.getPercentPaid(), 0.2);
    EXPECT_DOUBLE_EQ(home2.getRemainingDebt(), 800000.0);
    EXPECT_DOUBLE_EQ(home2.getEquity(), 200000.0);
}

TEST(homeTest, makePayment)
{
    std::string testFile = "houses_test.toml";
    Simulation simulation = Parser::parse(testFile);
    auto h1 = simulation.homes_.at(0);
    Home home1 = Home(h1);
    EXPECT_DOUBLE_EQ(home1.getEquity(), 90000.0);
    const double tax = home1.computeMonthlyPropertyTax();
    EXPECT_DOUBLE_EQ(tax, 712.5);
    const double amount = home1.getMonthlyPayment();
    // 2092.5 interest (3.1% annual on $810,000) + 712.5 tax (0.095% annual on $900,000)
    // + 2250.0 principal ($810,000 / 30 years * 12 months) + 675.0 PMI (1% annual on $810,000)
    const double interest = 2092.5;
    const double principal = 2250.0;
    const double PMI = 675.0;
    EXPECT_NEAR(amount, tax + interest + principal + PMI, 0.01);
    home1.makePayment(amount);
    EXPECT_DOUBLE_EQ(home1.getEquity(), 92250.0);
}

TEST(homeTest, incrementYear)
{
    std::string testFile = "houses_test.toml";
    Simulation simulation = Parser::parse(testFile);
    auto h1 = simulation.homes_.at(0);
    Home home1 = Home(h1);
    EXPECT_DOUBLE_EQ(home1.getValue(), 900000.0);
    home1.incrementYear(0.1);
    EXPECT_DOUBLE_EQ(home1.getValue(), 990000.0);

    // Verify that tax is calculated based on market value not original value
    const double tax = home1.computeMonthlyPropertyTax();
    EXPECT_NEAR(tax, 783.75, 0.01);
    const double amount = home1.getMonthlyPayment();
    // 2157.37 interest (3.1% annual on $810,000 compounded over 2 years since we didn't make the first year payment) 
    // + 783.75 tax (0.095% annual on $990,000)
    // + 2250.0 principal ($810,000 / 30 years * 12 months) + 675.0 PMI (1% annual on $810,000)
    const double interest = 2157.37;
    const double principal = 2250.0;
    const double PMI = 675.0;
    EXPECT_NEAR(home1.getMonthlyPayment(), tax + interest + principal + PMI, 0.01);

    // Verify that the equity appreciates with the house price
    EXPECT_DOUBLE_EQ(home1.getEquity(), 99000.0);

    // Verify that the percent paid is calculated based on the original price - the mortgage balance
    EXPECT_NEAR(home1.getPercentPaid(), 0.0721, 0.0001);

    // Verify can handle negative appreciation
    home1.incrementYear(-0.1);
    EXPECT_DOUBLE_EQ(home1.getValue(), 891000.0);
}
