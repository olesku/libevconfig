project(libevconfig)

cmake_minimum_required (VERSION 2.9)
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-Wall -std=c++17")

include(CTest)

add_library( config
  config.cpp
)

if (BUILD_TESTING)
  find_package(Catch2)
  add_executable(libevconfig_test test.cpp)
  target_link_libraries(libevconfig_test PRIVATE config)
  target_link_libraries(libevconfig_test PRIVATE Catch2::Catch2)
  add_test(libevconfig_test libevconfig_test)
endif()

add_custom_target(
        clangformat
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)