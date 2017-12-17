#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <vector>
#include <iostream>

namespace playground {

template<typename T>
class DataContainer
{
public:

    typedef T value_type;
    typedef std::vector<T> container_type;

    DataContainer()
    {
        std::cout << "DataObject Constructor\n";
    }

    bool addDataByValue(const T data);

    bool addDataByReference(const T& data);

    bool addDataByRRef(T&& data);

    void print();

protected:

    DataContainer::container_type m_data_container;

};



} /* namespace playground */

#endif // DATACONTAINER_H
