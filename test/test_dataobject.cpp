#include <iostream>
#include <string>

#include "src/dataobject.h"
#include "src/datacontainer.h"

using namespace std;
using namespace playground;

int main(int argc, char** argv) {

    std::cout << "Test file for data object\n";

    // Create simple data object
    DataFloat data_obj(0.0f, 0.0f);
    data_obj.setData_1(1.0f);
    data_obj.setData_2(2.0f);

    std::string temp_str = data_obj.getString();

    std::cout << data_obj.getString() << "\n";

    std::cout << "Using << operator:\n";
    std::cout << data_obj << "\n";

    DataContainer<DataFloat> obj_cont;

    std::cout << "Explicit copy constructor of Data Object\n";

    DataFloat data_obj2 = data_obj;

    std::cout << "Creating object 3\n";
    std::cout << "data_obj2: " << data_obj2 << "\n";

    DataFloat data_obj3(0.0f, 0.0f);

    std::cout << "Explicit copy assignment of Data Object 3\n";

    data_obj3 = data_obj;

    std::cout << "Explicit move constructor for from data object 3 to 4\n";

    DataFloat data_obj4 = std::move(data_obj3);
    data_obj4.setData_1(4.0f);
    data_obj4.setData_2(8.0f);
    std::cout << "data object4:\n" << data_obj4 << "\n";

    std::cout << "Explicit move assignment from data object 2 to 4\n";
//    data_obj4 = std::move(data_obj2);

    std::cout << "Constructing data obj6\n";
    DataFloat data_obj6(6.0f, 12.0f);


    std::cout << "Adding data by value:\n";
    obj_cont.addDataByValue(data_obj);
//    std::cout << "Adding data by const reference\n";
//    obj_cont.addDataByReference(data_obj);

    std::cout << "Moving data by value\n";
    obj_cont.addDataByValue(std::move(data_obj4));

//    std:: cout << "obj4 " << data_obj4.getString() << "\n";

//    std::cout << "Move data\n";
//    obj_cont.addDataByRRef(std::move(data_obj4));
//    obj_cont.addDataByValue(data_obj4);
    std::cout << "Construct by value in place \n";
    obj_cont.addDataByRRef(std::move(DataFloat(5.0f, 10.0f)));

    std::cout << "Add Object 6 by reference\n";
    obj_cont.addDataByReference(data_obj6);

    std::cout << "add by RRef with move: \n";
    obj_cont.addDataByRRef(std::move(data_obj6));

    obj_cont.print();

    std::vector<DataFloat> test_vec;

    std::cout << "Emplace back in test_vec ...\n";
    test_vec.emplace_back(DataFloat{1.0, 2.0});

    std::cout << "Construct data_obj6_vec\n";
    DataFloat data_obj6_vec(6.0f, 12.0f);

    std::cout << "add by Value\n";
    test_vec.emplace_back(std::move(data_obj6_vec));



//    for (const auto& item: test_vec) {
//        std::cout << item << "n";
//    }

    std::cout << "test_vec.size(): " << test_vec.size() << "\n";

    for(size_t i = 0; i < test_vec.size(); i++ ) {
        std::cout << test_vec[i] << "\n";
    }







}
