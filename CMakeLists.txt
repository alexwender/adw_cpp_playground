cmake_minimum_required(VERSION 3.10.2)

project(adw_cpp_playground)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find and set binary dir for GTest
# the gtest source dir is taken from ubuntu standard install path
set (gtest_SOURCE_DIR "/usr/src/googletest/googletest" CACHE FILEPATH "Google Test source directory")
add_subdirectory(${gtest_SOURCE_DIR} ${CMAKE_BINARY_DIR}/gtest)

enable_testing()

include(GoogleTest)

add_executable(
        test_dataobject
        test/test_dataobject.cpp
        src/dataobject.cpp)

target_include_directories(
        test_dataobject
        PUBLIC
        "include"
)

target_link_libraries(
        test_dataobject
        gtest_main
)

gtest_discover_tests(test_dataobject)

# add_executable(test_enumrange test/test_enumrange)

# add_executable(test_template_bool test/test_template_bool)

# add_executable(test_fun_with_functors test/test_fun_with_functors.cpp)
# target_link_libraries(test_fun_with_functors gtest gtest_main)

# add_executable(test_how_to_enable_if test/test_how_to_enable_if.cpp src/HowToEnableIf.hpp)
# target_link_libraries(test_how_to_enable_if gtest gtest_main)
