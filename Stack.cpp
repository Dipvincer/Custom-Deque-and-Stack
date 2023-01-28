//
// Created by dimal on 02.10.2022.
//

#include "Stack.h"


template <typename T, class Container>
Stack<T, Container>::Stack() = default;

template <typename T, class Container>
Stack<T, Container>::Stack(const Stack& other) :
container_(other.container_) {};

template <typename T, class Container>
Stack<T, Container>::Stack(Stack&& other) noexcept = default;

template <typename T, class Container>
Stack<T, Container>& Stack<T, Container>::operator=(const Stack& other) {
    container_.~Container();
    container_ = Container(other.container_);
    return *this;
}

template <typename T, class Container>
T& Stack<T, Container>::Top() {
    return container_.Back();
}

template <typename T, class Container>
const T& Stack<T, Container>::Top() const {
    return container_.Back();
}

template <typename T, class Container>
bool Stack<T, Container>::Empty() const {
    return container_.Size() == 0;
}

template <typename T, class Container>
size_t Stack<T, Container>::Size() const {
    return container_.Size();
}

template <typename T, class Container>
void Stack<T, Container>::Push(const T& value) {
    container_.PushBack(value);
}

template <typename T, class Container>
void Stack<T, Container>::Pop() {
    container_.PopBack();
}

template <typename T, class Container>
Stack<T, Container>::~Stack() {
    container_.~Container();
}


template <typename T, class Container>
typename Stack<T, Container>::StackIterator&
Stack<T, Container>::StackIterator::operator+=(int x) {
    iterator_ += x;
    return *this;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator
Stack<T, Container>::StackIterator::operator+(int x) const {
    auto result = *this;
    result += x;
    return result;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator&
Stack<T, Container>::StackIterator::operator-=(int x) {
    iterator_ -= x;
    return *this;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator
Stack<T, Container>::StackIterator::operator-(int x) const {
    auto result = *this;
    result -= x;
    return result;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator&
Stack<T, Container>::StackIterator::operator++() {
    iterator_ += 1;
    return *this;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator
Stack<T, Container>::StackIterator::operator++(int) {
    typename Container::Iterator temp = *this;
    iterator_ += 1;
    return temp;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator&
Stack<T, Container>::StackIterator::operator--() {
    iterator_ -= 1;
    return *this;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator
Stack<T, Container>::StackIterator::operator--(int) {
    typename Container::Iterator temp = *this;
    iterator_ -= 1;
    return temp;
}

template <typename T, class Container>
int Stack<T, Container>::StackIterator::operator-
(const typename Stack<T, Container>::StackIterator& other) const {
    return (this->iterator_ - other.iterator_);
}

template <typename T, class Container>
T& Stack<T, Container>::StackIterator::operator*() {
    return *iterator_;
}

template <typename T, class Container>
const T& Stack<T, Container>::StackIterator::operator*() const {
    return *iterator_;
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator*
Stack<T, Container>::StackIterator::operator->() const {
    return this;
}

template <typename T, class Container>
T& Stack<T, Container>::StackIterator::operator[](int x) {
    return iterator_[x];
}

template <typename T, class Container>
const T& Stack<T, Container>::StackIterator::operator[](int x) const {
    return iterator_[x];
}

template <typename T, class Container>
bool Stack<T, Container>::StackIterator::operator<
(const typename Stack<T, Container>::StackIterator& other) const {
    return iterator_ < other.iterator_;
}

template <typename T, class Container>
bool Stack<T, Container>::StackIterator::operator>
(const typename Stack<T, Container>::StackIterator& other) const {
    return iterator_ > other.iterator_;
}

template <typename T, class Container>
bool Stack<T, Container>::StackIterator::operator==
(const typename Stack<T, Container>::StackIterator& other) const {
    return iterator_ == other.iterator_;
}

template <typename T, class Container>
bool Stack<T, Container>::StackIterator::operator!=
(const typename Stack<T, Container>::StackIterator& other) const {
    return iterator_ != other.iterator_;
}

template <typename T, class Container>
bool Stack<T, Container>::StackIterator::operator>=
(const typename Stack<T, Container>::StackIterator& other) const {
    return iterator_ >= other.iterator_;
}

template <typename T, class Container>
bool Stack<T, Container>::StackIterator::operator<=
(const typename Stack<T, Container>::StackIterator& other) const {
    return iterator_ <= other.iterator_;
}

template <typename T, class Container>
Stack<T, Container>::StackIterator::StackIterator() = default;

template <typename T, class Container>
Stack<T, Container>::StackIterator::StackIterator
(const StackIterator& other) = default;

template <typename T, class Container>
Stack<T, Container>::StackIterator::StackIterator(StackIterator&& other)
noexcept = default;

template <typename T, class Container>
Stack<T, Container>::StackIterator::StackIterator
(const typename Container::Iterator& containerIterator) :
iterator_(containerIterator) {}

template <typename T, class Container>
Stack<T, Container>::StackIterator::~StackIterator() = default;

template <typename T, class Container>
typename Stack<T,Container>::StackIterator Stack<T, Container>::Begin() const {
    return StackIterator(container_.Begin());
}

template <typename T, class Container>
ReverseIterator<typename Stack<T, Container>::StackIterator>
        Stack<T,Container>::RBegin() const {
    return ReverseIterator<typename Stack<T, Container>::StackIterator>(End());
}

template <typename T, class Container>
typename Stack<T, Container>::StackIterator Stack<T, Container>::End() const {
    return StackIterator(container_.End());
}

template <typename T, class Container>
ReverseIterator<typename Stack<T, Container>::StackIterator>
        Stack<T, Container>::REnd() const {
    return ReverseIterator<typename Stack<T,
    Container>::StackIterator>(Begin());
}

template <typename T, class Container>
void Stack<T, Container>::Clear() {
    container_.Clear();
}

template <typename T, class Container>
void Stack<T, Container>::ImportFromFile(const char *path) {
    this->Clear();
    std::ifstream input;
    input.open(path);
    T buf;
    while(input >> buf) {
        Push(buf);
    }
}

template <typename T, class Container>
void Stack<T, Container>::ExportToFile(const char *path) {
    std::ofstream output;
    output.open(path);
    while(Size() != 0) {
        output << Top() << '\n';
        Pop();
    }
}

template <typename T, class Container>
void Stack<T, Container>::AppendFromFile(const char* path) {
    std::ifstream input;
    input.open(path);
    T buf;
    while(input >> buf) {
        Push(buf);
    }
}

template <typename T, class Container>
void Stack<T, Container>::CopyToFile(const char* path) const {
    std::ofstream output;
    output.open(path);
    for (StackIterator it = Begin(); it != End(); ++it) {
        output << *it << '\n';
    }
}

template <typename T, class Container>
void Stack<T, Container>::CopyBackwardToFile(const char* path) const {
    std::ofstream output;
    output.open(path);
    for (auto it = RBegin(); it != REnd(); ++it) {
        output << *it << '\n';
    }
}

template<typename T, class Container>
T Stack<T, Container>::ComplexEvaluate() const {
    if (Empty()) {
        return Complex();
    }
    Complex result = *Begin();
    for (StackIterator it = Begin() + 1; it != End(); ++it) {
        if ((*(it - 1)).CRefOp()->ClassName() == "Plus") {
            result.RefRegular() += (*it).CRefRegular();
            result.RefImaginary() += (*it).CRefImaginary();
        } else if ((*(it - 1)).CRefOp()->ClassName() == "Minus") {
            result.RefRegular() -= (*it).CRefRegular();
            result.RefImaginary() -= (*it).CRefImaginary();
        } else if ((*(it - 1)).CRefOp()->ClassName() == "Mul") {
            result.RefRegular() = (*(it - 1)).CRefRegular() *
                    (*it).CRefRegular() -
                    (*(it - 1)).CRefImaginary() * (*it).CRefImaginary();
            result.RefImaginary() = (*(it - 1)).CRefRegular() *
                    (*it).CRefImaginary() +
                    (*(it - 1)).CRefImaginary() * (*it).CRefRegular();
        } else if ((*(it - 1)).CRefOp()->ClassName() == "Div") {
            result.RefRegular() = ((*(it - 1)).CRefRegular() *
                    (*it).CRefRegular() +
                    (*(it - 1)).CRefImaginary() * (*it).CRefImaginary()) /
                    ((*it).CRefRegular() * (*it).CRefRegular() +
                    (*it).CRefImaginary() * (*it).CRefImaginary());
            result.RefImaginary() = ((*it).CRefRegular() *
                    (*(it - 1)).CRefImaginary() -
                    (*(it - 1)).CRefRegular() * (*it).CRefImaginary()) /
                            ((*it).CRefRegular() * (*it).CRefRegular() +
                            (*it).CRefImaginary() * (*it).CRefImaginary());
        } else {
            break;
        }
    }
    result.RefOp() = new Equal();
    return result;
}


