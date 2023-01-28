//
// Created by dimal on 02.10.2022.
//

#ifndef LABORATORYWORK_1_STACK_H
#define LABORATORYWORK_1_STACK_H

#include <cstdlib>
#include "Deque.cpp"
#include "Complex.h"
#include <fstream>

template <typename T, class Container = Deque<T>>
class Stack {

public:

    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack();
    Stack& operator=(const Stack& other);

    T& Top();
    const T& Top() const ;
    bool Empty() const ;
    size_t Size() const ;
    void Push(const T& value);
    void Pop();

    class StackIterator {

    public:

        typedef T ValueType;

        StackIterator& operator+=(int x);
        StackIterator operator+(int x) const;
        StackIterator& operator-=(int x);
        StackIterator operator-(int x) const;
        StackIterator& operator++();
        StackIterator operator++(int);
        StackIterator& operator--();
        StackIterator operator--(int);
        int operator-
        (const typename Stack<T, Container>::StackIterator& other) const;
        T& operator*();
        const T& operator*() const;
        StackIterator* operator->() const;
        T& operator[](int x);
        const T& operator[](int x) const;

        bool operator<
        (const typename Stack<T, Container>::StackIterator& other) const;
        bool operator>
        (const typename Stack<T, Container>::StackIterator& other) const;
        bool operator>=
        (const typename Stack<T, Container>::StackIterator& other) const;
        bool operator<=
        (const typename Stack<T, Container>::StackIterator& other) const;
        bool operator==
        (const typename Stack<T, Container>::StackIterator& other) const;
        bool operator!=
        (const typename Stack<T, Container>::StackIterator& other) const;

        StackIterator();
        StackIterator(const StackIterator& other);
        StackIterator(StackIterator&& other) noexcept;
        explicit StackIterator
        (const typename Container::Iterator& containerIterator);
        ~StackIterator();

    private:
        typename Container::Iterator iterator_;

    };

private:
    Container container_;

public:
    StackIterator Begin() const;
    ReverseIterator<StackIterator> RBegin() const;
    StackIterator End() const;
    ReverseIterator<StackIterator> REnd() const;
    void Clear();

    void ImportFromFile(const char* path);
    void AppendFromFile(const char* path);
    void ExportToFile(const char* path);
    void CopyToFile(const char* path) const;
    void CopyBackwardToFile(const char* path) const;

};


#endif //LABORATORYWORK_1_STACK_H
