#pragma once

#include <cstdint>
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
	constexpr const T* cbegin() const
	{
		return _ptr;
	}

	constexpr const T* cend() const
	{
		return _ptr + _count;
	}

	constexpr T* begin() const
	{
		return _ptr;
	}

	constexpr T* end() const
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

	constexpr const T& operator[](uint32_t index) const
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
