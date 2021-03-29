#pragma once

#include <cstring>
#include <stdexcept>

const size_t CAPACITY_MULTIPLIER = 2;
const size_t MIN_CAPACITY = 4;


template <typename T> 
class TVector {
public:
    TVector() {
        size_ = 0;
        capacity_ = MIN_CAPACITY;
        body_ = new T[MIN_CAPACITY];
    }

    TVector(size_t size) {
        capacity_ = size;
        size_ = size;
        body_ = new T[size];
    }

    TVector(size_t size, uint64_t value) {
        capacity_ = size;
        size_ = size;
        body_ = new T[size];
        for (size_t i = 0; i < size; ++i) {
            body_[i] = value;
        }
    }

    TVector(const TVector& other) : TVector() {
        TVector next(other.capacity_);
        next.size_ = other.size_;

        if (other.body_) {
            for (size_t i = 0; i < other.Size(); ++i) {
                next.body_[i] = other.body_[i];
            }
        }
        Swap(next, *this);
    }
    
    size_t Size() const {
        return size_;
    }

    T* begin() const {
        return body_;
    }

    T* end() const {
        if (body_) {
            return body_ + size_;
        }
        return nullptr;
    }

    void PushBack(const T& value) {
        if (size_ < capacity_) {
            body_[size_++] = value;
            return;
        }
        
        capacity_ *= CAPACITY_MULTIPLIER;
        T* temp = body_;
        body_ = new T[capacity_];
        memcpy(body_, temp, size_ * sizeof(T));
        body_[size_++] = value;
        delete[] temp;
    }

    const T& operator[](size_t index) const {
        if (index >= size_ || index < 0) {
            throw std::out_of_range("Out of range index");
        }
        return body_[index];
    }

    T& operator[](size_t index) {
        if (index >= size_ || index < 0) {
            throw std::out_of_range("Out of range index");
        }
        return body_[index];
    }

    void Swap(TVector& lhs, TVector& rhs) {
        T* tmp = rhs.body_;
        rhs.body_ = lhs.body_;
        lhs.body_ = tmp;
        Swap(lhs.capacity_, rhs.capacity_);
        Swap(lhs.size_, rhs.size_);
    }

    TVector& operator=(TVector other) {
        TVector next(other);
        Swap(next, *this);
        return *this;
    }

    ~TVector() {
        delete[] body_;
        size_ = 0;
        capacity_ = 0;
        body_ = nullptr;
    }

private:
    size_t size_;
    size_t capacity_;
    T* body_;

    void Swap(size_t& lhs, size_t& rhs) {
        size_t tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
};