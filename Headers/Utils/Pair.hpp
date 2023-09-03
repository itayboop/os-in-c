#pragma once

template<typename T, typename U>
class Pair final
{
public:
	constexpr explicit Pair()
	{}

	constexpr explicit Pair(const T& first, const U& second) : _first(first), _second(second)
	{}

private:
	constexpr T& first();
	constexpr U& second();

	constexpr const T& first() const;
	constexpr const T& second() const;

private:
	T _first;
	U _second;
};
