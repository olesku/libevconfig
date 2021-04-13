#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "config.hpp"

namespace evconfig {

  ConfigOption::ConfigOption(const std::string& optName, ValueType type, const std::string& defaultValue) :
    _optionName(optName), _type(type)
  {
      setValue(defaultValue);
  }

  void ConfigOption::setValue(const std::string& value) {
    switch(_type) {
      case ValueType::INT:
        try {
          number = std::stoi(value);
        } catch (...) {
            throw std::runtime_error{"Invalid number: " + value};
        }
        break;

      case ValueType::BOOL:
        if (value == "true" || value == "TRUE" || value == "1")
          boolean = true;
        else if (value == "false" || value == "FALSE" || value == "0")
          boolean = false;
        else
          // FIXME: Add custom exception.
          throw std::runtime_error{"Invalid boolean value: " + value};
        break;

      case ValueType::STRING:
        str = value;
        break;

      default:
        // FIXME: Add custom exception.
        throw std::runtime_error{"Invalid value type specified for option " + value};
    }
  }

  Config::Config() {}

  void Config::defineOption(const std::string& optName, ValueType type, const std::string& defaultValue) {
    for (auto& opt : _options) {
      if (opt->getName() == optName)
        return;
    }

    _options.push_back(std::make_unique<ConfigOption>(optName, type, defaultValue));
  }

  void Config::loadFromFile(const std::string& path) {
    std::fstream f;
    std::string line;

    f.open(path, std::fstream::in);

    unsigned int lineNo = 0;
    while(std::getline(f, line)) {
      std::string parsedKey, parsedValue;
      unsigned int pos = 0;

      lineNo++;

      // Ignore all leading whitespaces.
      for (char c = line[pos]; pos < line.length() && (c == ' ' || c == '\t'); c=line[++pos]);

      // Ignore empty lines and comments.
      if (pos == line.length() || line[pos] == '#')
        continue;

      // Parse key name until space, tab or equal sign is reached.
      for (char c = line[pos]; pos < line.length(); c=line[++pos]) {
        if (c == ' ' || c == '\t' || c == '=')
          break;

        parsedKey += c;
      }

      // Key should not be empty.
      if (parsedKey.empty())
        throw SyntaxErrorException(path, lineNo);

      // We should now be at the equal sign before the value.
      for (char c = line[pos]; pos < line.length() && c != '='; c=line[++pos]);
      if (line[pos] != '=')
        throw SyntaxErrorException(path, lineNo);

      // Parse value ignoring leading whitespace.
      for (char c = line[++pos]; pos < line.length() && (c == ' ' || c == '\t'); c=line[++pos]);
      while(pos < line.length()) parsedValue += line[pos++];

      if (parsedValue.empty())
        throw SyntaxErrorException(path, lineNo);

      // Update config object with parsed key and value.
      bool validOption = false;
      for (auto& opt : _options) {
        if (opt->getName() == parsedKey) {
          opt->setValue(parsedValue);
          validOption = true;
        }
      }

      if (!validOption)
        throw std::runtime_error{"Unknown config option \"" + parsedKey + "\" at " + path + ":" + std::to_string(lineNo)};
    }

    f.close();
  }

  void Config::loadFromEnvironment() {
    //_isLoaded = true;
  }

  int Config::getInt(const std::string& optName) const {
    for (auto& opt : _options) {
      if (opt->getName() == optName) {
        return opt->getInt();
      }
    }

  throw InvalidConfigOptionException{optName};
  }

  bool Config::getBool(const std::string& optName) const {
    for (auto& opt : _options) {
      if (opt->getName() == optName) {
        return opt->getBool();
      }
    }

    throw InvalidConfigOptionException{optName};
  }

  const std::string& Config::getString(const std::string& optName) const {
    for (auto& opt : _options) {
      if (opt->getName() == optName) {
        return opt->getString();
      }
    }

  throw InvalidConfigOptionException{optName};
}

}