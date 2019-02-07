#pragma once
#include <iostream>

#include <MySTD/string.h>
#include <MySTD/array.h>
#include <MySTD/arraylist.h>
#include <MySTD/linkedlist.h>
#include <MySTD/timer.h>

struct Data
{
	int a, b;
	mystd::string c;

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

#define TIMES_COUNT 1000
#define ADD_COUNT	1000
void testarraylist() {
	float times[TIMES_COUNT];
	mystd::timer t, t2;
	for (float i = 0.0f; i < TIMES_COUNT; i++) {
		t.reset();
		mystd::arraylist<Data> a;
		for (int j = 0; j < ADD_COUNT; j++)
			a.push_back({ j, j * 2, "WTF" });
		times[(int)i] = t.timeElapsed() * 1000.0f;
		std::cout << "array list: " << ((int)(i / TIMES_COUNT * 100)) << "% time: " << t2.timeElapsed() << "s\r";
	}

	//timer stats
	float elapsed = t2.timeElapsed();
	int highest = 0, lowest = 0;
	float total = 0.0f;

	for (int i = 0; i < TIMES_COUNT; i++) {
		if (times[lowest] > times[i]) lowest = i;
		if (times[highest] < times[i]) highest = i;
		total += times[i];
	}

	std::cout << "array list:\t\t\t" << std::endl;
	std::cout << "Highest: " << times[highest] << "ms" << std::endl;
	std::cout << "Lowest : " << times[lowest] << "ms" << std::endl;
	std::cout << "Average: " << (total / TIMES_COUNT) << "ms" << std::endl;
	std::cout << "Elapsed: " << elapsed << "s" << std::endl;
	std::cout << "----------------------------------" << std::endl;

}

void testlinkedlist() {
	float times[TIMES_COUNT];
	mystd::timer t, t2;
	for (float i = 0; i < TIMES_COUNT; i++) {
		t.reset();
		mystd::linkedlist<Data>* a = new mystd::linkedlist<Data>;
		for (int j = 0; j < ADD_COUNT; j++)
			a->push_back({ j, j * 2, "WTF" });
		times[(int)i] = t.timeElapsed() * 1000.0f;
		std::cout << "linked list: " << ((int)(i / TIMES_COUNT * 100)) << "% time: " << (int)t2.timeElapsed() << "s\r";
		delete a;
	}

	//timer stats
	float elapsed = t2.timeElapsed();
	int highest = 0, lowest = 0;
	float total = 0.0f;

	for (int i = 0; i < TIMES_COUNT; i++) {
		if (times[lowest] > times[i]) lowest = i;
		if (times[highest] < times[i]) highest = i;
		total += times[i];
	}

	std::cout << "linked list:\t\t\t" << std::endl;
	std::cout << "Highest: " << times[highest] << "ms, index: " << highest << std::endl;
	std::cout << "Lowest : " << times[lowest] << "ms, index: " << lowest << std::endl;
	std::cout << "Average: " << (total / TIMES_COUNT) << "ms" << std::endl;
	std::cout << "Elapsed: " << elapsed << "s" << std::endl;
	std::cout << "----------------------------------" << std::endl;

}

void testarray() {
	float times[TIMES_COUNT];
	mystd::timer t, t2;
	for (float i = 0; i < TIMES_COUNT; i++) {
		t.reset();
		mystd::array<Data, ADD_COUNT> a;
		for (int j = 0; j < ADD_COUNT; j++)
			a[j] = { j, j * 2, "WTF" };
		times[(int)i] = t.timeElapsed() * 1000.0f;
		std::cout << "array: " << ((int)(i / TIMES_COUNT * 100)) << "% time: " << t2.timeElapsed() << "s\r";
	}

	//timer stats
	float elapsed = t2.timeElapsed();
	int highest = 0, lowest = 0;
	float total = 0.0f;

	for (int i = 0; i < TIMES_COUNT; i++) {
		if (times[lowest] > times[i]) lowest = i;
		if (times[highest] < times[i]) highest = i;
		total += times[i];
	}

	std::cout << "array:\t\t\t" << std::endl;
	std::cout << "Highest: " << times[highest] << "ms" << std::endl;
	std::cout << "Lowest : " << times[lowest] << "ms" << std::endl;
	std::cout << "Average: " << (total / TIMES_COUNT) << "ms" << std::endl;
	std::cout << "Elapsed: " << elapsed << "s" << std::endl;
	std::cout << "----------------------------------" << std::endl;
}