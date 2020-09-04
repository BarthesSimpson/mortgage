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
    EXPECT_EQ(home1.getValue(), 900000);
    EXPECT_EQ(home1.getPercentPaid(), 10.0);
    EXPECT_EQ(home1.getRemainingDebt(), 810000.0);
    EXPECT_EQ(home1.getEquity(), 90000.0);

    auto h2 = simulation.homes_.at(1);
    Home home2 = Home(h2);
    EXPECT_EQ(home2.name, "20% down 2021 Medium");
    EXPECT_EQ(home2.getValue(), 1000000);
    EXPECT_EQ(home2.getPercentPaid(), 20.0);
    EXPECT_EQ(home2.getRemainingDebt(), 800000.0);
    EXPECT_EQ(home2.getEquity(), 200000.0);
}

TEST(homeTest, makePayment)
{
    std::string testFile = "houses_test.toml";
    Simulation simulation = Parser::parse(testFile);
    auto h1 = simulation.homes_.at(0);
    Home home1 = Home(h1);
    std::cout << home1 << std::endl;
    EXPECT_EQ(home1.getEquity(), 90000.0);
    const double tax = home1.computeMonthlyPropertyTax();
    EXPECT_EQ(tax, 712.5);
    const double amount = home1.getMonthlyPayment();
    // 2092.5 interest (3.1% annual on $810,000) + 712.5 tax (0.095% annual on $900,000)
    // + 2250.0 principal ($810,000 / 30 years * 12 months) + 675.0 PMI (1% annual on $810,000)
    const double interest = 2092.5;
    const double principal = 2250.0;
    const double PMI = 675.0;
    std::cout << amount << std::endl;
    EXPECT_NEAR(amount, tax + interest + principal + PMI, 0.001);
    home1.makePayment(amount);
    std::cout << home1 << std::endl;
    EXPECT_EQ(home1.getEquity(), 92250.0);
}
