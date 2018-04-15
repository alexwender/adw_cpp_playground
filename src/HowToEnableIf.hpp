//
// Created by awender on 4/15/18.
//

#ifndef ADW_CPP_PLAYGROUND_HOWTOENABLEIF_HPP
#define ADW_CPP_PLAYGROUND_HOWTOENABLEIF_HPP

#include <iostream>
#include <type_traits>


template <typename T>
struct has_requested_member_method_no_argument
{
  struct dummy { /* something */ };

  template <typename C, typename P>
  static auto test(P* p) -> decltype(std::declval<C>().requested_member(), std::true_type());

  template <typename, typename>
  static std::false_type test(...);

  typedef decltype(test<T, dummy>(nullptr)) type;
  static const bool value = std::is_same<std::true_type, decltype(test<T, dummy>(nullptr))>::value;
};


template <typename T, typename = void>
struct hasDoNothing : std::false_type{

};

template <typename T>
struct hasDoNothing<T, decltype(std::declval<T>().doNothing())> : std::true_type {

};

template <typename T, typename = int>
struct hasNothing : std::false_type{

};

template <typename T>
struct hasNothing<T, decltype(std::declval<T>().nothing)> : std::true_type {

};


template<class>
struct sfinae_true : std::true_type{};

namespace detail{
template<class T, class A0>
static auto test_process_value(int)
-> sfinae_true<decltype(std::declval<T>().process_value(std::declval<A0>()))>;
template<class, class A0>
static auto test_process_value(...) -> std::false_type;
} // detail::

template<class T, class Arg>
struct has_process_value : decltype(detail::test_process_value<T, Arg>(0)){};


template<typename T>
using Apply = typename T::type;

template<typename T>
class HowToEnableIf {

 public:

  template<
      typename U=T
  >
    typename std::enable_if<has_requested_member_method_no_argument<U>::value>::type  has_member(void) {
    std::cout << "Has member and is called ..\n";
    T::requested_member();
    std::cout << "\n";
  }

  template<
      typename U=T
  >
  typename std::enable_if<!has_requested_member_method_no_argument<U>::value>::type  has_member(void) {
    std::cout << "Has not member and substitute is called ..\n";
    T::substitute_member();
    std::cout << "\n";
  }

  template<
    typename U=T>

      int process_value(int value,
                        typename std::enable_if<has_process_value<U, int>::value>::type* = 0) {

    return T::process_value(value);

  };

  template<
      typename U=T>

  int process_value(int value,
                    typename std::enable_if<!has_process_value<U, int>::value>::type* = 0) {

    return T::substitute_process_value(value);

  };

  template<typename U=T>
  auto doNothing() -> Apply<std::enable_if<hasDoNothing<U>::value, int>> {

      local_obj.doNothing();

      return 2;

  };

  template<typename U=T>
      auto doNothing() ->Apply<std::enable_if<
          !hasDoNothing<U>::value && hasNothing<U>::value
          , int>> {

    return 1;
  }



 private:

  T local_obj;


//
//  template<
//      typename U=T,
//      typename = typename std::enable_if<!has_requested_member_method<U>::value>::type
//  >
//    void has_member() {
//    std::cout << "Ha not member and substitute is called ..\n";
//    T::substitute_member();
//    std::cout << "\n";
//  };



};


class HasMember {
 public:

  static void requested_member() {

    std::cout << "calling requested member from HasMember\n";

  }

  static int process_value(int value) {
    return value +1;
  }
};

class HasNotMember {

 public:

  static void substitute_member() {
    std::cout << "calling substitute member from HasNotMember\n";
  }

  static int substitute_process_value(int value) {
    return value + 2;
  }

};

class HasDoNothing {
 public:

  void doNothing() {
    std::cout << "doNothing from DoNothing" << "\n";
  }
};

class HasNotDoNothingButMember {
 public:

  int nothing=4;
};

#endif //ADW_CPP_PLAYGROUND_HOWTOENABLEIF_HPP

