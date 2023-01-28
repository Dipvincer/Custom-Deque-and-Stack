//
// Created by dimal on 02.10.2022.
//

#include "Deque.h"


// Deque::Iterator implementation


template <typename T, size_t PageSize>
Deque<T, PageSize>::Iterator::Iterator() = default;

template <typename T, size_t PageSize>
Deque<T, PageSize>::Iterator::Iterator(const Deque::Iterator& other) = default;

template <typename T, size_t PageSize>
Deque<T, PageSize>::Iterator::Iterator(Deque::Iterator&& other)
noexcept = default;

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator&
Deque<T, PageSize>::Iterator::operator+=(int x) {
    T** oldPage = currentPage_;
    if (((obj_ - *currentPage_) + x) < 0) {
        currentPage_ += ((obj_ - *currentPage_) + x -
                (int) (PageSize / sizeof (T)) + 1) /
                        (int) (PageSize / sizeof (T));
        if (currentPage_ < first_) {
            currentPage_ = first_;
            obj_ = *currentPage_ - 1;
            return *this;
        }
        obj_ = *currentPage_ + (PageSize / sizeof (T)) - 1 -
               ((obj_ - *oldPage) + x -
                (PageSize / sizeof (T)) + 1) % (PageSize / sizeof (T));
    } else {
        currentPage_ += ((obj_ - *currentPage_) + x) /
                        (PageSize / sizeof (T));
        if (currentPage_ > last_) {
            currentPage_ = last_;
            obj_ = *currentPage_ + (PageSize / sizeof (T));
            return *this;
        }
        obj_ = *currentPage_ + ((obj_ - *oldPage) + x)%(PageSize / sizeof (T));
    }
    return *this;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator Deque<T, PageSize>::Iterator::operator+
(int x) const {
    Deque::Iterator result(*this);
    result += x;
    return result;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator& Deque<T, PageSize>::Iterator::operator-=
(int x) {
    *this += -x;
    return *this;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator Deque<T, PageSize>::Iterator::operator-
(int x) const {
    Deque::Iterator result(*this);
    result += -x;
    return result;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator& Deque<T, PageSize>::Iterator::operator++
() {
    *this += 1;
    return *this;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator Deque<T, PageSize>::Iterator::operator++
(int) {
    Deque::Iterator temp = *this;
    *this += 1;
    return temp;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator& Deque<T, PageSize>::Iterator::operator--
() {
    *this -= 1;
    return *this;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator Deque<T, PageSize>::Iterator::operator--
(int) {
    Deque::Iterator temp = *this;
    *this -= 1;
    return temp;
}

template <typename T, size_t PageSize>
int Deque<T, PageSize>::Iterator::operator-(const Deque::Iterator& other)
const {
    return (currentPage_ - other.currentPage_) * (PageSize /sizeof (T))
           + (obj_ - *currentPage_) -
           (other.obj_ - *other.currentPage_);
}

template <typename T, size_t PageSize>
T& Deque<T, PageSize>::Iterator::operator*() {
    return *obj_;
}

template <typename T, size_t PageSize>
const T& Deque<T, PageSize>::Iterator::operator*() const {
    return *obj_;
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator* Deque<T, PageSize>::Iterator::operator->
() const {
    return this;
}

template <typename T, size_t PageSize>
T& Deque<T, PageSize>::Iterator::operator[](int x) {
    return *(*this + x);
}

template <typename T, size_t PageSize>
const T& Deque<T, PageSize>::Iterator::operator[](int x) const {
    return *(*this + x);
}

template <typename T, size_t PageSize>
bool Deque<T, PageSize>::Iterator::operator<(const Deque::Iterator& other)
const {
    return (*this - other < 0);
}

template <typename T, size_t PageSize>
bool Deque<T, PageSize>::Iterator::operator>(const Deque::Iterator& other)
const {
    return other < *this;
}

template <typename T, size_t PageSize>
bool Deque<T, PageSize>::Iterator::operator<=(const Deque::Iterator& other)
const {
    return !(*this > other);
}

template <typename T, size_t PageSize>
bool Deque<T, PageSize>::Iterator::operator>=(const Deque::Iterator& other)
const {
    return !(*this < other);
}

template <typename T, size_t PageSize>
bool Deque<T, PageSize>::Iterator::operator==(const Deque::Iterator& other)
const {
    return (*this >= other) && (*this <= other);
}

template <typename T, size_t PageSize>
bool Deque<T, PageSize>::Iterator::operator!=(const Deque::Iterator& other)
const {
    return !(*this == other);
}

template <typename T, size_t PageSize>
Deque<T, PageSize>::Iterator::Iterator(T* obj, T** page, T** first, T** last) :
        obj_(obj), currentPage_(page), first_(first), last_(last) {}


// other Deque:: stuff implementation


template <typename T, size_t PageSize>
Deque<T, PageSize>::Deque(): pageArray_(nullptr), numberOfPages_(0),
         begin_(nullptr), end_(nullptr) {}

template <typename T, size_t PageSize>
Deque<T, PageSize>::Deque(const Deque& other) {
    pageArray_ = (T**) malloc(sizeof(T*) * other.numberOfPages_);
    numberOfPages_ = other.numberOfPages_;
    for (int i = 0; i < numberOfPages_; ++i) {
        pageArray_[i] = (T*) malloc(PageSize);
        memcpy(pageArray_[i], other.pageArray_[i], PageSize);
    }
    begin_ = *pageArray_ + (other.begin_ - *other.pageArray_);
    end_ = pageArray_[numberOfPages_ - 1] + (other.end_ -
            other.pageArray_[numberOfPages_ - 1]);
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator Deque<T, PageSize>::Begin()
const noexcept {
    return Iterator(begin_, pageArray_, pageArray_,
                    pageArray_ + numberOfPages_ - 1);
}

template <typename T, size_t PageSize>
typename Deque<T, PageSize>::Iterator Deque<T, PageSize>::End()
const noexcept {
    return Iterator(end_, pageArray_ + numberOfPages_ - 1,
                    pageArray_, pageArray_ + numberOfPages_ - 1);
}

template <typename T, size_t PageSize>
ReverseIterator<typename Deque<T,
PageSize>::Iterator> Deque<T, PageSize>::RBegin()
const noexcept {
    return ReverseIterator<typename Deque<T, PageSize>::Iterator>(End());
}

template <typename T, size_t PageSize>
ReverseIterator<typename Deque<T,
PageSize>::Iterator> Deque<T, PageSize>::REnd()
const noexcept {
    return ReverseIterator<typename Deque<T, PageSize>::Iterator>(Begin());
}

template <typename T, size_t PageSize>
void Deque<T, PageSize>::PushBack(const T& value) {
    if (end_) {
        if (pageArray_[numberOfPages_ - 1] + PageSize /sizeof(T) != end_) {
            *(end_++) = value;
            return;
        }
        pageArray_ = (T**) realloc(pageArray_, numberOfPages_ + 1);
        ++numberOfPages_;
        pageArray_[numberOfPages_ - 1] = (T*) malloc(PageSize);
        end_ = pageArray_[numberOfPages_ - 1];
        *(end_++) = value;
        return;
    }
    pageArray_ = (T**) malloc(sizeof(T*));
    numberOfPages_ = 1;
    *pageArray_ = (T*) malloc(PageSize);
    begin_ = *pageArray_;
    end_ = *pageArray_;
    *(end_++) = value;
}

template <typename T, size_t PageSize>
Deque<T, PageSize>::~Deque() {
    for (int i = 0; i < numberOfPages_; ++i) {
        free(pageArray_[i]);
    }
    free(pageArray_);
    pageArray_ = nullptr;
    begin_ = nullptr;
    end_ = nullptr;
    numberOfPages_ = 0;
}

template <typename T, size_t PageSize>
void Deque<T, PageSize>::PopBack() {
    Iterator temp = End() - 1;
    if (End().obj_ == *(End().currentPage_)) {
        if (numberOfPages_ == 1) {
            Clear();
            return;
        }
        T* oldPage = End().obj_;
        (*End()).~T();
        free(oldPage);
        --numberOfPages_;
    } else {
        (*End()).~T();
    }
    end_ = temp.obj_;
}

template <typename T, size_t PageSize>
void Deque<T, PageSize>::PushFront(const T& value) {
    if (begin_) {
        if (*pageArray_ != begin_) {
            *(--begin_) = value;
            return;
        }
        pageArray_ = realloc(pageArray_, numberOfPages_ + 1);
        memmove(pageArray_ + 1, pageArray_, numberOfPages_);
        ++numberOfPages_;
        *pageArray_ = malloc(PageSize);
        begin_ = *pageArray_ + PageSize / sizeof(T) - 1;
        *begin_ = value;
        return;
    }
    pageArray_ = malloc(sizeof(T*));
    numberOfPages_ = 1;
    *pageArray_ = malloc(PageSize);
    begin_ = *pageArray_ + PageSize / sizeof(T) - 1;
    end_ = *pageArray_ + PageSize / sizeof(T);
    *begin_ = value;
}

template <typename T, size_t PageSize>
void Deque<T, PageSize>::PopFront() {
    Iterator temp = Begin() + 1;
    if (Begin().obj_ == *(Begin().currentPage_) + PageSize / sizeof(T)) {
        if (numberOfPages_ == 1) {
            ~Deque();
            return;
        }
        T* oldPage = *Begin().currentPage_;
        (*Begin()).~T();
        free(oldPage);
        --numberOfPages_;
        memmove(pageArray_, pageArray_ + 1, numberOfPages_);
    } else {
        (*End()).~T();
    }
    begin_ = temp.obj_;
}

template <typename T, size_t PageSize>
void Deque<T, PageSize>::Clear() {
    this->~Deque();
}

template <typename T, size_t PageSize>
size_t Deque<T, PageSize>::Size() const {
    if (this->pageArray_ == nullptr) {
        return 0;
    }
    return End() - Begin();
}

template <typename T, size_t PageSize>
Deque<T, PageSize>& Deque<T, PageSize>::operator= (const Deque& other) {
    ~Deque();
    *this = Deque(other);
    return *this;
}

template <typename T, size_t PageSize>
Deque<T, PageSize>& Deque<T, PageSize>::operator= (Deque&& other)
        noexcept = default;

template <typename T, size_t PageSize>
T& Deque<T, PageSize>::operator[](size_t index) {
    return Begin()[index];
}

template <typename T, size_t PageSize>
const T& Deque<T, PageSize>::operator[](size_t index) const {
    return Begin()[index];
}

template <typename T, size_t PageSize>
T& Deque<T, PageSize>::Front() {
    return *begin_;
}

template <typename T, size_t PageSize>
const T& Deque<T, PageSize>::Front() const {
    return *begin_;
}

template <typename T, size_t PageSize>
T& Deque<T, PageSize>::Back() {
    return *(end_ - 1);
}

template <typename T, size_t PageSize>
const T& Deque<T, PageSize>::Back() const {
    return *(end_ - 1);
}

