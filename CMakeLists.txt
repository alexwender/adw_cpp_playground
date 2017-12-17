cmake_minimum_required(VERSION 3.0.0)

project(adw_cpp_playground)

set (CMAKE_CXX_STANDARD 11)

# adding playground library

set(playground_SRC src/dataobject.cpp)
list(APPEND playground_SRC src/datacontainer.h)

message(STATUS "playground SRC:\n${playground_SRC}")

set(playground_HDR src/dataobject.h)
list(APPEND playground_HDR src/datacontainer.cpp)

add_library(playground ${playground_HDR} ${playground_SRC})

# include the top level cmake directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_dataobject test/test_dataobject)
target_link_libraries(test_dataobject playground)


