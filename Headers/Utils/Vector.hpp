#pragma once

#include "OsDefenitions/stddef.h"

#include "Span.hpp"
#include "KernelException.hpp"

template<typename T, uint32_t MAX_SIZE>
class Vector : public Span<T>
{
public:
	constexpr explicit Vector(const T* arr, uint32_t size);

	constexpr explicit Vector() : Span<T>(_arr, 0)
	{}

	constexpr explicit Vector(uint32_t initial_size);

public:
	void push_back(const T& value);

	constexpr void resize(uint32_t new_size);

private:
	T _arr[MAX_SIZE];
};
