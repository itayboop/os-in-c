#pragma once

#include "OsDefenitions/TypeTraits.hpp"

#include "KernelException.hpp"

template<typename T>
class Span
{
public:
	constexpr Span(): _ptr(nullptr), _count(0)
	{}

	constexpr explicit Span(T* ptr, uint32_t count);

public:
	constexpr uint32_t size();

	constexpr T* begin();
	constexpr std::add_const_t<T>* begin() const;

	constexpr T* end();
	constexpr std::add_const_t<T>* end() const;

	constexpr Span<T> copy_from(const Span<T>& span_to_copy, size_t size);

	constexpr T& operator[](uint32_t index);

	constexpr std::add_const_t<T>& operator[](uint32_t index) const;

protected:
	T* _ptr;
	uint32_t _count;
};
