#pragma once

namespace mystd {

	template<typename T>
	class iterator
	{
	public:

		iterator(T* ptr)
			: m_Ptr(ptr)
		{}

		T& operator*()
		{
			return *m_Ptr;
		}

		iterator& operator++() //pre incremenet
		{
			++m_Ptr;
			return *this;
		}

		iterator operator++(int) //post increment
		{
			m_Ptr++;
			return *this;
		}

		iterator& operator--() //pre decrement
		{
			--m_Ptr;
			return *this;
		}

		iterator operator--(int) //post decrement
		{
			m_Ptr--;
			return *this;
		}

		bool operator!=(const iterator& other) const 
		{ 
			return m_Ptr != other.m_Ptr; 
		}

		bool operator==(const iterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

	protected:
		T* m_Ptr;
	};

	template<typename T>
	class reverse_iterator : public iterator<T>
	{
	public:
		reverse_iterator(T* ptr)
			: iterator<T>(ptr)
		{}

		reverse_iterator& operator++() //pre incremenet
		{
			--m_Ptr;
			return *this;
		}

		reverse_iterator operator++(int) //post increment
		{
			m_Ptr--;
			return *this;
		}

		reverse_iterator& operator--() //pre decrement
		{
			++m_Ptr;
			return *this;
		}

		reverse_iterator operator--(int) //post decrement
		{
			m_Ptr++;
			return *this;
		}
	};
}
