#include <iostream>
#include <iomanip>

#include "src/dataobject.h"
#include "src/datacontainer.h"

using namespace std;

namespace playground {



template class DataContainer<DataObject<float> >;

template<typename T>
bool DataContainer<T>::addDataByValue(const DataContainer::value_type data)
{

    this->m_data_container.emplace_back(data);

    return true;

}

template<typename T>
bool DataContainer<T>::addDataByReference(const DataContainer::value_type &data)
{
    this->m_data_container.emplace_back(data);

}

template<typename T>
bool DataContainer<T>::addDataByRRef(DataContainer::value_type &&data)
{
    this->m_data_container.emplace_back(std::move(data));

}

template<typename T>
void DataContainer<T>::print()
{

    size_t counter = 0;
    for (const auto& elem: this->m_data_container) {
        std::cout << "["  << std::setw(12) << counter << "]" << elem.getString() << "\n";
        counter++;
    }

}

} /* namespace playground */
