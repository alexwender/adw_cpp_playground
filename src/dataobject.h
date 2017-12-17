#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <iostream>
#include <sstream>
#include <string>

namespace playground {

template<typename T>
class DataObject
{
public:
    DataObject()
    {
        std::cout << "DataObject Contructor\n";
    }

    std::string getString() const
    {
//        std::cout << "DataObject: \n";
//        std::cout << "m_data_1: " << m_data_1 << "\n";
//        std::cout << "m_data_2: " << m_data_2 << "\n";

        std::stringstream temp_str;
        temp_str << "DataObject: \n";
        temp_str << "m_data_1: " << m_data_1 << "\n";
        temp_str << "m_data_2: " << m_data_2 << "\n";

        return temp_str.str();


    }

protected:
    T m_data_1;
    T m_data_2;
};

typedef DataObject<float> DataFloat;

} /* namespace playgound */




#endif // DATAOBJECT_H
