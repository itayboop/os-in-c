#pragma once

template<typename T, typename U>
class Pair final
{
public:
	constexpr explicit Pair()
	{}

	constexpr explicit Pair(const T& first, const U& second) : _first(first), _second(second)
	{}

public:
	constexpr T& first()
	{
		return this->_first;
	}
	constexpr U& second()
	{
		return this->_second
	}

	constexpr const T& first() const
	{
		return this->_first;
	}
	constexpr const U& second() const
	{
		return this->_second;
	}

private:
	T _first;
	U _second;
};
