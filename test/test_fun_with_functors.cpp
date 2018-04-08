//
// Created by alex on 08.04.18.
//

#include <gtest/gtest.h>

#include <iostream>

TEST(TestFunWithFunctors, SimpleTest) {
  std::cout << "Simple FunWithFunctors test ...\n";
}

int main (int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}