#pragma once

#include "OsDefenitions/TypeTraits.hpp"
#include "OsDefenitions/stddef.h"

#include "KernelException.hpp"

template<typename T>
class Span
{
public:
	constexpr Span(): _ptr(nullptr), _count(0)
	{}

	constexpr Span(T* ptr, uint32_t count) : _ptr(ptr), _count(count)
	{
		if ((ptr == nullptr) && (count != 0))
		{
			THROW_KERNEL_EXCEPTION();
		}
	}

public:
	constexpr uint32_t size()
	{
		return _count;
	}

	constexpr T* begin()
	{
		return _ptr;
	}

	constexpr std::add_const_t<T>* begin() const
	{
		return _ptr;
	}

	constexpr T* end()
	{
		return _ptr + _count;
	}

	constexpr std::add_const_t<T>* end() const
	{
		return _ptr + _count;
	}

	constexpr Span<T> copy_from(const Span<T>& other, size_t size)
	{
		if (this == &other) {
			return *this;
		}
		// TODO: uncomment and make it work
		// if (size == this->_count)
		// [
		// 	THROW_KERNEL_EXCEPTION();
		// ]

		for (int i = 0; i < this->_count; ++i) {
			this->_ptr[i] = other[i];
		}

		return *this;
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
