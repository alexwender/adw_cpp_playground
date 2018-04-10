//
// Created by alex on 08.04.18.
//

#ifndef ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP
#define ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP

#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

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


struct LayeredPointReference{

  std::uint32_t layer_id=0;
  std::uint32_t point_id=0;

  LayeredPointReference(
      std::uint32_t layer=0,
      std::uint32_t point=0
      ):layer_id(layer), point_id(point){

  };

  friend std::ostream& operator<<(std::ostream& stream, const LayeredPointReference& ref) {
    stream << ref.layer_id << ", " << ref.point_id;
    return stream;
  }

};


class SortLayeredList {

 public:
  using UPtr = std::unique_ptr<SortLayeredList>;
  using point_list_type = LAYERED_POINT_LIST::value_type;
  using point_type = point_list_type::value_type;
  using point_value_type = point_type::value_type;
  using output_container = std::vector<LayeredPointReference>;

  LAYERED_POINT_LIST::SPtr m_stored_values;

  SortLayeredList(LAYERED_POINT_LIST::SPtr& values):m_stored_values(values) {};

  output_container operator()(const point_type& point) {
    std::cout << "Sorting with point: " << point.data[0] << ", " << point.data[1] << ", " << point.data[2] << "\n";

    std::cout << "In layers: " << m_stored_values->layers.size() << "\n";

    output_container temp_cont;

    for (int i=0; i < m_stored_values->layers.size(); i++) {

      std::cout << "layer: " << i << ": number_points: " << m_stored_values->layers[i].points.size() << "\n";

      temp_cont.emplace_back(
          LayeredPointReference(i, 0.0)
          );

    }

    return temp_cont;

  };

};

template<
    typename SORT_LAYERED_LIST_POINTER,
    typename OUTPUT = LayeredPointReference
    >
class TemplatedSortLayeredList {

 public:

  using layered_point_list = typename std::pointer_traits<SORT_LAYERED_LIST_POINTER>::element_type;
  using point_list = typename LAYERED_POINT_LIST::value_type;
  using point_type = typename point_list::value_type;
  using point_value_type = typename point_type::value_type;
  using output_container = typename std::vector<OUTPUT>;

  SORT_LAYERED_LIST_POINTER m_stored_values;

  TemplatedSortLayeredList(SORT_LAYERED_LIST_POINTER& values):m_stored_values(values) {};

  output_container operator()(const point_type& point) {
    std::cout << "Templated Sorting with point: " << point.data[0] << ", " << point.data[1] << ", " << point.data[2] << "\n";

    std::cout << "In layers: " << m_stored_values->layers.size() << "\n";

    output_container temp_cont;

    for (int i=0; i < m_stored_values->layers.size(); i++) {

      std::cout << "layer: " << i << ": number_points: " << m_stored_values->layers[i].points.size() << "\n";

      temp_cont.emplace_back(OUTPUT(i, 0));


    }
    return temp_cont;
  };

};

template<
    std::uint32_t N=2,
    typename REFERENCE_TYPE = LayeredPointReference
    >
struct CorrespondenceResult {

  static const std::uint32_t dim = N;

  using value_type = REFERENCE_TYPE;
  using OUTPUT = typename std::array<REFERENCE_TYPE, N>;

  bool is_valid = false;

  OUTPUT references;

  friend std::ostream& operator<<(std::ostream& stream, const CorrespondenceResult& ref) {
    stream << ref.references[0];

    for (int i=1; i < N; i++) {
      stream << ", " << ref.references[1];
    }

    return stream;
  }

};

template<
    typename SORT_LAYERED_LIST_POINTER,
    typename INPUT,
    typename OUTPUT = CorrespondenceResult<2, LayeredPointReference>
    >
class AbstractTemplatedSortFilter {
 public:
  using layered_point_list = typename std::pointer_traits<SORT_LAYERED_LIST_POINTER>::element_type;
  using point_list = typename layered_point_list::value_type;
  using point_type = typename point_list::value_type;
  using output_type = OUTPUT;
  using reference_type = typename output_type::value_type;

  SORT_LAYERED_LIST_POINTER m_stored_values;

  AbstractTemplatedSortFilter(SORT_LAYERED_LIST_POINTER& values):m_stored_values(values) {};

  virtual output_type operator()(const point_type& point, const INPUT& reference) = 0;

};

template<
    typename SORT_LAYERED_LIST_POINTER,
    typename INPUT
    >
class EdgeTemplatedSortFilter : public AbstractTemplatedSortFilter<
    SORT_LAYERED_LIST_POINTER,
    INPUT,
    CorrespondenceResult<2, LayeredPointReference>
> {
  using AbstractTemplatedSortFilter<SORT_LAYERED_LIST_POINTER, INPUT, CorrespondenceResult<2>>::AbstractTemplatedSortFilter;
  using output_type = typename AbstractTemplatedSortFilter<SORT_LAYERED_LIST_POINTER, INPUT, CorrespondenceResult<2>>::output_type;
  using point_type = typename AbstractTemplatedSortFilter<SORT_LAYERED_LIST_POINTER, INPUT, CorrespondenceResult<2>>::point_type;
  using reference_type = typename AbstractTemplatedSortFilter<SORT_LAYERED_LIST_POINTER, INPUT, CorrespondenceResult<2>>::reference_type;

 public:

  output_type operator()(const point_type& point, const INPUT& references) final {
    std::cout << "Return edge correspondence ...\n";

    output_type temp_output;

    temp_output.references[0] = reference_type(10, 20);
    temp_output.references[1] = reference_type(20, 30);

    return temp_output;
  }
};

template<
    typename SORT_LAYERED_LIST_POINTER,
    typename INPUT
    >
class SurfTemplatedSortFiler : public AbstractTemplatedSortFilter<
    SORT_LAYERED_LIST_POINTER,
    INPUT,
    CorrespondenceResult<3, LayeredPointReference>
    >
{
//  using AbstractTemplatedSortFilter<
//      SORT_LAYERED_LIST_POINTER,
//      INPUT,
//      CorrespondenceResult<3, LayeredPointReference>>::AbstractTemplatedSortFilter

 public:

  using base_type = AbstractTemplatedSortFilter<
      SORT_LAYERED_LIST_POINTER,
      INPUT,
      CorrespondenceResult<3, LayeredPointReference>>;

  using base_type::AbstractTemplatedSortFilter;

  using output_type = typename base_type::output_type;
  using point_type = typename base_type::point_type;
  using reference_type = typename base_type::reference_type;

  output_type operator()(const point_type& point, const INPUT& references) final {

    std::cout << "Return surf correspondence ...\n";

    output_type temp_output;

    temp_output.references[0] = reference_type(100, 200);
    temp_output.references[1] = reference_type(200, 300);
    temp_output.references[2] = reference_type(300, 400);

    return temp_output;

  }



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
    auto sort_result = (*sort_functor)(point);
    for (const auto& result: sort_result) {
      std::cout << result << "\n";
    }

    return true;
  };



};




} /* namespace playground */
#endif //ADW_CPP_PLAYGROUND_FUNWITHFUNCTORS_HPP
