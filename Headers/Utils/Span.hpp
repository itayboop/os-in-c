#pragma once

#include <cstdint>
#include <type_traits>

#include "KernelException.hpp"
#include "ThirdParty/Types/stddef.h"

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

	template <typename U>
	constexpr Span<T> copy_from_impl(const Span<U>& span_to_copy, size_t size);

	constexpr Span<T> copy_from(const Span<T>& span_to_copy, size_t size);

	constexpr Span<T> copy_from(const Span<std::add_const_t<T>>& span_to_copy, size_t size);

	constexpr T& operator[](uint32_t index);

	constexpr std::add_const_t<T>& operator[](uint32_t index) const

private:
	constexpr Span<T> copy_from_impl(const Span<U>& span_to_copy, size_t size);

protected:
	T* _ptr;
	uint32_t _count;
};
