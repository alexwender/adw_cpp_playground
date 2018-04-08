//
// Created by alex on 08.04.18.
//

#ifndef ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP
#define ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP

#include <iostream>

namespace playground {

class FunWithFunctors {

};

template<typename T>
class Functor {
 public:

  bool operator(const T& value)() const {

    std::cout << "value is " << value << "\n";

  }
};

} /* namespace playground */
#endif //ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP
