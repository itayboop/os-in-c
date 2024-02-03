#pragma once

#include <cstdint>
#include <type_traits>
#include "KernelException.hpp"

template<typename T>
class Span
{
public:
	constexpr Span(): _ptr(nullptr), _count(0)
	{}

	constexpr explicit Span(T* ptr, uint32_t count) : _ptr(ptr), _count(count)
	{
		if ((ptr == nullptr) && (count != 0))
		{
			THROW_KERNEL_EXCEPTION();
		}
	}

public:
	constexpr std::add_const_t<T>* begin() const
	{
		return _ptr;
	}

	constexpr std::add_const_t<T>* end() const
	{
		return _ptr + _count;
	}

	constexpr T* begin()
	{
		return _ptr;
	}

	constexpr T* end()
	{
		return _ptr + _count;
	}

	constexpr uint32_t size()
	{
		return _count;
	}

	template <typename U>
	constexpr Span<T> copy_from_impl(const Span<U>& span_to_copy, size_t size)
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

	constexpr Span<T> copy_from(const Span<T>& span_to_copy, size_t size)
	{
		return copy_from_impl(span_to_copy, size);
	}

	constexpr Span<T> copy_from(const Span<std::add_const_t<T>>& span_to_copy, size_t size)
	{
		return copy_from_impl(span_to_copy, size);
	}

	constexpr T& operator[](uint32_t index)
	{
		if (index >= _count)
		{
			THROW_KERNEL_EXCEPTION();
		}

		return _ptr[index];
	}

	constexpr std::add_const_t<T>& operator[](uint32_t index) const
	{
		if (index >= _count)
		{
			THROW_KERNEL_EXCEPTION();
		}

		return _ptr[index];
	}

protected:
	T* _ptr;
	uint32_t _count;
};
