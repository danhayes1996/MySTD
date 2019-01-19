#include <iostream>
#include "arraylist.h"

void main(void)
{
	mystd::arraylist<int> s = { 1,3,4,6 };
	std::cout << s << std::endl;
	s.push_front(12);
	std::cout << s << std::endl;
	s.push_front(67);
	std::cout << s << std::endl;
	/*for (mystd::arraylist<int>::reverse_iterator it = s.rbegin(); it != s.rend(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	mystd::string str = "abcdef";
	for (mystd::string::const_iterator i = str.cbegin(); i != str.cend(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	*/
	system("PAUSE");
}