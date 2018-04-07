#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>
#include "linkedlist.h"

//forward declare so friend class linkedlist<T> can use arraylist private data
template<typename T> class linkedlist;

namespace mystd 
{
	template <typename T>
	class arraylist 
	{
		friend class linkedlist<T>;
	private:
		T* m_Data;
		size_t m_DataSize;
		size_t m_DataCount;

	private:
		inline bool need_to_resize() const 
		{
			return m_DataSize == m_DataCount;
		}

		void resize(size_t newSize) 
		{
			T* temp = new T[newSize];
			for (size_t i = 0; i < m_DataCount; i++)
				temp[i] = m_Data[i];

			delete[] m_Data;
			m_Data = temp;
			m_DataSize = newSize;
		}

	public:
		arraylist(size_t size = 5) 
			: m_Data(new T[size]), m_DataSize(size), m_DataCount(0) { }

		arraylist(const std::initializer_list<T>& list) 
			: m_DataSize(list.size()), m_DataCount(list.size()) 
		{
			m_Data = new T[m_DataSize];
			for (size_t i = 0; i < m_DataSize; i++)
				m_Data[i] = *(list.begin() + i);
		}

		arraylist(const arraylist& other) 
			: m_Data(new T[other.m_DataCount]), m_DataSize(other.m_DataCount), m_DataCount(other.m_DataCount) 
		{
			for (size_t i = 0; i < m_DataSize; i++)
				m_Data[i] = other[i];
		}
		
		arraylist(const linkedlist<T>& other) 
			: m_Data(new T[other.m_DataCount]), m_DataSize(other.m_DataCount), m_DataCount(other.m_DataCount)
		{
			linkedlist<T>::Node* n = other.m_Start;
			for (size_t i = 0; n != nullptr; n = n->next, i++)
				m_Data[i] = n->item;
		}

		arraylist(const T* arr, size_t count) 
			: m_Data(new T[count]), m_DataSize(count), m_DataCount(count)
		{
			for (size_t i = 0; i < count; i++, arr++) m_Data[i] = *arr;
		}

		~arraylist() 
		{
			delete[] m_Data;
		}

		linkedlist<T> to_linked_list() const {
			linkedlist<T> list;
			for (size_t i = 0; i < m_DataCount; i++) list.push_back(m_Data[i]);
			return list;
		}

		bool push_back(T item) 
		{
			if (need_to_resize()) resize(m_DataSize * 2);

			m_Data[m_DataCount] = item;
			m_DataCount++;
			return true;
		}

		bool push_at(unsigned int index, T item) 
		{
			if (need_to_resize()) resize(m_DataSize * 2);

			if (index >= m_DataCount)
			{
				m_Data[m_DataCount++] = item;
				return true;
			}

			for (size_t i = m_DataCount; i > index; i--)
				m_Data[i] = m_Data[i - 1];

			m_Data[index] = item;
			m_DataCount++;

			return true;
		}

		T set(int index, T item) 
		{
			if (index >= m_DataCount) throw std::out_of_range("");
			T ret = m_Data[index];
			m_Data[index] = item;
			return ret;
		}

		T remove_at(unsigned int index) 
		{
			if (index >= m_DataCount) throw std::out_of_range("");
			T item = m_Data[index];

			for (size_t i = index; i < m_DataCount; i++)
				m_Data[i] = m_Data[i + 1];
			m_DataCount--;
			return item;
		}

		bool remove(T item) 
		{
			int index = indexOf(item);
			if (index == -1) return false;
			removeAt(index);
			return true;
		}

		//indexFrom = inclusive, indexTo = exclusive
		void remove_range(unsigned int indexFrom, unsigned int indexTo) 
		{ 
			if (indexFrom >= indexTo || indexFrom > m_DataCount || indexTo > m_DataCount) return;

			for (size_t i = 0; i < m_DataSize - indexTo; i++)
				m_Data[indexFrom + i] = m_Data[indexTo + i];

			m_DataCount -= indexTo - indexFrom;
		}

		//indexFrom = inclusive, indexTo = inclusive
		void remove_range_i(unsigned int indexFrom, unsigned int indexTo) 
		{ 
			removeRange(indexFrom, indexTo + 1);
		}

		void clear() 
		{
			delete[] m_Data;
			m_DataCount = 0;
			m_DataSize = 5;
			m_Data = new T[m_DataSize];
		}

		size_t size() const 
		{
			return m_DataCount;
		}

		void trim_to_size() 
		{
			if (m_DataCount != m_DataSize) resize(m_DataCount);
		}

		void ensure_capacity(size_t minCapacity) 
		{
			if (minCapacity > m_DataSize) resize(minCapacity);
		}

		bool empty() const 
		{
			return !m_DataCount;
		}

		int index_of(T item) const 
		{
			for (size_t i = 0; i < m_DataCount; i++)
				if (item == m_Data[i]) return i;
			return -1;
		}

		int last_index_of(T item) const 
		{
			for (size_t i = m_DataCount - 1; i >= 0; i--)
				if (item == m_Data[i]) return i;
			return -1;
		}

		bool contains(T item) const
		{
			return indexOf(item) != -1;
		}

		T const& get(unsigned int index) const 
		{
			return operator[](index);
		}

		T const& operator[](unsigned int index) const 
		{
			if (index >= m_DataCount) throw std::out_of_range("");
			return m_Data[index];
		}

		bool operator==(const arraylist& other) const 
		{
			if (size() != other.size()) return false;
			for (size_t i = 0; i < size(); i++)
				if (this->get(i) != other[i]) return false;
			return true;
		}

		bool operator!=(const arraylist& other) const 
		{
			return !(*this == other);
		}

		friend arraylist operator+(const arraylist& left, const arraylist& right) {
			arraylist list = left;
			for (size_t i = 0; i < right.size(); i++) list.push_back(right[i]);
			return list;
		}
		
		friend std::ostream& operator<<(std::ostream& stream, const arraylist& list) 
		{
			if (list.empty()) return stream << "arraylist:[empty]";

			stream << "arraylist:[";
			for (size_t i = 0; i < list.m_DataCount - 1; i++)
				stream << list[i] << ", ";
			return stream << list[list.m_DataCount - 1] << "]";
		}
	};
}
