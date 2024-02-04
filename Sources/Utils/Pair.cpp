#include "Utils/Pair.hpp"

template<typename T, typename U>
constexpr T& Pair<T, U>::first()
{
    return _first;
}

template<typename T, typename U>
constexpr U& Pair<T, U>::second()
{
    return this->_second;
}

template<typename T, typename U>
constexpr const T& Pair<T, U>::first() const {
    return _first;
}

template<typename T, typename U>
constexpr const U& Pair<T, U>::second() const {
    return _second;
}
