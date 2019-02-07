#pragma once

#include "pair.h"

namespace mystd {

	/* searches for an element equal to the value specified
	   @return an iterator pointing to the value if its found, otherwise it will return the iterator 'last'
	*/
	template<typename InputIterator, typename T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; ++first)
			if (*first == val) return first;
		return last;
	}

	/* swaps the values x and y. */
	template<typename T>
	void swap(T& x, T& y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}

	/* Assigns a given value to the elements from first to last. */
	template<typename InputIterator, typename T>
	void fill(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; ++first)
			*first = val;
	}

	/* @return the greater of x and y */
	template<typename T>
	const T& max(const T& x, const T& y)
	{
		return x > y ? x : y;
	}

	/* @return the greatest value between the two iterators specified. */
	template<typename InputIterator>
	InputIterator max_element(InputIterator first, InputIterator last)
	{
		InputIterator biggest = first;
		++first;
		for (; first != last; ++first)
			if (*first > *biggest) biggest = first;
		return biggest;
	}

	/* @return the smaller of x and y */
	template<typename T>
	const T& min(const T& x, const T& y)
	{
		return x < y ? x : y;
	}

	/* @return the smallest value between the two iterators specified. */
	template<typename InputIterator>
	InputIterator min_element(InputIterator first, InputIterator last)
	{
		InputIterator smallest = first;
		++first;
		for (; first != last; ++first)
			if (*first < *smallest) smallest = first;
		return smallest;
	}

	/* @return the smallest value, followed by the largest value in a pair. */
	template<typename T>
	mystd::pair<T, T> minmax(const T& x, const T& y)
	{
		if (y < x) return mystd::pair<T, T>(y, x);
		return mystd::pair<T, T>(x, y);
	}

	/* @return the smallest and greatest element in the range from first to last. */
	template<typename InputIterator>
	mystd::pair<InputIterator, InputIterator> minmax_element(InputIterator first, InputIterator last)
	{
		InputIterator smallest = first;
		InputIterator largest = first;
		++first;

		for (; first != last; ++first)
		{
			if (*first < *smallest) smallest = first;
			if (*first > *largest)  largest = first;
		}

		return mystd::pair<InputIterator, InputIterator>(smallest, largest);
	}

	/* @return the value clamped between values hi and lo. */
	template<typename T>
	const T& clamp(const T& val, const T& min, const T& max)
	{
		if (val > max) return max;
		if (val < min) return min;
		return val;
	}

	/* @return the number of increments needed to get from first to last */
	template<typename InputIterator>
	int distance(InputIterator first, InputIterator last)
	{
		int dist = 0;
		for (; first != last; ++first)
			dist++;
		return dist;
	}
}
