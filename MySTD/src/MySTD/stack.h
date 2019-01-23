#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>

namespace mystd {
	template<typename T>
	class stack
	{
	private:
		struct Node;
		class stack_iterator;

	public:
		using iterator = typename stack_iterator;

		stack()
			: m_Top(nullptr), m_DataCount(0) { }

		stack(const std::initializer_list<T>& list)
			: m_Top(nullptr), m_DataCount(0)
		{
			for (size_t i = 0; i < list.size(); i++)
				push(*(list.end() - i - 1));
		}

		stack(const stack& other)
			: m_Top(nullptr), m_DataCount(other.m_DataCount)
		{
			m_Top = new Node{ other.m_Top->item, nullptr };

			Node* end = m_Top;
			for (Node* n = other.m_Top->next; n != nullptr; n = n->next)
			{
				Node* newNode = new Node{ n->item, end };
				end->next = newNode;
				end = newNode;
			}
			end->next = nullptr;
		}

		~stack()
		{
			clear();
		}

		bool empty() const
		{
			return !m_DataCount;
		}

		size_t size() const
		{
			return m_DataCount;
		}

		bool push(T item)
		{
			Node* newTop = new Node{ item, m_Top };
			m_Top = newTop;

			m_DataCount++;
			return true;
		}

		T pop()
		{
			if (!m_DataCount) throw std::out_of_range("");

			Node* topNode = m_Top;
			m_Top = m_Top->next;

			T item = topNode->item;
			delete topNode;

			m_DataCount--;
			return item;
		}

		void clear()
		{
			Node* current = m_Top;
			for (unsigned int i = 0; i < m_DataCount; i++) {
				Node* next = current->next;
				delete current;
				current = next;
			}
			m_Top = nullptr;
			m_DataCount = 0;
		}

		T const& top() const
		{
			if (!m_DataCount) throw std::out_of_range("");
			return m_Top->item;
		}

		int search(T item) const
		{
			int index = 0;
			for (Node* current = m_Top; current != nullptr; current = current->next, index++)
				if (current->item == item) return index;
			return -1;
		}

		iterator begin()
		{
			return m_Top;
		}

		iterator end()
		{
			return nullptr;
		}

		friend std::ostream& operator<<(std::ostream& stream, const stack& s)
		{
			if (s.empty()) return stream << "stack:[empty]";

			stream << "stack:[";
			stack::Node* current = s.m_Top;
			for (; current->next != nullptr; current = current->next)
				stream << current->item << ", ";
			return stream << current->item << "]";
		}

		//delete this function ( this is for testing only )
		void print_address_trace() const
		{
			Node* current = m_Top;
			std::cout << "size:" << size() << std::endl;
			for (size_t i = 0; i < size() && current != nullptr; i++) {
				std::cout << "(" << current << ") -> " << current->item << ", " << current->next << std::endl;
				current = current->next;
			}
		}

	private:
		struct Node
		{
			T item;
			Node* next;
		};

		Node* m_Top;
		size_t m_DataCount;

		//using it = typename mystd::iterator<stack<T>::Node>;

//----------------------STACK ITERATOR----------------------
	private:
		class stack_iterator
		{
		public:
			stack_iterator(Node* ptr)
				: m_Ptr(ptr)
			{
			}

			T& operator*()
			{
				return m_Ptr->item;
			}

			stack_iterator& operator++() //pre incremenet
			{
				m_Ptr = m_Ptr->next;
				return *this;
			}

			stack_iterator operator++(int) //post increment
			{
				m_Ptr = m_Ptr->next;
				return *this;
			}

			bool operator!=(const stack_iterator& other) const
			{
				return m_Ptr != other.m_Ptr;
			}

			bool operator==(const stack_iterator& other) const
			{
				return m_Ptr == other.m_Ptr;
			}

		private:
			Node* m_Ptr;
		};
	};
}