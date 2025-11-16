cmake_minimum_required(VERSION 3.25)
project(LifeGame LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
add_executable(LifeGame app/main.cpp)

# test project
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(LifeGameTests
  tests/test_life.cpp
)
target_link_libraries(LifeGameTests
  PRIVATE
    gtest_main
)
include(GoogleTest)
gtest_discover_tests(LifeGameTests)
