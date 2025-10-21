#ifndef VECTOR_H
#define VECTOR_H
//include this for using size_t(=array size/always positive)
#include <cstddef>
//for std::out_of_range () => handling exception
#include <stdexcept>
//implement vector by myself
template <typename T>
class Vector{
private:
    T* data;
    std::size_t size_;
    std::size_t capacity_;
    //function to extend space if array have no more space
    void resize(std::size_t newCap){
        T* newData = new T[newCap];
        for(std::size_t i = 0;i<size_;i++){
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity_ = newCap;
    }

public:
    //constructor and destructor
    Vector<T>::Vector() : data(nullptr), size_(0), capacity_(0){}
    ~Vector() {
        delete[] data;
    }
    //add new data at the end of the array
    void Vector<T>::push_back(const T& value){
        if(size_ == capacity_){
            //space will be doubled.
            resize(capacity_ == 0 ? 1 : capacity_*2);
        }
        data[size_++] = value;
    }

    std::size_t size() const{
        return size_;
    }
    //operator - access as non const = free to change
    T& Vector<T>::operator[](std::size_t index){
    if(index >= size_){
        //check in runtime
        throw std::out_of_range("Index out of range");
    }
    return data[index];
    }
    //operator - access as const = for read
    const T& Vector<T>::operator[](std::size_t index) const{
        if(index >= size_){
            //check in runtime
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    //clear vector
    //size = 0, but capacity will maintain => reuse space later
    void Vector<T>::clear(){
        size_ = 0;
    }
};

#endif