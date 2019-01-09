#include <iostream>
#include "array.h"
#include "string.h"
#include <string>

#include <vector>
#include <iterator>

struct data 
{ 
	int x; 
	mystd::string y; 

	data()
		: x(2), y("dan")
	{}

	data(int x, const mystd::string& y)
		: x(x), y(y)
	{}

	friend std::ostream& operator<<(std::ostream& stream, const data& d)
	{
		return stream << "(" << d.x << ", " << d.y << ")";
	}
};


void main(void)
{
	std::vector<int>::iterator i;

	mystd::string s = "HELLO WORLD!";
	mystd::string s2 = { 'a', 'b', 'c', 'd' };

	std::cout << s.length() << std::endl;
	std::cout << s2 << std::endl;
	std::cout << s2.length() << std::endl;
	system("PAUSE");
}

