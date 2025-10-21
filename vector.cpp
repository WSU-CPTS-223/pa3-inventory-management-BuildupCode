#include "vector.h"
#include <cstring>

template <typename T>
Vector<T>::Vector() : data(nullptr), size_(0), capacity_(0){}

template <typename T>
Vector<T>::~Vector(){
    delete[] data;
}

template <typename T>
void Vector<T>::resize(std::size_t newCap){
    T* newData = new T[newCap];
    for(std::size_t i = 0;i<size_;i++){
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity_ = newCap;
}

template <typename T>
void Vector<T>::push_back(const T& value){
    if(size_ == capacity_){
        resize(capacity_ == 0 ? 1 : capacity_*2);
    }
    data[size_++] = value;
}

template <typename T>
std::size_t Vector<T>::size() const {
    return size_;
}

template <typename T>
T& Vector<T>::operator[](std::size_t index){
    if(index >= size_){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const{
    if(index >= size_){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
void Vector<T>::clear(){
    size_ = 0;
}
