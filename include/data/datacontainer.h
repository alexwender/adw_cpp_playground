#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <vector>
#include <iostream>
#include <iomanip>

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

    void addDataByValue(const T data);

    void addDataByReference(const T& data);

    void addDataByRRef(T&& data);

    void print();

protected:

    DataContainer::container_type m_data_container;

};

template<typename T>
void DataContainer<T>::addDataByValue(const DataContainer::value_type data)
{

    this->m_data_container.emplace_back(data);
}

template<typename T>
void DataContainer<T>::addDataByReference(const DataContainer::value_type &data)
{
    this->m_data_container.emplace_back(data);

}

template<typename T>
void DataContainer<T>::addDataByRRef(DataContainer::value_type &&data)
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



template class DataContainer<DataObject<float> >;

} /* namespace playground */

#endif // DATACONTAINER_H
