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
    std::cout << home1 << std::endl;
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
