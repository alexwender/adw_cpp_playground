#include <iostream>
#include <type_traits>
#include "src/enumrange.hpp"

using namespace std;

int main() {

    cout << "Funcion for testing enum range class ..." << endl;

    cout << "First enum value: " << as_value(TestEnum::VAL0) << endl;

    auto enum_range = EnumRange<TestEnum, TestEnum::FIRST, TestEnum::LAST, 1>();

    constexpr auto COMPLETE = EnumRange<TestEnum, TestEnum::FIRST, TestEnum::LAST, 1>();

    for (const auto& i: COMPLETE) {
        cout << as_value(i) << " = " << TEST_ENUM_TO_STRING.at(i) << endl;
    }

    return 0;
}
