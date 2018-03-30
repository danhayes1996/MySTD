#include <iostream>
#include <string>

#include "array.h"
#include "arraylist.h"
#include "linkedlist.h"

#include <chrono>

struct Timer 
{
	std::chrono::time_point<std::chrono::steady_clock> start;

	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {

	}

	void reset() {
		start = std::chrono::high_resolution_clock::now();
	}

	float timeElapsed() 
	{
		std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start;
		
		return duration.count() * 1000.0f;
	}
};

struct Data 
{
	int a, b;
	std::string c;

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

#define TIMES_COUNT 300
#define ADD_COUNT	1000
void testarraylist() {
	float times[TIMES_COUNT];
	Timer t, t2;
	for (float i = 0.0f; i < TIMES_COUNT; i++) {
		t.reset();
		mystd::arraylist<Data> a;
		for (int j = 0; j < ADD_COUNT; j++)
			a.push_back({ j, j * 2, "WTF" });
		times[(int)i] = t.timeElapsed();
		std::cout << "array list: " << ((int)(i / TIMES_COUNT * 100)) << "%\r";
	}

	//timer stats
	float elapsed = t2.timeElapsed();
	int highest = 0, lowest = 0;
	float total = 0.0f;

	for (int i = 0; i < TIMES_COUNT; i++) {
		if (times[lowest] > times[i]) lowest = i;
		if (times[highest] < times[i]) highest = i;
		total += times[i];
		;
	}

	std::cout << "array list:\t\t" << std::endl;
	std::cout << "Highest: " << times[highest] << "ms" << std::endl;
	std::cout << "Lowest : " << times[lowest] << "ms" << std::endl;
	std::cout << "Average: " << (total / TIMES_COUNT) << "ms" << std::endl;
	std::cout << "Elapsed: " << (elapsed / 1000.0f) << "s" << std::endl;
	std::cout << "----------------------------------" << std::endl;

}

void testlinkedlist() {
	float times[TIMES_COUNT];
	Timer t, t2;
	for (float i = 0; i < TIMES_COUNT; i++) {
		t.reset();
		mystd::linkedlist<Data> a;
		for (int j = 0; j < ADD_COUNT; j++)
			a.push_back({ j, j * 2, "WTF" });
		times[(int)i] = t.timeElapsed();
		std::cout << "linked list: " << ((int)(i / TIMES_COUNT * 100)) << "%\r";
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

	std::cout << "linked list:\t\t" << std::endl;
	std::cout << "Highest: " << times[highest] << "ms" << std::endl;
	std::cout << "Lowest : " << times[lowest] << "ms" << std::endl;
	std::cout << "Average: " << (total / TIMES_COUNT) << "ms" << std::endl;
	std::cout << "Elapsed: " << (elapsed / 1000.0f) << "s" << std::endl;
	std::cout << "----------------------------------" << std::endl;

}

void testarray() {
	float times[TIMES_COUNT];
	Timer t, t2;
	for (float i = 0; i < TIMES_COUNT; i++) {
		t.reset();
		mystd::array<Data, ADD_COUNT> a;
		for (int j = 0; j < ADD_COUNT; j++)
			a[j] = { j, j * 2, "WTF" };
		times[(int)i] = t.timeElapsed();
		std::cout << "array: " << i << ", " << ((int)(i / TIMES_COUNT * 100)) << "%\r";
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

	std::cout << "array:\t\t" << std::endl;
	std::cout << "Highest: " << times[highest] << "ms" << std::endl;
	std::cout << "Lowest : " << times[lowest] << "ms" << std::endl;
	std::cout << "Average: " << (total / TIMES_COUNT) << "ms" << std::endl;
	std::cout << "Elapsed: " << (elapsed / 1000.0f) << "s" << std::endl;
	std::cout << "----------------------------------" << std::endl;
}

void main(void)
{
	testarraylist();
	testlinkedlist();
	testarray();
	std::cin.get();
}