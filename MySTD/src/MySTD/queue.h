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
			for (auto it = list.begin(); it != list.end(); ++it)
				push(*it);
		}

		queue(const queue& other)
			: m_Start(nullptr), m_End(nullptr), m_Count(other.m_Count)
		{
		}

		~queue()
		{
			clear();
		}

		void push(T item)
		{
			if (empty())
			{
				m_Start = new Node{ item, nullptr };
			}
			else if (m_End == nullptr)
			{
				m_End = new Node{ item, nullptr };
				m_Start->next = m_End;
			}
			else
			{
				Node* newNode = new Node{ item, nullptr };
				m_End->next = newNode;
				m_End = newNode;
			}
			m_Count++;
		}

		T pop()
		{
			Node* startNode = m_Start;
			m_Start = m_Start->next;

			T item = startNode->item;
			delete startNode;

			m_Count--;
			return item;
		}

		T& front()
		{
			return m_Start->item;
		}

		const T& front() const
		{
			return m_Start->item;
		}

		bool empty() const
		{
			return !m_Count;
		}

		size_t size() const
		{
			return m_Count;
		}

		void clear()
		{
			Node* current = m_Start;
			for (unsigned int i = 0; i < m_Count; i++) {
				Node* next = current->next;
				delete current;
				current = next;
			}
			m_Start = m_End = nullptr;
			m_Count = 0;
		}

		friend std::ostream& operator<<(std::ostream& stream, const queue& q)
		{
			if (q.empty()) return stream << "queue<" << typeid(T).name() << ">:[empty]";

			stream << "queue<" << typeid(T).name() << ">:[";
			queue::Node* current = q.m_Start;
			for (; current->next != nullptr; current = current->next)
				stream << current->item << ", ";
			return stream << current->item << "]";
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