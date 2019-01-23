#pragma once

namespace mystd {

	template<typename InputIterator, typename T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; ++first)
			if (*first == val) return first;
		return last;
	}

	template<typename T>
	void swap(T& x, T& y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}
}
