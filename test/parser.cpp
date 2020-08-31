#include "gtest/gtest.h"
#include "parser.hpp"
#include <string>

TEST(parserTest, parseToml)
{
    std::string testFile = "houses_test.toml";
    Simulation simulation = Parser::parse(testFile);
    auto h1 = simulation.homes_.at(0);
    auto h2 = simulation.homes_.at(1);
    EXPECT_EQ(h1.name, "80/10/10 30 year 2020 Cheap");
    EXPECT_EQ(h2.name, "20% down 2021 Medium");
}