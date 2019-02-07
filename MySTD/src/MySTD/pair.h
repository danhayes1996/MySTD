#pragma once

#include <ostream>

namespace mystd {

	template<typename T1, typename T2>
	struct pair
	{
		T1 first;
		T2 second;

		pair()
			: first(T1()), second(T2())
		{}

		pair(const T1& x, const T2& y)
			: first(x), second(y)
		{}

		pair(const pair& other)
			: first(other.first), second(other.second)
		{}
		
		pair& operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}

		void swap(pair& other)
		{
			T1 fst = first;
			T2 sec = second;
			first = other.first;
			second = other.second;
			other.first = fst;
			other.second = sec;
		}

		friend std::ostream& operator<<(std::ostream& stream, const pair& p)
		{
			return stream << "pair<" << typeid(T1).name() << ", " << typeid(T2).name() << ">:[" << p.first << ", " << p.second << "]";
		}
	};

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 first, T2 second)
	{
		return pair<T1, T2>(first, second);
	}
}
