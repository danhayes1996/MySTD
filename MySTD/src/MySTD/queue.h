#pragma once

#include <initializer_list>
#include <ostream>

namespace mystd {

	template<typename T>
	class queue
	{
	public:
		queue()
			: m_Start(nullptr), m_End(nullptr), m_Count(0)
		{
		}

		queue(const std::initializer_list<T>& list)
			: m_Start(nullptr), m_End(nullptr), m_Count(0)
		{
		}

		queue(const queue& other)
			: m_Start(nullptr), m_End(nullptr), m_Count(other.m_Count)
		{
		}

		~queue()
		{
		}

		void push(T item);
		T pop();
		T front();
		bool empty();
		size_t size();
		void clear();

		friend std::ostream& operator<<(std::ostream& stream, const queue& q)
		{

		}

	private:
		struct Node 
		{
			T item;
			Node* next;
		};

		Node* m_Start;
		Node* m_End;
		size_t m_Count;
	};

}