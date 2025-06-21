#pragma once

#include <stddef.h>
#include <stdint.h>

#include "OsDefinitions/TypeTraits.hpp"
#include "Utils/Functions/PrintUtils.hpp"
#include "KernelException.hpp"

template<typename T>
class Span
{
public:
	constexpr Span() : _ptr(nullptr), _count(0)
	{}

	constexpr Span(const Span<T> &other) : _ptr(other._ptr), _count(other._count)
	{}

	constexpr Span(T *ptr, uint32_t count) : _ptr(ptr), _count(count)
	{
		if ((ptr == nullptr) && (count > 0))
		{
			PrintUtils::printk("PTR is null but count is bigger than zero.\n");
			THROW_KERNEL_EXCEPTION();
		}
	}

public:
	constexpr uint32_t size()
	{
		return this->_count;
	}

	constexpr T * begin()
	{
		return this->_ptr;
	}

	constexpr std::add_const_t<T> * begin() const
	{
		return this->_ptr;
	}

	constexpr T * end()
	{
		return this->_ptr + this->_count;
	}

	constexpr std::add_const_t<T> * end() const
	{
		return this->_ptr + this->_count;
	}

	constexpr Span<T> copy_from(const Span<T> &other, size_t size)
	{
		if (this == &other) {
			return *this;
		}

		if (size > this->_count)
		{
			PrintUtils::printk("Source size is bigger than destination size. ");
			THROW_KERNEL_EXCEPTION();
		}

		for (unsigned int i = 0; i < size; ++i) {
			this->_ptr[i] = other[i];
		}

		return *this;
	}

	constexpr T &operator[](uint32_t index)
	{
		if (index >= this->_count)
		{
			PrintUtils::printk("Index out of bounds. ");
			THROW_KERNEL_EXCEPTION();
		}

		return this->_ptr[index];
	}

	constexpr std::add_const_t<T> &operator[](uint32_t index) const
	{
		if (index >= this->_count)
		{
			PrintUtils::printk("Index out of bounds. ");
			THROW_KERNEL_EXCEPTION();
		}

		return this->_ptr[index];
	}

protected:
	T *_ptr;
	uint32_t _count;
};
