#include <iostream>
#include <type_traits>
#include "src/enumrange.hpp"

using namespace std;

int main() {

    cout << "Funcion for testing enum range class ..." << endl;

    cout << "First enum value: " << as_value(TestEnum::VAL0) << endl;

    cout << "Limited range: " << endl;

    auto enum_range = EnumRange<TestEnum, TestEnum::VAL0, TestEnum::VAL1, 1>();

    for (const auto& i: enum_range) {
        cout << as_value(i) << " = " << TEST_ENUM_TO_STRING.at(i) << endl;
    }

//    constexpr auto COMPLETE = EnumRange<TestEnum, TestEnum::FIRST, TestEnum::LAST, 1>();

    cout << "All values: " << endl;

    for (const auto& i: ALL_TEST_ENUMS) {
        cout << as_value(i) << " = " << TEST_ENUM_TO_STRING.at(i) << endl;
    }

    return 0;
}
