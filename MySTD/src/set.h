#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>

namespace mystd
{
	template<typename T>
	class set
	{
	private:
		T * m_Data;
		size_t m_DataSize;
		size_t m_DataCount;

	public:
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
			//TODO: order set
		}

		~set()
		{
			delete[] m_Data;
		}

		bool empty() const
		{
			return !m_DataCount;
		}

		size_t size() const
		{
			return m_DataCount;
		}

		void insert(const T& item)
		{
			//TODO: resize buffer if needed
			//TODO: check see if item already exists
			//TODO: insert element in the right place
		}

		T remove(size_t index)
		{
			//remove element
			//
		}

		T remove(const T& item)
		{
			
		}

		T* begin()
		{
			return m_Data;
		}

		const T* begin() const
		{
			return m_Data;
		}

		T* end()
		{
			return &m_Data[m_DataCount - 1];
		}

		const T* end() const
		{
			return &m_Data[m_DataCount - 1];
		}

		T const& at(size_t index) const
		{
			if (index >= m_DataCount) throw std::out_of_range("index out of range");
			return m_Data[index];
		}

		T& at(size_t index)
		{
			if (index >= m_DataCount) throw std::out_of_range("index out of range");
			return m_Data[index];
		}

		T& operator[](size_t index)
		{
			return at(index);
		}

		T const& operator[](size_t index) const
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
			if (s.empty()) return stream << "set:[empty]" << std::endl;
			stream << "set:[";
			for (size_t i = 0; i < s.m_DataCount - 1; i++)
				stream << s.m_Data[i] << ", ";
			return stream << s[s.m_DataCount - 1] << "]";
		}
	};
}