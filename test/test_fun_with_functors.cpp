//
// Created by alex on 08.04.18.
//

#include <gtest/gtest.h>

#include <iostream>

#include <src/FunWithFunctors.hpp>

namespace playground {

TEST(TestFunWithFunctors, SimpleTest) {

  std::cout << "Simple FunWithFunctors test ...\n";

  std::unique_ptr<Functor<double>> functor(new Functor<double>(2.0));

  auto perf_function = makePerformFunction(std::move(functor));

  perf_function.performFunction(2.0);

//  auto perf_function_char = makePerformFunction(Functor<char>('a'));
//
//  perf_function_char.performFunction('b');

  auto layered_points = LAYERED_POINT_LIST::createEmpty(4);

  for (auto& layer: layered_points->layers) {

    layer.points.push_back(POINT(0.0, 0.0, 0.0));

  }

  for (auto& layer: layered_points->layers) {

    std::cout << layer.points.size() << "\n";

  }
//
  std::unique_ptr<SortLayeredList> sort_list(new SortLayeredList(layered_points));
//
//  auto ret_val = sort_list(POINT(0.0, 1.0, 0.0));

  ProcessLayeredList<SortLayeredList::UPtr> process_list(std::move(sort_list));

  process_list.processPoint(POINT(0.0, 0.0, 0.0));


  std::unique_ptr<TemplatedSortLayeredList<decltype(layered_points)>> templated_sort_list(
      new TemplatedSortLayeredList<decltype(layered_points)>(layered_points));

  ProcessLayeredList<decltype(templated_sort_list)> process_list_2(std::move(templated_sort_list));

  std::cout << "process_list_2\n";

  process_list_2.processPoint(POINT(0.0, 0.0, 1.0));

  std::unique_ptr<TemplatedSortLayeredList<decltype(layered_points)>> templated_sort_list_single(
      new TemplatedSortLayeredList<decltype(layered_points)>(layered_points));

  const auto point = POINT(0.0, 10.0, 0.0);

  auto sort_result = (*templated_sort_list_single)(point);

  EdgeTemplatedSortFilter<
      decltype(layered_points),
      TemplatedSortLayeredList<decltype(layered_points)>::output_container
      > edge_filter(layered_points);
//
  auto edge_ref = edge_filter(point, sort_result);
//
  std::cout << "reference: " << edge_ref << "\n";


  SurfTemplatedSortFiler<
      decltype(layered_points),
      TemplatedSortLayeredList<decltype(layered_points)>::output_container
      > surf_filter(layered_points);

  auto surf_ref = surf_filter(point, sort_result);

  std::cout << "surf references: " << surf_ref << "\n";



  ASSERT_EQ(true, true);




}
} /* namespace playground */

int main (int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}