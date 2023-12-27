#pragma once

#include <cstdint>
#include <type_traits>
#include "KernelException.hpp"

template<typename T>
class Span
{
public:
	constexpr explicit Span(T* ptr, uint32_t count) : _ptr(ptr), _count(count)
	{
		if ((ptr == nullptr) && (count != 0))
		{
			THROW_KERNEL_EXCEPTION();
		}
	}

public:
	constexpr std::add_const_t<T>* cbegin() const
	{
		return _ptr;
	}

	constexpr std::add_const_t<T>* cend() const
	{
		return _ptr + _count;
	}

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

	constexpr uint32_t size() const
	{
		return _count;
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
	T* const _ptr;
	uint32_t _count;
};
