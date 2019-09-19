#include <iostream>

#include <MySTD\string.h>
#include <MySTD\pointer.h>

int main(int argc, char** argv)
{
	{
		mystd::unique<int> u;
		*u = 5;
		std::cout << *u << std::endl;
	}
	
	{
		mystd::unique<mystd::string> u;
		*u = "abc";
		std::cout << *u << std::endl;
	}

	{
		mystd::unique<mystd::string> u(new mystd::string);
		*u = "123";
		std::cout << *u << std::endl;
	}

	{
		mystd::unique<mystd::string> u(new mystd::string("hello"));
		std::cout << *u << std::endl;
		*u = "qwerty";
		std::cout << u->to_upper() << std::endl;
	}

	system("PAUSE");
	return 0;
}