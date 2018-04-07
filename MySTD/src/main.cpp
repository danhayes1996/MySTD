#include <iostream>
#include <string>
#include "set.h"
#include "arraylist.h"

struct Data
{
	int a, b;
	std::string c;

	bool operator==(const Data& other)
	{
		return a == other.a && b == other.b && c == other.c;
	}

	bool operator!=(const Data& other)
	{
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Data& data)
	{
		return stream << "(" << data.a << ", " << data.b << ", " << data.c << ")";
	}
};


struct comp
{
	bool operator()(const Data& left, const Data& right)
	{
		if (left.a > right.a) return true;
		if (left.b > right.b) return true;
		if (left.c > right.c) return true;
		return false;
	}
};


void main(void)
{
	const mystd::arraylist<Data> s = { {1, 2, "1"}, { 24, 122, "124" }, { 1, 2, "1" } };
	
	std::cout << s[1] << std::endl;

	std::cin.get();
}