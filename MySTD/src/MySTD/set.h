#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>

#include "compare.h"
#include "iterator.h"

namespace mystd {

	template<typename T, typename Compare = mystd::less<T>>
	class set
	{
	public:
		using iterator = typename mystd::iterator<const T>;
		using const_iterator = typename mystd::iterator<const T>;
		using reverse_iterator = typename mystd::reverse_iterator<const T>;
		using const_reverse_iterator = typename mystd::reverse_iterator<const T>;

		set(size_t size = 5)
			: m_Data(new T[size]), m_DataSize(size), m_DataCount(0) { }

		set(const set& other)
			: m_Data(new T[other.m_DataCount]), m_DataSize(other.m_DataCount), m_DataCount(other.m_DataCount) 
		{ 
			for (size_t i = 0; i < m_DataCount; i++)
				m_Data[i] = other.m_Data[i];
		}

		set(const std::initializer_list<T>& list)
			: m_Data(new T[list.size()]), m_DataSize(list.size()) 
		{
			for (size_t i = 0; i < list.size(); i++)
				insert(*(list.begin() + i));
		}

		~set()
		{
			delete[] m_Data;
		}

		bool empty() const
		{
			return !m_DataCount;
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

		bool insert(const T& item)
		{
			//if item isnt in set
			if (index_of(item) == -1)
			{
				if (need_to_resize()) resize(m_DataSize * 2);
				
				//put item at correct index (to keep set ordered)
				Compare c;
				for (size_t i = 0; i < m_DataCount; i++)
				{
					if (c(item, m_Data[i]))
					{
						//move shift items to the right of m_Data[i] up by one
						for (size_t j = m_DataCount; j > i; j--)
							m_Data[j] = m_Data[j - 1];

						//put new item in empty space
						m_Data[i] = item;
						m_DataCount++;
						return true;
					} 
				}
				//add the item to the end of the set (only done if the Compare dictates it should be last)
				m_Data[m_DataCount] = item;
				m_DataCount++;
				return true;
			}
			return false;
		}

		T remove_at(size_t index)
		{
			if (index >= m_DataCount) throw std::out_of_range("");
			T item = m_Data[index];

			for (size_t i = index; i < m_DataCount; i++)
				m_Data[i] = m_Data[i + 1];
			m_DataCount--;
			return item;
		}

		T remove(const T& item)
		{
			return remove_at(index_of(item));
		}

		bool contains(const T& item)
		{
			return index_of(item) != -1 ? true : false;
		}

		int index_of(const T& item)
		{
			for (size_t i = 0; i < m_DataCount; i++)
				if (m_Data[i] == item) return i;
			return -1;
		}

		iterator begin()
		{
			return m_Data;
		}

		const_iterator begin() const
		{
			return m_Data;
		}

		const_iterator cbegin() const
		{
			return m_Data;
		}

		reverse_iterator rbegin()
		{
			return &m_Data[m_DataCount - 1];
		}

		const_reverse_iterator crbegin() const
		{
			return &m_Data[m_DataCount - 1];
		}

		iterator end()
		{
			return &m_Data[m_DataCount];
		}

		const_iterator end() const
		{
			return &m_Data[m_DataCount];
		}

		reverse_iterator rend()
		{
			return &m_Data[-1];
		}

		const_reverse_iterator crend() const
		{
			return &m_Data[-1];
		}

		const T& at(size_t index) const
		{
			if (index >= m_DataCount) throw std::out_of_range("index out of range");
			return m_Data[index];
		}

		const T& operator[](size_t index) const
		{
			return at(index);
		}

		bool operator==(const set& other) const
		{
			for (size_t i = 0; i < m_DataCount; i++)
				if (m_Data[i] != other.m_Data[i]) return false;
			return true;
		}

		bool operator!=(const set& other) const
		{
			return !(*this == other);
		}

		friend std::ostream& operator<<(std::ostream& stream, const set& s)
		{
			if (s.empty()) return stream << "set<" << typeid(T).name()  << ">:[empty]" << std::endl;
			
			stream << "set<" << typeid(T).name() << ">:[";
			for (size_t i = 0; i < s.m_DataCount - 1; i++)
				stream << s.m_Data[i] << ", ";
			return stream << s[s.m_DataCount - 1] << "]";
		}

	private:
		bool need_to_resize()
		{
			return m_DataCount == m_DataSize;
		}

		void resize(size_t size)
		{
			T* temp = new T[size];
			for (size_t i = 0; i < m_DataCount; i++)
				temp[i] = m_Data[i];

			delete[] m_Data;
			m_Data = temp;
			m_DataSize = size;
		}

	private:
		T* m_Data;
		size_t m_DataSize;
		size_t m_DataCount;
	};
}