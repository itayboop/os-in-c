#include "Utils/Span.hpp"

template<typename T>
constexpr Span<T>::Span(T* ptr, uint32_t count) : _ptr(ptr), _count(count)
{
    if ((ptr == nullptr) && (count != 0))
    {
        THROW_KERNEL_EXCEPTION();
    }
}

template<typename T>
constexpr std::add_const_t<T>* Span<T>::begin() const
{
    return _ptr;
}

template<typename T>
constexpr std::add_const_t<T>* Span<T>::end() const
{
    return _ptr + _count;
}

template<typename T>
constexpr T* Span<T>::begin()
{
    return _ptr;
}

template<typename T>
constexpr T* Span<T>::end()
{
    return _ptr + _count;
}

template<typename T>
constexpr uint32_t Span<T>::size()
{
    return _count;
}

template <typename T>
template <typename U>
constexpr Span<T> Span<T>::copy_from_impl(const Span<U>& span_to_copy, size_t size)
{
    if (this == &span_to_copy) {
        return *this;
    }

    static_assert(size == this->_count, "Size mismatch in copy_from");
    for (int i = 0; i < this->_count; ++i) {
        this->_ptr[i] = span_to_copy[i];
    }

    return *this;
}

template <typename T>
constexpr Span<T> Span<T>::copy_from(const Span<T>& span_to_copy, size_t size)
{
    return copy_from_impl(span_to_copy, size);
}

template <typename T>
constexpr Span<T> Span<T>::copy_from(const Span<std::add_const_t<T>>& span_to_copy, size_t size)
{
    return copy_from_impl(span_to_copy, size);
}

template <typename T>
constexpr T& Span<T>::operator[](uint32_t index)
{
    if (index >= _count)
    {
        THROW_KERNEL_EXCEPTION();
    }

    return _ptr[index];
}

template <typename T>
constexpr std::add_const_t<T>& Span<T>::operator[](uint32_t index) const
{
    if (index >= _count)
    {
        THROW_KERNEL_EXCEPTION();
    }

    return _ptr[index];
}

