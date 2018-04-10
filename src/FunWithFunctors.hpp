//
// Created by alex on 08.04.18.
//

#ifndef ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP
#define ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP

#include <iostream>
#include <memory>
#include <type_traits>

namespace playground {

class FunWithFunctors {

};

template<typename T>
class Functor {
 public:

  using value_type = T;

  Functor(const T& value):prev_value(value) {

  };

  bool operator()(const T& value) const {

    std::cout << "passed value is  : " << value << "\n";
    std::cout << "previous value is: " << prev_value << "\n";

  }

 private:
  T prev_value;
};


template<
    typename T,
    typename FUNCTION
>
class PerformFunction {

 private:
  std::unique_ptr<FUNCTION> perform_function;

 public:

  PerformFunction(std::unique_ptr<FUNCTION> p_function):
      perform_function(std::move(p_function)){

  };

  void performFunction(const T& value) const {
    (*perform_function)(value);
  }

};


template<
    typename FuncType>
PerformFunction<typename FuncType::value_type, FuncType> makePerformFunction(
    std::unique_ptr<FuncType> func) {
  return PerformFunction<typename FuncType::value_type, FuncType>(std::move(func));
}

template<typename T>
struct _POINT {

  using value_type = T;

  std::array<T, 3> data;

  _POINT(const T& x, const T& y, const T& z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
  };

  _POINT():data({0.0, 0.0, 0.0}){};

};

using POINT = _POINT<double>;

struct POINT_LIST {

  using value_type = POINT;

  std::vector<POINT> points;

  POINT_LIST():points(0){};

};

struct LAYERED_POINT_LIST {

  using SPtr = typename std::shared_ptr<LAYERED_POINT_LIST>;
  using value_type = POINT_LIST;

  std::vector<POINT_LIST> layers;

  double option_value=0.0;

  LAYERED_POINT_LIST(const uint number_layers):layers(number_layers){

    };

  static inline SPtr createEmpty(const uint number_layers) {

    auto ret = std::make_shared<LAYERED_POINT_LIST>(number_layers);

    return ret;

  }



};

class SortLayeredList {

 public:
  using UPtr = std::unique_ptr<SortLayeredList>;
  using point_list_type = LAYERED_POINT_LIST::value_type;
  using point_type = point_list_type::value_type;
  using point_value_type = point_type::value_type;

  LAYERED_POINT_LIST::SPtr m_stored_values;

  SortLayeredList(LAYERED_POINT_LIST::SPtr& values):m_stored_values(values) {};

  bool operator()(const point_type& point) {
    std::cout << "Sorting with point: " << point.data[0] << ", " << point.data[1] << ", " << point.data[2] << "\n";

    std::cout << "In layers: " << m_stored_values->layers.size() << "\n";

    for (int i=0; i < m_stored_values->layers.size(); i++) {

      std::cout << "layer: " << i << ": number_points: " << m_stored_values->layers[i].points.size() << "\n";

    }

    return true;

  };

};




template<
    typename SORT_FUNCTION_POINTER
    >
class ProcessLayeredList {

 public:

  using SORT_FUNCTION = typename std::pointer_traits<SORT_FUNCTION_POINTER>::element_type;
  using POINT_TYPE = typename SORT_FUNCTION::point_type;

  SORT_FUNCTION_POINTER sort_functor;

  ProcessLayeredList(SORT_FUNCTION_POINTER sort_function)
      :sort_functor(std::move(sort_function)) {

  };

  bool processPoint(const POINT_TYPE& point) {
    std::cout << "First sorting ... \n";
    (*sort_functor)(point);
  };



};




} /* namespace playground */
#endif //ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP
