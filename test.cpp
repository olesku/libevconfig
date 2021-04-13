#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "config.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace evconfig;

Config cfg;

TEST_CASE("libevconfig") {
  cfg.defineOption("test_number", ValueType::INT, "1337");

  cfg.defineOption("false_boolean_lowercase", ValueType::BOOL, "false");
  cfg.defineOption("false_boolean_uppercase", ValueType::BOOL, "FALSE");
  cfg.defineOption("false_boolean_0", ValueType::BOOL, "0");

  cfg.defineOption("true_boolean_lowercase", ValueType::BOOL, "true");
  cfg.defineOption("true_boolean_uppercase", ValueType::BOOL, "TRUE");
  cfg.defineOption("true_boolean_0", ValueType::BOOL, "1");

  cfg.defineOption("test_string", ValueType::STRING, "Foobar");

  SECTION("Check that defaults is set correctly") {
    SECTION("Test numbers") {
      REQUIRE(cfg.getInt("test_number") == 1337);
    }

    SECTION("Test booleans") {
      REQUIRE(cfg.getBool("false_boolean_lowercase") == false);
      REQUIRE(cfg.getBool("false_boolean_uppercase") == false);
      REQUIRE(cfg.getBool("false_boolean_0") == false);

      REQUIRE(cfg.getBool("true_boolean_lowercase") == true);
      REQUIRE(cfg.getBool("true_boolean_uppercase") == true);
      REQUIRE(cfg.getBool("true_boolean_0") == true);
    }

    SECTION("Test strings") {
      REQUIRE(cfg.getString("test_string") == "Foobar");
    }
  }

  /*ofstream testFile;
  testFile.open("test.conf");
  testFile << "test_number = 10" << endl;
  testFile << "false_boolean_lowercase = false" << endl;
  testFile << "false_boolean_uppercase = FALSE" << endl;
  testFile << "false_boolean_0 = 0" << endl;
  testFile << "true_boolean_lowercase = true" << endl;
  testFile << "true_boolean_uppercase = TRUE" << endl;
  testFile << "true_boolean_0 = 1" << endl;
  testFile << "test_string = Hello world" << endl;
  testFile.close();*/

  SECTION("Check parameters in configfile is set correctly") {
    cfg.loadFromFile("test.conf");

    SECTION("Test numbers") {
      REQUIRE(cfg.getInt("test_number") == 10);
    }

    SECTION("Test booleans") {
      REQUIRE(cfg.getBool("false_boolean_lowercase") == false);
      REQUIRE(cfg.getBool("false_boolean_uppercase") == false);
      REQUIRE(cfg.getBool("false_boolean_0") == false);

      REQUIRE(cfg.getBool("true_boolean_lowercase") == true);
      REQUIRE(cfg.getBool("true_boolean_uppercase") == true);
      REQUIRE(cfg.getBool("true_boolean_0") == true);
    }

    SECTION("Test strings") {
      REQUIRE(cfg.getString("test_string") == "Hello world!");
    }
  }
}
