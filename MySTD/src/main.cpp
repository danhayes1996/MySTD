#include <iostream>

#include "string.h"

void main(void)
{
	mystd::string str = "abc";
	mystd::string str2 = "abc";
	std::cout << (str <= str2) << std::endl;

	std::cin.get();
}