cmake_minimum_required(VERSION 3.0.0)

project(adw_cpp_playground)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# adding playground library

set (gtest_SOURCE_DIR "$ENV{HOME}/googletest/googletest" CACHE FILEPATH "Google Test source directory")

message(STATUS "gtest_SOURCE_DIR: ${gtest_SOURCE_DIR}")

add_subdirectory(${gtest_SOURCE_DIR} ${CMAKE_BINARY_DIR}/gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(playground_SRC src/dataobject.cpp)
list(APPEND playground_SRC src/datacontainer.h)

message(STATUS "playground SRC:\n${playground_SRC}")

set(playground_HDR src/dataobject.h src/FunWithFunctors.hpp)
list(APPEND playground_HDR src/datacontainer.cpp)
list(APPEND playground_HDR src/enumrange.hpp)

add_library(playground ${playground_HDR} ${playground_SRC})

# include the top level cmake directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_dataobject
        test/test_dataobject
        src/datacontainer.cpp
        src/datacontainer.h)
target_link_libraries(test_dataobject playground)

add_executable(test_enumrange test/test_enumrange)

add_executable(test_template_bool test/test_template_bool)

add_executable(test_fun_with_functors test/test_fun_with_functors.cpp)
target_link_libraries(test_fun_with_functors gtest gtest_main)

add_executable(test_how_to_enable_if test/test_how_to_enable_if.cpp src/HowToEnableIf.hpp)
target_link_libraries(test_how_to_enable_if gtest gtest_main)