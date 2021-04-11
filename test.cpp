#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "config.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace evconfig;

Config cfg;

TEST_CASE("libevconfig") {
  cfg.defineOption("test_number", ValueType::INT, "0");
  cfg.defineOption("test_boolean", ValueType::BOOL, "false");
  cfg.defineOption("test_string", ValueType::STRING, "");

  SECTION("Config file") {
    ofstream testFile;
    testFile.open("test.conf");
    testFile << "test_number = 10" << endl;
    testFile << "test_boolean1 = true" << endl;
    testFile << "test_string = Hello world" << endl;
    testFile.close();

    cfg.loadFromFile("test.conf");

    REQUIRE(cfg.getInt("test_number") == 10);
    REQUIRE(cfg.getBool("test_boolean1") == true);
    REQUIRE(cfg.getString("test_string") == "Hello world");
  }
}
