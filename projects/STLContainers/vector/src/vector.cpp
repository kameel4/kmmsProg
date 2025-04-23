#include "vector.hpp"

#include <iostream>

using biv::Vector;

template<typename T>
Vector<T>::Vector() {
	arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
}

template<typename T>
size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (int i = 0; i < size; ++i) {
		if (arr[i] == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const size_t position, const T& value) {
	if (position > size) {
		return false;
	}

	if (size == capacity) {
		capacity *= 2;
		T* temp = new T[capacity];
		for (int i = 0, j = 0; i < size + 1; ++i) {
			if (i == position) {
				temp[i] = value;
			}
			else {
				temp[i] = arr[j++];
			}
		}
		delete[] arr;
		arr = temp;
	}

	for (int i = size; i > position; --i) {
		arr[i] = arr[i - 1];
	}
	arr[position] = value;
	++size;
	return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        capacity *= 2;
        T* temp = new T[capacity];
        for (int i = 0; i < size; ++i) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    arr[size++] = value;

}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	for (int i = 0; i < size; ++i) {
		if (arr[i] == value) {
			for (int j = i; j < size - 1; ++j) {
				arr[j] = arr[j + 1];
			}
			--size;
			return true;
		}
	}
	return false;

}
