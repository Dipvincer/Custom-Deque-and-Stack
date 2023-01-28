//
// Created by dimal on 11.10.2022.
//

#include "ReverseIterator.h"

template <typename Iterator>
ReverseIterator<Iterator>::ReverseIterator() = default;

template <typename Iterator>
ReverseIterator<Iterator>::ReverseIterator(const ReverseIterator& other)
= default;

template <typename Iterator>
ReverseIterator<Iterator>::ReverseIterator(ReverseIterator&& other)
noexcept = default;

template <typename Iterator>
ReverseIterator<Iterator>::ReverseIterator(const Iterator& iterator)
: iterator_(iterator - 1) {}

template <typename Iterator>
ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator+=(int x) {
    iterator_ += -x;
    return *this;
}

template <typename Iterator>
ReverseIterator<Iterator> ReverseIterator<Iterator>::operator+
        (int x) const {
    ReverseIterator result(*this);
    result += x;
    return result;
}

template <typename Iterator>
ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator-=
        (int x) {
    *this += -x;
    return *this;
}

template <typename Iterator>
ReverseIterator<Iterator> ReverseIterator<Iterator>::operator-
        (int x) const {
    ReverseIterator result(*this);
    result += -x;
    return result;
}

template <typename Iterator>
ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator++
        () {
    *this += 1;
    return *this;
}

template <typename Iterator>
ReverseIterator<Iterator> ReverseIterator<Iterator>::operator++
        (int) {
    ReverseIterator temp = *this;
    *this += 1;
    return temp;
}

template <typename Iterator>
ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator--
        () {
    *this -= 1;
    return *this;
}

template <typename Iterator>
ReverseIterator<Iterator> ReverseIterator<Iterator>::operator--
        (int) {
    ReverseIterator temp = *this;
    *this -= 1;
    return temp;
}

template <typename Iterator>
int ReverseIterator<Iterator>::operator-(const ReverseIterator& other)
const {
    return other.iterator_ - iterator_;
}

template <typename Iterator>
typename Iterator::ValueType& ReverseIterator<Iterator>::operator*() {
    return *iterator_;
}

template <typename Iterator>
const typename Iterator::ValueType& ReverseIterator<Iterator>::operator*()
        const {
    return *iterator_;
}

template <typename Iterator>
ReverseIterator<Iterator>* ReverseIterator<Iterator>::operator->
        () const {
    return this;
}

template <typename Iterator>
typename Iterator::ValueType& ReverseIterator<Iterator>::operator[](int x) {
    return *(*this + x);
}

template <typename Iterator>
const typename Iterator::ValueType&
ReverseIterator<Iterator>::operator[](int x) const {
    return *(*this + x);
}

template <typename Iterator>
bool ReverseIterator<Iterator>::operator<(const ReverseIterator& other)
const {
    return (*this - other < 0);
}

template <typename Iterator>
bool ReverseIterator<Iterator>::operator>(const ReverseIterator& other)
const {
    return other < *this;
}

template <typename Iterator>
bool ReverseIterator<Iterator>::operator<=(const ReverseIterator& other)
const {
    return !(*this > other);
}

template <typename Iterator>
bool ReverseIterator<Iterator>::operator>=(const ReverseIterator& other)
const {
    return !(*this < other);
}

template <typename Iterator>
bool ReverseIterator<Iterator>::operator==(const ReverseIterator& other)
const {
    return (*this >= other) && (*this <= other);
}

template <typename Iterator>
bool ReverseIterator<Iterator>::operator!=(const ReverseIterator& other)
const {
    return !(*this == other);
}
