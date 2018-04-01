#include <iostream>
#include <string>

#include "array.h"

struct Data
{
	int a = 0, b = 0;
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

void main(void)
{
	mystd::array<Data, 5> arr;
	arr[1] = { 10, 2, "hello" };
	std::cout << arr << std::endl;

	std::cin.get();
}