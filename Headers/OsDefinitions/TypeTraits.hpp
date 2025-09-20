#pragma once
#include <stddef.h>

namespace std
{
template<typename T>
struct add_const {
    typedef const T type;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

using size_t = size_t;

struct nothrow_t {};
constexpr nothrow_t nothrow{};
}
