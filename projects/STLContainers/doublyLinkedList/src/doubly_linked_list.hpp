#pragma once

#include <cstddef>
using namespace std;

namespace biv {
	template <typename T> 
	class DoublyLinkedList {
		private:
			class Node {
				public:
					T value;
					Node* prev = nullptr;
					Node* next = nullptr;
					
					Node(const T& value) : value(value) {}
						
					Node(const Node&) = delete;
					Node& operator = (const Node&) = delete;
			};

			Node* begin = nullptr;
			Node* end = nullptr;

		public:
			DoublyLinkedList() noexcept {};
			
			DoublyLinkedList(const T* array, size_t array_size);
			DoublyLinkedList(const DoublyLinkedList&) = delete;
			DoublyLinkedList& operator = (const DoublyLinkedList&) = delete;
			bool operator == (const DoublyLinkedList<T>& other) const noexcept;
			~DoublyLinkedList();
			
			size_t get_size() const noexcept;
			bool has_item(const T& value) const noexcept;
			void print() const noexcept;
			void push_back(const T& value);
			bool remove_first(const T& value) noexcept;
	};
}
