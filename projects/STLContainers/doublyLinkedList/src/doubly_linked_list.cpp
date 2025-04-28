#include "doubly_linked_list.hpp"

#include <iostream>

using biv::DoublyLinkedList;


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const T* array, size_t array_size) : begin(nullptr), end(nullptr) {
    Node** current = &begin;
    for (size_t i = 0; i < array_size; ++i) {
        *current = new Node(array[i]);
        if (i == 0) {
            end = *current;
        } else {
            (*current)->prev = *(current - 1);
            (*(current - 1))->next = *current;
        }
        ++current;
    }
}

template<typename T>
bool DoublyLinkedList<T>::operator == (const DoublyLinkedList<T>& other) const noexcept {
    Node* current = begin;
    Node* other_current = other.begin;
    while (current != nullptr && other_current != nullptr) {
        if (current->value != other_current->value) {
            return false;
        }
        current = current->next;
        other_current = other_current->next;
    }
    return current == nullptr && other_current == nullptr;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = begin;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    begin = end = nullptr;

}

template<typename T>
size_t DoublyLinkedList<T>::get_size() const noexcept {
    size_t size = 0;
    Node* current = begin;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
    Node* current = begin;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;

}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (begin == nullptr) {
        begin = end = new_node;
    } else {
        end->next = new_node;
        new_node->prev = end;
        end = new_node;
    }
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                if (this->get_size() != 1){
                    begin = current->next;}
                else{
                    begin = nullptr;
                    end = nullptr;
                }
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                if (this->get_size() != 1){
                    end = current->prev;
                }else{
                    begin = nullptr;
                    end = nullptr;
                }
            }

            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}
