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
	// TODO: are cbegin and cend really needed?
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

	constexpr T& operator=(Span<T> spanToCopy)
	{
		this->_count = spanToCopy._count;
		this->_ptr = spanToCopy._ptr;
	}

	constexpr std::add_const_t<T>& operator=(Span<const T> spanToCopy)
	{
		this->_count = spanToCopy._count;
		this->_ptr = spanToCopy._ptr;
	}

protected:
	T* const _ptr;
	uint32_t _count;
};
