//
// Created by dimal on 02.10.2022.
//

#ifndef LABORATORYWORK_1_DEQUE_H
#define LABORATORYWORK_1_DEQUE_H

#include <cstdlib>
#include <cstring>
#include "ReverseIterator.cpp"

template <typename T, size_t PageSize = 4096>
class Deque {
public:

    class Iterator {
    public:

        typedef T ValueType;

        Iterator();
        Iterator(const Deque::Iterator& other);
        Iterator(Deque::Iterator&& other) noexcept;

        Iterator& operator+=(int x);
        Iterator operator+(int x) const;
        Iterator& operator-=(int x);
        Iterator operator-(int x) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        int operator-(const Deque::Iterator& other) const;
        T& operator*();
        const T& operator*() const;
        Iterator* operator->() const;
        T& operator[](int x);
        const T& operator[](int x) const;
        bool operator<(const Deque::Iterator& other) const;
        bool operator<=(const Deque::Iterator& other) const;
        bool operator>=(const Deque::Iterator& other) const;
        bool operator>(const Deque::Iterator& other) const;
        bool operator==(const Deque::Iterator& other) const;
        bool operator!=(const Deque::Iterator& other) const;

    private:

        Iterator(T* obj, T** page, T** first, T** last);

        T* obj_;
        T** currentPage_;
        T** first_;
        T** last_;

        friend class Deque;
    };

    Deque();
    Deque(const Deque& other);

    Iterator Begin() const noexcept;
    Iterator End() const noexcept;
    ReverseIterator<Iterator> RBegin() const noexcept;
    ReverseIterator<Iterator> REnd() const noexcept;

    void PushBack(const T& value);
    void PopBack();
    void PushFront(const T& value);
    void PopFront();

    void Clear();
    size_t Size() const;

    Deque& operator= (const Deque& other);
    Deque& operator= (Deque&& other) noexcept;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& Front();
    const T& Front() const;
    T& Back();
    const T& Back() const;

    ~Deque();

private:
    T** pageArray_;
    size_t numberOfPages_;
    T* begin_;
    T* end_;
};


#endif //LABORATORYWORK_1_DEQUE_H
