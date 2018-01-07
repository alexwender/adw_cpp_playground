#ifndef ENUMRANGE_H
#define ENUMRANGE_H

#include <type_traits>
#include <algorithm>
#include <map>


enum class TestEnum: uint32_t {
    VAL0 = 0,
    VAL1,
    VAL2,
    FIRST=VAL0,
    LAST=VAL2,
};

const std::map<TestEnum, std::string> TEST_ENUM_TO_STRING = {
    {TestEnum::VAL0, "Val0"},
    {TestEnum::VAL1, "Val1"},
    {TestEnum::VAL2, "Val2"}
};

template<typename Enumeration>
auto as_value(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template<
        typename TYPE,
        TYPE FROM,
        TYPE TO,
        typename std::underlying_type<TYPE>::type STEP>
class EnumRange
{
public:

    class iterator: public std::iterator<
            std::input_iterator_tag,
            long,
            long,
            const long*,
            long>{
        TYPE num = FROM;

    public:
        explicit iterator(TYPE _num = 0) : num(_num) {}
        iterator& operator++() {
            num = TO >= FROM ? static_cast<TYPE>(as_value(num) + STEP): static_cast<TYPE>(as_value(num) - STEP);
            return *this;
        }
        iterator operator++(int) {
            iterator retval = *this;
            ++(*this);
            return retval;
        }
        bool operator==(iterator other) const  {
            return num = other.num;
        }
        bool operator!=(iterator other) const {
            return num != other.num;
        }
        const TYPE& operator*() const {
            return num;
        }
    };

    iterator begin() const {
        return iterator(FROM);
    }

    iterator end() const {
        return iterator(TO >= FROM ? static_cast<TYPE>(as_value(TO) + STEP): static_cast<TYPE>(as_value(TO) - STEP));
    }


};

#endif // ENUMRANGE_H
