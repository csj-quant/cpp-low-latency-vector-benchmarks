#pragma once
#include <new>
#include <cstdlib>
#include <cstring>
#include <utility>

template<typename T>
class mini_vector
{
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_cap)
    {
        T* new_block = static_cast<T*>(operator new[](new_cap * sizeof(T)));

        // move or copy old data
        for (size_t i=0;i<size_;i++)
        {
            new(new_block + i) T(std::move(data_[i]));
        }

        // destroy old objects
        for (size_t i = 0; i < size_; i++)
        {
            data_[i].~T();
        }

        operator delete[](data_);

        data_ = new_block;
        capacity_ = new_cap;
    }

public:
    mini_vector() : data_(nullptr), size_(0), capacity_(0) {}

    ~mini_vector()
    {
        for (size_t i = 0; i < size_; i++)
        {
            data_[i].~T();
        }
        operator delete[](data_);
    }

    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        new(data_ + size_) T(value);
        size_++;
    }

    void reserve(size_t new_cap)
    {
        if (new_cap > capacity_)
        {
            reallocate(new_cap);
        }
    }

    T& operator[](size_t idx)
    {
        return data_[idx];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    T* data() const{ return data_; }
};