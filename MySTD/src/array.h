#pragma once

#include <ostream>
#include <initializer_list>
#include <stdexcept>

namespace mystd {
	template<typename T, size_t N>
	class array 
	{
	public:
		array() 
			: m_Data(new T[N]) { }

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
			return &m_Data[N - 1];
		}

		const T* end() const 
		{
			return &m_Data[N - 1];
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
			stream << "array:[";
			for (size_t i = 0; i < N - 1; i++)
				stream << arr[i] << ", ";
			return stream << arr[N - 1] << "]";
		}

	private:
		T* m_Data;
	};
}