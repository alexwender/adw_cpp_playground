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
};



} /* namespace playground */

#endif // DATACONTAINER_H
