#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>

#include "iterator.h"

namespace mystd {
	template<typename T, size_t N>
	class array 
	{
	public:
		using iterator = typename mystd::iterator<T>;
		using const_iterator = typename mystd::iterator<const T>;
		using reverse_iterator = typename mystd::reverse_iterator<T>;
		using const_reverse_iterator = typename mystd::reverse_iterator<const T>;

		array() 
			: m_Data(new T[N]) 
		{ }

		array(const std::initializer_list<T>& list)
			: m_Data(new T[N])
		{
			for (size_t i = 0; i < N; i++) 
			{
				if(i < list.size()) m_Data[i] = *(list.begin() + i);
				else m_Data[i] = T(); //default constructor for T
			}
		}

		array(const array& other) 
			: m_Data(new T[N])
		{
			for (size_t i = 0; i < N; i++)
				m_Data[i] = other[i]; //used to be T(other[i]) to use copy constructor for T, but this seems to work fine..
		}

		~array() 
		{
			delete[] m_Data;
		}

		size_t size() const 
		{
			return N;
		}

		size_t max_size() const
		{
			return N;
		}

		bool empty() const
		{
			return !N;
		}

		/* Sets val as the value for all the elements in the array */
		void fill(const T& val)
		{
			for (unsigned int i = 0; i < N; i++)
			{
				m_Data[i] = val;
			}
		}

		iterator begin() 
		{ 
			return &m_Data[0]; 
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
			return &m_Data[N - 1];
		}

		const_reverse_iterator crbegin() const
		{
			return &m_Data[N - 1];
		}

		iterator end() 
		{
			return &m_Data[N];
		}

		const_iterator end() const
		{
			return &m_Data[N - 1];
		}

		const_iterator cend() const
		{
			return &m_Data[N - 1];
		}

		reverse_iterator rend()
		{
			return &m_Data[-1];
		}

		const_reverse_iterator crend() const
		{
			return &m_Data[-1];
		}

		T* data()
		{
			return &m_Data[0];
		}

		T& at(size_t index)
		{
			if (index >= N) throw std::out_of_range("");
			return m_Data[index];
		}

		T const& at(size_t index) const 
		{
			if (index >= N) throw std::out_of_range("");
			return m_Data[index];
		}

		T& operator[](size_t index) 
		{
			if (index >= N) throw std::out_of_range("");
			return m_Data[index];
		}

		T const& operator[](size_t index) const 
		{
			if (index >= N) throw std::out_of_range("");
			return m_Data[index];
		}

		bool operator==(const array& other) const 
		{
			for (size_t i = 0; i < N; i++)
				if (m_Data[i] != other[i]) return false;
			return true;
		}

		bool operator!=(const array& other) const 
		{
			return !(*this == other);
		}

		friend std::ostream& operator<<(std::ostream& stream, const array& arr) 
		{
			stream << "array<" << typeid(T).name() << ">:[";
			for (size_t i = 0; i < N - 1; i++)
				stream << arr[i] << ", ";
			return stream << arr[N - 1] << "]";
		}

	private:
		T* m_Data;
	};
}