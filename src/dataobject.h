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
    DataObject(const T val1, const T val2)
        :m_data_1(val1), m_data_2(val2)
    {
        std::cout << "DataObject Contructor\n";
    }

    // Copy Constructor
    DataObject(const DataObject& other)
        :m_data_1(other.m_data_1),
          m_data_2(other.m_data_2)
    {
        std::cout << "Copy constructor\n";

    }

    // Copy Assignment
    DataObject& operator=(const DataObject& other) {
        std::cout << "DataObject Copy Assignment\n";
        if (&other != this) {
            this->m_data_1 = other.m_data_1;
            this->m_data_2 = other.m_data_2;
        }
        return *this;
    }

    // Move Constructor

    DataObject(DataObject&& rhs) noexcept
        : m_data_1(std::move(rhs.m_data_1)),
            m_data_2(std::move(rhs.m_data_2))
    {

        std::cout << "DataObject Move Constructor\n";
    }

    // Move Assignment Operator

    DataObject& operator=(DataObject&& other) noexcept {

        std::cout << "DataObject Move assignment\n";

        this->m_data_1 = std::move(other.m_data_1);
        this->m_data_2 = std::move(other.m_data_2);
        return *this;

    }

    std::string getString() const
    {
//        std::cout << "DataObject: \n";
//        std::cout << "m_data_1: " << m_data_1 << "\n";
//        std::cout << "m_data_2: " << m_data_2 << "\n";

        std::stringstream temp_str;
//        temp_str << "DataObject: \n";
//        temp_str << "m_data_1: " << m_data_1 << "\n";
//        temp_str << "m_data_2: " << m_data_2 << "\n";
        temp_str << m_data_1 << ", " << m_data_2;

        return temp_str.str();


    }

//    ~DataObject() {

//    }

//    std::ostream& operator<<(std::ostream& os)
//    {
//        os << this->m_data_1 << ", " << this->m_data_2;
//        return os;
//    }

    friend std::ostream& operator<<(std::ostream& os, DataObject& item){
        os << item.m_data_1 << ", " << item.m_data_2;
        return os;
    }

    // getters and setters



    T getData_1() const{
        return m_data_1;
    }
    void setData_1(const T &data_1){
        m_data_1 = data_1;
    }

    T getData_2() const {
        return m_data_2;
    }
    void setData_2(const T &data_2){
        m_data_2 = data_2;
    }

protected:
    T m_data_1;
    T m_data_2;

};

//template<typename T>
//std::ostream &operator<<(std::ostream & os, const DataObject<T> &item)
//{
//    os << "test";
//    return os;

//}



typedef DataObject<float> DataFloat;

} /* namespace playgound */




#endif // DATAOBJECT_H
