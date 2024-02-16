#pragma once

#include "OsDefenitions/stddef.h"

#include "Span.hpp"
#include "KernelException.hpp"

template<typename T, uint32_t MAX_SIZE>
class Vector : public Span<T>
{
public:
	constexpr explicit Vector(const T* arr, uint32_t size) : Vector(size)
	{
		for (uint32_t i = 0; i < this->_count; ++i)
		{
			_arr[i] = arr[i];
		}
	};

	constexpr explicit Vector() : Span<T>(_arr, 0)
	{}

	constexpr explicit Vector(uint32_t initial_size) : Vector()
	{
		resize(initial_size);
	};

public:
	void push_back(const T& value)
	{
		if (this->_count == MAX_SIZE)
		{
			THROW_KERNEL_EXCEPTION();
		}

		_arr[++this->_count] = value;
	};

	constexpr void resize(uint32_t new_size)
	{
		if (new_size > MAX_SIZE)
		{
			THROW_KERNEL_EXCEPTION();
		}

		this->_count = new_size;
	};

private:
	T _arr[MAX_SIZE];
};
