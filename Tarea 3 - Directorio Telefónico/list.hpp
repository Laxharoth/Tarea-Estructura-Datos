#ifndef LIST_HPP
#define LIST_HPP

#include <cstdio>

template <class T>
struct Node{
    T data{};
    Node<T> *next = nullptr;
    Node<T>();
    Node<T>(T data);
};

template <class T>
struct ListIterator{
    Node<T> *current;
    Node<T> *prev;
    ListIterator<T> next();
    ListIterator<T>();
    ListIterator<T>(Node<T> *current, Node<T> *prev);
    ListIterator<T>(Node<T> *current);
    bool operator==(const ListIterator<T> &lhs);
    bool operator!=(const ListIterator<T> &lhs);
    T &operator*();
    ~ListIterator<T>();
};

template <class T>
struct LinkedList{
    Node<T> *head;
    size_t size = 0;
    void insert(T value);
    void clear();
    T remove(ListIterator<T> removeIter);
    ListIterator<T> begin();
    ListIterator<T> end();
    LinkedList();
    ~LinkedList();
    private:
    Node<T> *tail;
};

#include "list.tcc"

#endif
