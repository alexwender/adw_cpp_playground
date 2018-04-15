//
// Created by awender on 4/15/18.
//

#include <gtest/gtest.h>
#include <src/HowToEnableIf.hpp>

namespace playground {

TEST(HowToEnableIfTest, SimpleTest) {
  std::cout << "Testing enable if\n";

//  HowToEnableIf<HasMember>::has_member();

  HowToEnableIf<HasMember> has_member;

  HowToEnableIf<HasNotMember> has_not_member;

  has_member.has_member();

  has_not_member.has_member();

  auto has_member_value = has_member.process_value(1);

  auto has_not_member_value = has_not_member.process_value(1);
//
  std::cout << "has member value:     " << has_member_value <<"\n";
  std::cout << "has not member value: " << has_not_member_value << "\n";

  static_assert(has_requested_member_method_no_argument<HasMember>::value, "error");
  static_assert(!has_requested_member_method_no_argument<HasNotMember>::value, "error");
  static_assert(has_process_value<HasMember, int>::value, "Has not process value");
  static_assert(!has_process_value<HasNotMember, int>::value, "Has process value");

//  HasDoNothing test;

  static_assert(hasDoNothing<HasDoNothing>::value, "has not do nothing");
  static_assert(hasNothing<HasNotDoNothingButMember>::value, "has not do nothing but also not member");
  static_assert(!hasNothing<HasDoNothing>::value, "awea");

  HowToEnableIf<HasDoNothing> has_do_nothing;
  HowToEnableIf<HasNotDoNothingButMember> has_not_do_nothing;

  auto res_nothing = has_do_nothing.doNothing();
  auto res_no_nothing = has_not_do_nothing.doNothing();

  std::cout << "res_nothing   : " << res_nothing << "\n";
  std::cout << "res_no_nothing: " << res_no_nothing << "\n";


}

}

int main(int argc, char** argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}