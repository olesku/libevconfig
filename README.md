# libevconfig
libevconfig is a C++ library for parsing config files with ini like key=value format.
It supports comments, types and can read from files, streams or ennvironment variables.

It does type validation and syntax checking.
Currently supported types are integers, booleans and strings.

## Example usage
```cpp
#include <string>
#include "config.hpp"

using namespace evconfig;

int main(int argc, char* argv[]) {
  Config cfg;
  cfg.defineOption<int>("my_int", ValueSettings::REQUIRED);
  cfg.defineOption<bool>("my_boolean", ValueSettings::REQUIRED);
  cfg.defineOption<std::string>("my_string", ValueSettings::REQUIRED);


  // If this is set we will also read values from environment variables.
  // Those will take presedence over the values read from the config file.
  setLoadFromEnv(true);

  // Define a config file to read from.
  cfg.setFile("myFile.conf");

  // We can also use this syntax to feed the parser with data.
  cfg << "my_string = Hello world!\n";

  cfg.load();

  const auto my_int      = cfg.get<int>("my_boolean");
  const auto my_boolean  = cfg.get<bool>("my_boolean");
  const auto my_string   = cfg.get<std::string>("my_boolean");

  return 0;
}
```

Read the tests for more examples of how to use the library.