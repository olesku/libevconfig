#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>

namespace evconfig {
  enum class ValueType : uint8_t {
    INT,
    BOOL,
    STRING
  };

  class ConfigNotLoadedException : public std::exception {
    public:
      std::string msg;

      ConfigNotLoadedException(const std::string& optName) {
        msg = "Tried to get config parameter \"" + optName + "\" before config is loaded.";
      }

      const char* what() const throw() {
        return msg.c_str();
      }
  };

  class InvalidTypeException {
    public:
      std::string msg;

      InvalidTypeException(const std::string& optName, ValueType requestedType, ValueType actualType) {
        msg = "Could not get " + optName + " as type " + _typeToString(requestedType) +
              " actual type is " + _typeToString(actualType);
      }

      const char * what() const throw() {
        return msg.c_str();
      }

      private:
        std::string _msg;

        const std::string _typeToString(ValueType type) {
          switch(type) {
            case ValueType::INT:
              return "integer";
            break;

            case ValueType::BOOL:
              return "boolean";
            break;

            case ValueType::STRING:
              return "string";
            break;

            default:
              return "unknown";
          }
        }
  };

  class InvalidConfigOptionException : public std::exception {
    public:
      std::string msg;

      InvalidConfigOptionException(std::string optName) {
        msg = "Invalid config option " + optName;
      }

      const char * what() const throw() {
        return msg.c_str();
      }
  };

  class SyntaxErrorException : public std::exception {
    public:
      std::string msg;

      SyntaxErrorException(std::string path, unsigned int lineNo) {
        msg = "Invalid config syntax at " + path + ":" + std::to_string(lineNo);
      }

      const char * what() const throw() {
        return msg.c_str();
      }
  };

  class ConfigOption {
    private:
      std::string _optionName;

      union {
        int32_t number;
        bool boolean;
        std::string str;
      };

      ValueType _type;

    public:
      ConfigOption(const std::string& optName, ValueType type, const std::string& defaultValue);
      ~ConfigOption() {};

      const std::string& getName() const {
        return _optionName;
      }

      int32_t getInt() {
        if (_type != ValueType::INT) {
          throw InvalidTypeException(getName(), ValueType::INT, _type);
        }

        return number;
      }

      bool getBool() {
        if (_type != ValueType::BOOL) {
          throw InvalidTypeException(getName(), ValueType::BOOL, _type);
        }

        return boolean;
      }

      const std::string& getString() const {
        if (_type != ValueType::STRING) {
          throw InvalidTypeException(getName(), ValueType::STRING, _type);
        }
        return str;
      }

      void setValue(const std::string& value);
  };

  class Config {
    public:
      Config();

      void defineOption(const std::string& optName, ValueType type, const std::string& defaultValue);
      void loadFromFile(const std::string& path);
      void loadFromEnvironment();

      int getInt(const std::string& optName) const;
      bool getBool(const std::string& optName) const;
      const std::string& getString(const std::string& optName) const;

    private:
      std::vector<std::unique_ptr<ConfigOption>> _options;
  };
}
