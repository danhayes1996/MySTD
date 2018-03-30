#pragma once

#include "linkedlist.h"

void testLinkedList() {
	//CONSTRUCTOR
	mystd::linkedlist<int> list;
	std::cout << "Constructed -> \t\t\t" << list << "\t\t\t\t\tsize = " << list.size() << std::endl;

	//ADD 10 ITEMS
	for (int i = 0; i < 10; i++) list.push_back(i * 2);
	std::cout << "Added 10 items -> \t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//EMPTY
	std::cout << "Is empty? -> " << (list.empty() ? "true" : "false") << "\t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//REMOVE ITEM AT INDEX 2
	list.removeAt(2);
	std::cout << "Removed item at index 2 -> \t" << list << "\t\tsize = " << list.size() << std::endl;

	//ADDED ITEM AT INDEX 2
	list.push_back(2, -1);
	std::cout << "Added item at index 2 -> \t" << list << "\t\tsize = " << list.size() << std::endl;

	//CHANGE ITEM AT INDEX 2
	list.set(2, 500);
	std::cout << "Change item at index 2 -> \t" << list << "\tsize = " << list.size() << std::endl;

	//REMOVE 500 
	list.remove(500);
	std::cout << "Remove 500 -> \t\t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//REMOVE RANGE 2 TO 4
	list.removeRange(2, 4);
	std::cout << "Remove ranged 2 - 4 -> \t\t" << list << "\t\t\tsize = " << list.size() << std::endl;

	//REMOVE RANGED INCLUSIVE 0 TO 4
	list.removeRangeInclusive(0, 4);
	std::cout << "Remove range inclusive 0 - 4 -> " << list << "\t\t\t\t\tsize = " << list.size() << std::endl;

	//CLEAR
	list.clear();
	std::cout << "Clear -> \t\t\t" << list << "\t\t\t\t\tsize = " << list.size() << std::endl;

	//EMPTY
	std::cout << "Is empty? -> " << (list.empty() ? "true" : "false") << "\t\t" << list << "\t\t\t\t\tsize = " << list.size() << std::endl;

	//ADD 10 ITEMS
	for (int i = 0; i < 10; i++) list.push_back(i);
	std::cout << "Added 10 items -> \t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//CONTAINS 8
	std::cout << "Contains 8 -> " << (list.contains(8) ? "true" : "false") << "\t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//CONTAINS 25
	std::cout << "Contains 25 -> " << (list.contains(25) ? "true" : "false") << "\t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//[] OPERATOR
	std::cout << "list[2] -> " << list[2] << "\t\t\t" << list << "\t\tsize = " << list.size() << std::endl;

	//[] OPERATOR
	std::cout << "list[10] -> " << list[10] << "\t\t\t" << list << "\t\tsize = " << list.size() << std::endl;
}