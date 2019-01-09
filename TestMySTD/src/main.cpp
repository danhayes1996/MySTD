#include <iostream>
#include "btree.h"

void main(void)
{
	mystd::binary_tree<int> t;
	t.insert(42);
	t.insert(1);
	t.insert(5);
	t.insert(2);
	t.insert(10);
	t.insert(4);
	t.insert(20);
	t.insert(25);
	t.insert(100);

	std::cout << t.search(12) << std::endl;


	std::cin.get();
}