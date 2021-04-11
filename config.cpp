#include "config.hpp"

namespace evconfig {
  Config::Config() : _isLoaded(false) {}

  void Config::defineOption(const std::string& optName, ValueType type, const std::string& defaultValue) {

  } 

  void Config::loadFromFile(const std::string& path) {

  }

  void Config::loadFromEnvironment() {

  }
  
  int Config::getInt(const std::string& optName) {
    return 0;
  }

  bool Config::getBool(const std::string& optName) {
    return true;
  }

  const std::string& Config::getString(const std::string& optName) {
    return "";
  }
}
