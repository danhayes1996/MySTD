#include <iostream>
#include <string>
#include "set.h"
#include "arraylist.h"
#include <set>
#include "compare.h"

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
		if (left.a < right.a) return true;
		if (left.b < right.b) return true;
		if (left.c < right.c) return true;
		return false;
	}
};

void main(void)
{
	const mystd::set<Data, comp> s = { {1, 1, "1"},{ 2, 2, "2" },{ 3, 3, "3" }};
	std::cout << s << std::endl;

	mystd::set<int> s2;

	std::cin.get();
}