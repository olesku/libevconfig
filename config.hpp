#include <string>
#include <vector>
#include <unordered_map>

namespace evconfig {
  enum class ValueType : uint8_t {
    INT,
    BOOL,
    STRING
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
      ConfigOption() {};
      ~ConfigOption() {};

      const std::string& getName() {
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

      const std::string& getString() {
        if (_type != ValueType::STRING) {
          throw InvalidTypeException(getName(), ValueType::STRING, _type);
        }
        return str;
      }

      void setValue(const std::string& optName, ValueType type, const std::string& value);
  };

  class Config {
    public:
      Config();

      void defineOption(const std::string& optName, ValueType type, const std::string& defaultValue);      
      void loadFromFile(const std::string& path);
      void loadFromEnvironment();
      
      int getInt(const std::string& optName);
      bool getBool(const std::string& optName);
      const std::string& getString(const std::string& optName);

    private:
      bool _isLoaded;
      std::vector<ConfigOption> options;
  };
}
