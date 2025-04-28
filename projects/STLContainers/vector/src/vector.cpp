#include "vector.hpp"

#include <iostream>

using biv::Vector;

template <typename T>
const std::size_t biv::Vector<T>::START_CAPACITY = 32;

template<typename T>
void Vector<T>::shrink(){
	capacity = capacity /2;
	T* temp = new T[capacity];
	for (int i = 0; i < size; i++){
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
}

template<typename T>
Vector<T>::Vector() {
	arr = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const T* array, size_t array_size){
	capacity = array_size;
    size = array_size;
    arr = new T[capacity];
    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = array[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	capacity = START_CAPACITY;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& other) const noexcept {
	if (size != other.size) {
		return false;
	}
	for (int i = 0; i < size; ++i) {
		if (arr[i] != other.arr[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
size_t Vector<T>::get_capacity() const noexcept {
	return capacity;
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
	if (position > size || position < 0) {
		return false;
	}

	if (size == capacity) {
		capacity *= 2;
		T* temp = new T[capacity];
		for (int i = 0, j = 0; i < size + 1; i++) {
			if (i == position) {
				temp[i] = value;
			}
			else {
				cout<<"arr[j]: "<< arr[j]<<endl;
				temp[i] = arr[j++];

			}
		}
		delete[] arr;
		arr = temp;
	}

	// for (int i = size; i > position; --i) {
	// 	arr[i + 1] = arr[i];
	// }
	// arr[position] = value;
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
			if (size < (capacity / 2)) {
				this->shrink();
			}		
			return true;
		}
	}
	return false;

}
