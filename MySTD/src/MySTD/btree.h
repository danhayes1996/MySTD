#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

namespace mystd
{
	template <typename T>
	class binary_tree
	{
	public:
		binary_tree()
			: m_Start(nullptr), m_Count(0) { }

		binary_tree(const binary_tree& other)
			: m_Start(nullptr), m_Count(0)
		{

		}

		binary_tree(const std::initializer_list<T>& list)
			: m_Start(nullptr), m_Count(0)
		{
			for(size_t i = 0; i < list.size(); i++)
				insert(*(list.begin + i));
		}

		~binary_tree()
		{

		}

		bool empty() const
		{
			return !m_Count;
		}

		size_t size() const
		{
			return m_Count;
		}
		
		void rebalance()
		{
			//rebalance the tree to make it more efficient
		}

		bool search(const T& item) const
		{
			Node* current = m_Start;
			while (current != nullptr)
			{
				if (current->item == item) return true;
				if (item < current->item) current = current->left;
				else current = current->right;
			}
			return false;
		}

		bool insert(const T& item)
		{
			if (m_Start == nullptr)
			{
				m_Start = new Node{ item, nullptr, nullptr };
				m_Count++;
				return true;
			}

			Node* current = m_Start;
			while (current != nullptr) {
				if (current->item == item) return false;

				if (item < current->item)
				{
					if (current->left == nullptr)
					{
						current->left = new Node{ item, nullptr, nullptr };
						break;
					}
					else current = current->left;
				}
				else if (item > current->item)
				{
					if (current->right == nullptr)
					{
						current->right = new Node{ item, nullptr, nullptr };
						break;
					}
					else current = current->right;
				}
			}
			m_Count++;
			return true;
		}

		T remove(const T& item)
		{

		}

		bool operator==(const binary_tree& other) const
		{
			return false;
		}

		bool operator!=(const binary_tree& other) const
		{
			return false;
		}

		friend std::ostream& operator<<(std::ostream& stream, const binary_tree& tree)
		{
			stream << "binary_tree:[";
			tree.print_infix(stream, tree.m_Start);
			return stream << " ]";
		}

	private:
		void print_infix(std::ostream& stream, Node* n) const
		{
			if (n != nullptr)
			{
				print_infix(stream, n->left);
				stream << " " << n->item;
				print_infix(stream, n->right);
			}
		}

		void print_prefix(std::ostream& stream, Node* n) const
		{
			if (n != nullptr)
			{
				stream << " " << n->item;
				print_prefix(stream, n->left);
				print_prefix(stream, n->right);
			}
		}

		void print_postfix(std::ostream& stream, Node* n) const
		{
			if (n != nullptr)
			{
				print_postfix(stream, n->left);
				print_postfix(stream, n->right);
				stream << " " << n->item;
			}
		}

	private:
		struct Node
		{
			T item;
			Node* left;
			Node* right;
		};

		Node* m_Start;
		size_t m_Count;
	};
}