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

public:
    //constructor and destructor
    Vector() : data(nullptr), size_(0), capacity_(0){}
    //copy constructor for deep copy from another vector
    Vector(const Vector&other):data(nullptr),size_(other.size_),capacity_(other.capacity_){
        if(capacity_>0){
            data = new T[capacity_];
            //copy elements
            for(std::size_t i = 0;i<size_;i++){
                data[i] = other.data[i];
            }
        }
    }
    //copy assignment operator
    Vector& operator=(const Vector& other){
        if(this != &other){
            T* new_data = nullptr;
            if(other.capacity_>0){
                new_data = new T[other.capacity_];
                //copy elements
                for(std::size_t i = 0;i<other.size_;i++){
                    new_data[i] = other.data[i];
                }
            }
            //free old memory
            delete[] data;
            data = new_data;
            //cop size and capacity
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }
    std::size_t Size() const{
        return size_;
    }
    //add new data at the end of the array
    void PushBack(const T& value){
        if(size_ == capacity_){
            //space will be doubled.
            Reserve(capacity_ == 0 ? 1 : capacity_*2);
        }
        data[size_++] = value;
    }
    //operator - access as non const = free to change
    T& operator[](std::size_t index){
        if(index >= size_){
            //check in runtime
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    //operator - access as const = for read
    const T& operator[](std::size_t index) const{
        if(index >= size_){
            //check in runtime
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    //clear vector
    //size = 0, but capacity will maintain => reuse space later
    void Clear(){
        size_ = 0;
    }
    //change capacity to new_capacity
    void Reserve(std::size_t new_capacity){
        if(new_capacity <= capacity_){
            return;
        }
        T* new_data = new T[new_capacity];
        for(std::size_t i = 0;i<size_;i++){
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity_ = new_capacity;
    }

    //change size to new_size
    void Resize(std::size_t new_size){
        if(new_size>capacity_){
            Reserve(new_size);
        }
        size_ = new_size;
    }
};

#endif