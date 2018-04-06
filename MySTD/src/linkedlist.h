#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>
#include "arraylist.h"

//forward declare so friend class arraylist<T> can use linkedlist private data
template<typename T> class arraylist;

namespace mystd 
{
	template<typename T>
	class linkedlist 
	{

		friend class arraylist<T>;
	private:
		struct Node 
		{
			T item;
			Node* next;
			Node* prev;
		};

	private:
		Node* m_Start;
		Node* m_End;
		size_t m_DataCount;

	public:
		linkedlist() 
			: m_Start(nullptr), m_End(nullptr), m_DataCount(0) { }

		linkedlist(const std::initializer_list<T>& list) 
			: m_Start(nullptr), m_End(nullptr), m_DataCount(0)
		{
			for (size_t i = 0; i < list.size(); i++)
				push_back(*(list.begin() + i));
		}

		linkedlist(const linkedlist& other) 
			: m_Start(nullptr), m_End(nullptr), m_DataCount(0)
		{
			Node* n = other.m_Start;
			for (size_t i = 0; i < other.m_DataCount; i++, n = n->next) 
				push_back(n->item);
		}

		linkedlist(const arraylist<T>& other) 
			: m_Start(nullptr), m_End(nullptr), m_DataCount(0)
		{
			for (size_t i = 0; i < other.m_DataCount; i++)
				push_back(other.m_Data[i]); //TODO: is other[i] quicker??
		}

		~linkedlist()
		{
			Node* currentNode = m_Start;
			for (size_t i = 0; i < m_DataCount; i++) 
			{
				Node* nextNode = currentNode->next;
				delete currentNode;
				currentNode = nextNode;
			}
		}

		size_t size() const
		{
			return m_DataCount;
		}

		bool push_back(T item)
		{
			Node* n = new Node;
			n->item = item;
			n->next = n->prev = nullptr;

			if (empty()) m_Start = m_End = n;
			else 
			{
				n->prev = m_End;
				n->next = nullptr;
				m_End->next = n;
				m_End = n;
			}
			m_DataCount++;
			return true;
		}

		bool push_front(T item) {
			Node* n = new Node;
			n->item = item;
			n->next = n->prev = nullptr;

			if (empty()) m_Start = m_End = n;
			else
			{
				n->next = m_Start;
				m_Start = n;
			}
			m_DataCount++;
			return true;
		}

		bool push_at(unsigned int index, T item)
		{
			if (index > m_DataCount) return false;
			else if (index == m_DataCount) return push_back(item);

			Node* newNode = new Node;
			newNode->item = item;
			newNode->next = newNode->prev = nullptr;
			Node* n = m_Start;

			for (size_t i = 0; i < index; i++) n = n->next;
			Node* prevNode = n->prev;
			if (prevNode == nullptr) 
			{
				m_Start = newNode;
				newNode->next = n;
				n->prev = newNode;
			}
			else 
			{
				prevNode->next = newNode;
				newNode->prev = prevNode;
				newNode->next = n;
				n->prev = newNode;
			}
			m_DataCount++;

			return true;
		}

		T set(unsigned int index, T item)
		{
			if (index >= m_DataCount || index < 0) throw std::out_of_range("");
			Node* n = m_Start;
			for (size_t i = 0; i < index; i++)
				n = n->next;

			T returnItem = n->item;
			n->item = item;

			return returnItem;
		}

		T remove_at(unsigned int index)
		{
			if (index >= m_DataCount) throw std::out_of_range("");

			Node* n = m_Start;
			for (size_t i = 0; i < index; i++)
				n = n->next;

			T t = n->item;
			Node* prevNode = n->prev;
			if (prevNode == nullptr) m_Start = n->next;
			else if (index == size() - 1) 
			{
				m_End = prevNode;
				m_End->next = nullptr;
			}
			else 
			{
				prevNode->next = n->next;
				prevNode->next->prev = prevNode;
			}

			if (n == m_End) m_End = prevNode;
			m_DataCount--;

			delete n;
			return t;
		}

		bool remove(T item)
		{
			Node* n = m_Start;
			for (size_t i = 0; i < m_DataCount; i++) 
			{
				if (n->item == item) 
				{
					removeAt(i);
					return true;
				}
				n = n->next;
			}
			return false;
		}

		bool remove_range(unsigned int indexFrom, unsigned int indexTo)
		{
			if (indexFrom >= indexTo || indexFrom >= m_DataCount || indexTo > m_DataCount) return false;

			if (indexFrom == 0 && indexTo == m_DataCount) 
			{
				clear();
				return true;
			}

			Node* nFrom = m_Start;
			Node* nTo = m_Start;
			for (size_t i = 0; i < indexTo; i++) 
			{
				if (i < indexFrom) nFrom = nFrom->next;
				nTo = nTo->next;
			}
			Node* leftJoin = nFrom->prev;

			Node* current = nFrom;
			for (unsigned int i = 0; i < (indexTo - indexFrom); i++) 
			{
				Node* next = current->next;
				delete current;
				current = next;
			}

			if (leftJoin == nullptr) 
			{
				m_Start = nTo;
				nTo->prev = nullptr;
			}
			else if (indexTo != m_DataCount) 
			{
				leftJoin->next = nTo;
				nTo->prev = leftJoin;
			}
			else 
			{
				m_End = leftJoin;
				leftJoin->next = nullptr;
			}

			m_DataCount -= indexTo - indexFrom;
			return true;
		}

		bool remove_range_i(unsigned int indexFrom, unsigned int indexTo)
		{
			return removeRange(indexFrom, indexTo + 1);
		}

		void clear()
		{
			Node* currentNode = m_Start;
			for (size_t i = 0; i < m_DataCount; i++) 
			{
				Node* nextNode = currentNode->next;
				delete currentNode;
				currentNode = nextNode;
			}
			m_Start = m_End = nullptr;
			m_DataCount = 0;
		}

		bool empty() const
		{
			return !m_DataCount;
		}

		bool contains(T item) const
		{
			for (Node* current = m_Start; current != nullptr; current = current->next)
				if (current->item == item) return true;
			return false;
		}

		int index_of(T item) const
		{
			int index = 0;
			for (Node* current = m_Start; current != nullptr; current = current->next, index++)
				if (current->item == item) return index;
			return -1;
		}

		int last_index_of(T item) const
		{
			int index = m_DataCount - 1;
			for (Node* current = m_End; current != nullptr; current = current->prev, index--)
				if (current->item == item) return index;
			return -1;
		}

		T const& get(unsigned int index) const
		{
			if (index >= m_DataCount) throw std::out_of_range("");
			Node* n = m_Start;
			for (unsigned int i = 0; i < index; i++) n = n->next;
			return n->item;
		}

		T const& operator[](unsigned int index) const {
			if (index >= m_DataCount) throw std::out_of_range("");
			Node* current = m_Start;
			for (; index != 0; current = current->next, index--);
			return current->item;
		}

		bool operator==(const linkedlist& other) const
		{
			if (size() != other.size()) return false;

			Node* iterator = m_Start;
			Node* otherIterator = other.m_Start;

			for (; iterator != nullptr; iterator = iterator->next, otherIterator = otherIterator->next)
				if (iterator->item != otherIterator->item) return false;

			return true;
		}

		bool operator!=(const linkedlist& other) const
		{
			return !(*this == other);
		}

		friend std::ostream& operator<<(std::ostream& stream, const linkedlist& list)
		{
			if (list.empty()) return stream << "linkedlist:[empty]";

			stream << "linkedlist:[";
			for (linkedlist::Node* n = list.m_Start; n != list.m_End; n = n->next)
				stream << n->item << ", ";
			return stream << list.m_End->item << "]";
		}

		//TODO: delete this function
		void print_address_trace() const 
		{
			Node* current = m_Start;
			std::cout << "size:" << size() << std::endl;
			for (size_t i = 0; i < size(); i++, current = current->next)
				std::cout << "(" << current << ") -> " << current->prev << ", " << current->item << ", " << current->next << std::endl;
		}

	};
}