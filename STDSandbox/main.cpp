#include <iostream>

#include <MySTD\string.h>
#include <MySTD\array.h>
#include <MySTD\arraylist.h>
#include <MySTD\algorithm.h>
#include <MySTD\pair.h>

int main(int argc, char** argv)
{

	mystd::string s = "Hello-World!-my-name-is-dan.";
	auto words = s.split('-');
	std::cout << words << std::endl;
	
	system("PAUSE");
	return 0;
}