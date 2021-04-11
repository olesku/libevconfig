project(libevconfig)

set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-Wall")

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
