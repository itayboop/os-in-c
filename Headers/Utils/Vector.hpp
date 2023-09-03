#pragma once

#include "Span.hpp"
#include "KernelException.hpp"

template<typename T, uint32_t MAX_SIZE>
class Vector : public Span<T>
{
public:
	constexpr explicit Vector(const T* arr, uint32_t size) : Vector(size)
	{
		for (uint32_t i = 0; i < _count; ++i)
		{
			_arr[i] = arr[i];
		}
	}

	constexpr explicit Vector() : Span(_arr, 0)
	{}

	constexpr explicit Vector(uint32_t initial_size) : Vector()
	{
		resize(initial_size);
	}

public:
	void push_back(const T& value)
	{
		if (_count == MAX_SIZE)
		{
			THROW_KERNEL_EXCEPTION();
		}

		_arr[++_count] = value;
	}

	constexpr void resize(uint32_t new_size)
	{
		if (new_size > MAX_SIZE)
		{
			THROW_KERNEL_EXCEPTION();
		}

		_count = new_size;
	}

private:
	T _arr[MAX_SIZE];
};
