#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include "arraylist.h"

namespace mystd {
	template <typename T>
	class binary_tree
	{
	private:
		struct Node;

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
			delete_recursive(m_Start);
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
			//mystd::arraylist<T> data;
			//to_array(m_Start, data);
		}

		bool search(const T& item) const
		{
			Node* current = m_Start;
			while (current) {
				if (item == current->item) return true;
				else if (item < current->item) {
					current = current->left;
				}
				else if (item > current->item) {
					current = current->right;
				}
			}
			return false;
		}

		bool insert(const T& item)
		{
			if (m_Count == 0) {
				m_Start = new Node{ item, nullptr, nullptr };
				m_Count++;
				return true;
			}
			return insert_item(m_Start, item);
		}

		T remove(const T& item)
		{
			return NULL;
		}

		void clear() {
			delete_recursive(m_Start);
			m_Start = nullptr;
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
			if (tree.empty()) return stream << "[ empty ]";
			stream << "[";
			tree.print_prefix(stream, tree.m_Start);
			return stream << " ]";
		}

	private:
		bool insert_item(Node* n, const T& item) {
			if (item < n->item) {
				if (n->left) {
					return insert_item(n->left, item);
				}
				else {
					Node* newNode = new Node{ item, nullptr, nullptr };
					n->left = newNode;
					m_Count++;
					return true;
				}
			}
			else if (item > n->item) {
				if (n->right) {
					return insert_item(n->right, item);
				}
				else {
					Node* newNode = new Node{ item, nullptr, nullptr };
					n->right = newNode;
					m_Count++;
					return true;
				}
			}
			return false; //items are equal
		}

		void to_array(Node* n, mystd::arraylist<T>& arr) {
			if (!n) return;

			if (n->left) to_array(n->left, arr);
			arr.push_back(n->item);
			if (n->right) to_array(n->right, arr);
		}

		void delete_recursive(Node* n) {
			if (!n) return;
			if (n->left) delete_recursive(n->left);
			if (n->right) delete_recursive(n->right);
			delete n;
			m_Count--;
		}

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