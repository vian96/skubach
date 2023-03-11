#ifndef MY_LIST_H
#define MY_LIST_H

#include <cassert>
#include <vector>
#include <iostream>
#include <stdexcept>

// TODO probably it is not okay to have it here
template<typename Container>
concept Iterable = requires(Container t) {
        { *t.begin()++, t.end() }; // it has end and you can increment and dereference begin
};

template<typename T>
class List {
    // WARNING iterators and for i:list are not working with const properly
private:
    struct Node {
        Node *next;
        Node *prev;
        T data;

        Node() {}
        Node(Node *next_, Node *prev_, const T &data_) : next(next_), prev(prev_), data(data_) {}
    };

    Node *head = nullptr;
    Node *back = nullptr;

    int size_ = 0;
public:
    List();
    ~List();

    template<Iterable ContT>
    List(ContT &v);

    List &operator=(List<T>& other);

    int size() const;

    void push_back(const T &elem); 
    void push_front(const T &elem); 
    
    void pop_back(); 
    void pop_front(); 

    T& operator[](int idx);
    const T& operator[](int idx) const;

    class Iterator {
        // WARNING iterators and for i:list are not working with const properly
        // WARNING this iterator relies on the fact that any ptr%2==0
        public:
        Node *ptr;

        public:
        Iterator(){}
        Iterator(Node *ptr_) : ptr(ptr_){}

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        Iterator& operator+=(int rhs);
        Iterator& operator-=(int rhs);

        friend Iterator operator+(Iterator lhs, int rhs) {
            lhs += rhs; 
            return lhs; 
        }

        friend Iterator operator-(Iterator lhs, int rhs) {
            lhs -= rhs; 
            return lhs; 
        }

        Iterator& operator=(const Iterator& other);
        T& operator* ();
        T& operator-> ();

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.ptr == rhs.ptr;
        }
        // TODO is there any way to put op+,-,== out of class?
        // https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
    };

    Iterator begin();
    Iterator end();

    Iterator insert(Iterator it, const T &elem);
    Iterator erase(Iterator it);
};

//-----------------------------------------------
// LIST MEMBERS
//-----------------------------------------------

// Constructors, destructors, assign

template<typename T>
List<T>::List() {
    size_ = 0;
};

template<typename T>
List<T>::~List() {
    while (size())
        pop_back();
}

template<typename DataT>
template<Iterable ContT>
List<DataT>::List(ContT &v) {
    for (const auto &i : v)
        push_back(i);
}

template<typename T>
List<T> &List<T>::operator=(List<T>& other) {
    if (this == &other)
        return *this;

    new (this) List(other);
    return *this;
}

// Access functions

template<typename T>
T& List<T>::operator[](int idx) {
    if (idx < 0 || idx >= size_)
        throw std::out_of_range("operator [] out of range");

    Node *cur = head;
    for (int i = 0; i < idx; i++)
        cur = cur->next;
    return cur->data;
};

template<typename T>
const T& List<T>::operator[](int idx) const {
    if (idx < 0 || idx >= size_)
        throw std::out_of_range("operator [] out of range");

    Node *cur = head;
    for (int i = 0; i < idx; i++)
        cur = cur->next;
    return cur->data;
};

template<typename T>
int List<T>::size() const {
    return size_;
}

// Basic modify

template<typename T>
void List<T>::push_back(const T &elem) {
    if (!size()) {
        head = new Node(nullptr, nullptr, elem);
        back = head;
        size_++;
        return;
    }

    back->next = new Node(nullptr, back, elem);
    back = back->next;
    size_++;
} 

template<typename T>
void List<T>::push_front(const T &elem) {
    if (!size()) {
        push_back(elem);
        return;
    }

    Node *temp = new Node(head, nullptr, elem);
    head->prev = temp;
    head = temp;
    size_++;
} 

template<typename T>
void List<T>::pop_back() {
    if (!size())
        throw std::out_of_range("operator pop out of empty list");

    if (size() == 1) {
        delete head;
        size_--;
        head = nullptr;
        back = nullptr;
        return;
    }

    Node *prev = back->prev;
    delete back;
    back = prev;
    back->next = nullptr;
    size_--;
} 

template<typename T>
void List<T>::pop_front() {
    if (!size())
        throw std::out_of_range("operator pop out of empty list");

    if (size() == 1) {
        pop_back();
        return;
    }

    Node *prev = head->next;
    delete head;
    head = prev;
    head->prev = nullptr;
    size_--;
} 

// Iterators functions

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator((Node*)((unsigned long long)back + 1));
}

template<typename T>
typename List<T>::Iterator List<T>::insert(Iterator it, const T &elem) {
    if (it == begin()) {
        push_front(elem);
        return begin();
    }
    if (it == end()) {
        push_back(elem);
        auto t = end() - 1;
        return t;
    }

    size_++;
    Node *temp = new Node(it.ptr, it.ptr->prev, elem);
    temp->prev->next = temp;
    temp->next->prev = temp;
    return --it;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator it) {
    if (it == end())
        throw std::out_of_range("Erasing element behind last");

    if (it == begin()) {
        pop_front();
        return begin();
    }
    if (it == end() - 1) {
        pop_back();
        return end();
    }

    size_--;
    Node *cur = it.ptr; // current Node*
    it++;
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    delete cur;
    return it;
}

// Cout function

template<typename T>
std::ostream& operator<<(std::ostream& os, List<T>& cont) {
    for(const auto& it : cont)
        os << it << ' ';
    return os << '\n';
}

//-----------------------------------------------
// ITERATORS MEMBERS
//-----------------------------------------------

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if ((unsigned long long)ptr % 2 == 1)
        throw std::out_of_range("incrementing end iterator");

    if (ptr->next == nullptr)
        ptr = (Node*)((unsigned long long)ptr + 1);
    else
        ptr = ptr->next;
    return *this; 
}


template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator old = *this;
    operator++(); 
    return old;   
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    if (!ptr->prev)
        throw std::out_of_range("Decrementing begin iterator");

    if ((unsigned long long)ptr % 2 == 1)
        ptr = (Node*)((unsigned long long)ptr - 1);
    else
        ptr = ptr->prev;
    return *this; 
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator old = *this; 
    operator--();  
    return old;    
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator+=(int rhs) {
    if (rhs < 0)
        for (int i = 0; i > rhs; i--)
            operator--();
    else
        for (int i = 0; i < rhs; i++)
            operator++();
    return *this;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator-=(int rhs) {
    (*this) += (-rhs);
    return *this;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const typename List<T>::Iterator& other) {
    if (this == &other)
        return *this;
    this->ptr = other->ptr;
    return *this;
}

template<typename T>
T& List<T>::Iterator::operator* () {
    if ((unsigned long long)ptr % 2 == 1)
        throw std::out_of_range("Dereferencing end iterator");
    return ptr->data;
}

template<typename T>
T& List<T>::Iterator::operator-> () {
    if ((unsigned long long)ptr % 2 == 1)
        throw std::out_of_range("Dereferencing end iterator");
    return ptr->data;
}

#endif // MY_LIST_H



