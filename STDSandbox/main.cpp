#include <iostream>

#include <MySTD\array.h>
#include <MySTD\string.h>
#include <MySTD\algorithm.h>

#include <vector>

void printVector(const std::vector<int>& v)
{
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	mystd::array<int, 4> s = { 1,3,6,2 };
	std::cout << s << std::endl;
	std::cout << "a=" << *s.begin() << ", b=" << *(s.end() - 1) << std::endl;
	mystd::swap(*s.begin(), *(s.end() - 1));
	std::cout << "a=" << *s.begin() << ", b=" << *(s.end() - 1) << std::endl;
	std::cout << s << std::endl << std::endl;

	std::vector<int> v = { 1,3,6,2 };
	printVector(v);
	std::cout << "a=" << *v.begin() << ", b=" << *(v.end() - 1) << std::endl;
	mystd::swap(*v.begin(), *(v.end() - 1));
	std::cout << "a=" << *v.begin() << ", b=" << *(v.end() - 1) << std::endl;
	printVector(v);
	system("PAUSE");
}