//
// Created by dimal on 11.10.2022.
//

#ifndef LABORATORYWORK_1_REVERSEITERATOR_H
#define LABORATORYWORK_1_REVERSEITERATOR_H

template <typename Iterator>
class ReverseIterator {
public:

    ReverseIterator();
    ReverseIterator(const ReverseIterator& other);
    ReverseIterator(ReverseIterator&& other) noexcept;

    ReverseIterator& operator+=(int x);
    ReverseIterator operator+(int x) const;
    ReverseIterator& operator-=(int x);
    ReverseIterator operator-(int x) const;
    ReverseIterator& operator++();
    ReverseIterator operator++(int);
    ReverseIterator& operator--();
    ReverseIterator operator--(int);
    int operator-(const ReverseIterator& other) const;
    typename Iterator::ValueType& operator*();
    const typename Iterator::ValueType& operator*() const;
    ReverseIterator* operator->() const;
    typename Iterator::ValueType& operator[](int x);
    const typename Iterator::ValueType& operator[](int x) const;
    bool operator<(const ReverseIterator& other) const;
    bool operator<=(const ReverseIterator& other) const;
    bool operator>=(const ReverseIterator& other) const;
    bool operator>(const ReverseIterator& other) const;
    bool operator==(const ReverseIterator& other) const;
    bool operator!=(const ReverseIterator& other) const;

    explicit ReverseIterator(const Iterator& iterator);

private:
    Iterator iterator_;
};


#endif //LABORATORYWORK_1_REVERSEITERATOR_H
