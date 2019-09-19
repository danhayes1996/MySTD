#pragma once

//TODO: Shared pointers, fix unique pointer array (cannot view or change values in the array)

namespace mystd {

	template<typename T>
	class unique
	{
		public:
			unique() : m_Ptr(new T) { }

			unique(T* ptr) : m_Ptr(ptr) { }

			~unique()
			{
				delete m_Ptr;
			}

			inline T* get() const { return m_Ptr; }

			T& operator*() const
			{
				return *get();
			}

			T* operator->() const {
				return get();
			}

		private:
			T* m_Ptr;
	};

//not working currently
/*	template<typename T>
	class unique<T[]>
	{
	public:
		unique(T* ptr) : m_Ptr(ptr) { }

		~unique()
		{
			delete[] m_Ptr;
		}

		inline T* get() const { return m_Ptr; }

		T& operator*() const
		{
			return *get();
		}

		T* operator->() const {
			return get();
		}

		T& operator[](int index) const {
			return m_Ptr[index];
		}

	private:
		T* m_Ptr;
	};
*/
}