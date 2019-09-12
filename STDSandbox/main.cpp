#include <iostream>

#include <MySTD\string.h>
#include <MySTD\array.h>
#include <MySTD\arraylist.h>
#include <MySTD\algorithm.h>
#include <MySTD\pair.h>
#include <MySTD\btree.h>

int main(int argc, char** argv)
{
	mystd::binary_tree<int> t;
	t.insert(5);
	t.insert(3);
	t.insert(1);
	t.insert(2);
	t.insert(7);
	t.insert(6);
	t.insert(10);
	t.insert(4);
	std::cout << t << std::endl;

	t.clear();

	std::cout << t << std::endl;
	system("PAUSE");
	return 0;
}