#include <iostream>
#include <iomanip>

using namespace std;

int normal_function(int val1, int val2, bool switch_on) {

    int return_value = 0;

    if (switch_on) {

        return_value = (val1 + val2) * (val2 + val2);

    } else {

        return_value = (val1 * val2) + (val1 * val1);
    }

    return return_value;
}

template<typename T>
void print_result(string description, T value) {
    cout << setw(30) << left << description << ": " << setw(20) << right << value << endl;
}

int main() {

    int val1 = 5;
    int val2 = 10;

    auto result_normal_true = normal_function(val1, val2, true);
    auto result_normal_false = normal_function(val1, val2, false);

    print_result("result_normal_true", result_normal_true);
    print_result("result_normal_false", result_normal_false);
//    cout << "result_normal_true:  " << result_normal_true << endl;
//    cout << "result_normal_false: " << result_normal_false << endl;

    return 0;
}
