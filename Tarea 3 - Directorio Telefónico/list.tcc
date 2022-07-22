#include "list.hpp"

template<class T>
void LinkedList<T>::insert(T value){
    Node<T> *newNode = new Node<T>{value};
    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
        this->size = 1;
        return;
    }
    this->tail->next = newNode;
    this->tail = newNode;
    this->size++;
};
template<class T>
void LinkedList<T>::clear(){
    tail = nullptr;
    while(this->head != nullptr){
        Node<T> *tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
    this->size = 0;
}
template<class T>
LinkedList<T>::~LinkedList(){
        this->clear();
}
template<class T>
LinkedList<T>::LinkedList():head(nullptr),size(0){};

template<class T>
ListIterator<T> LinkedList<T>::begin(){
    return ListIterator<T>(this->head);
}
template<class T>
ListIterator<T> LinkedList<T>::end(){
    return ListIterator<T>();
}
template<class T>
T LinkedList<T>::remove(ListIterator<T> removeIter){
    if(removeIter.current == this->head){
        this->head = this->head->next;
    }
    else{
        removeIter.prev->next = removeIter.current->next;
    }
    if(removeIter.current == this->tail){
        this->tail = removeIter.prev;
    }
    T data = removeIter.current->data;
    delete removeIter.current;
    removeIter.prev = nullptr;
    removeIter.current = nullptr;
    return data;
}
//List Iterator
template <class T>
bool ListIterator<T>::operator==(const ListIterator<T> &lhs){
    return lhs.current == current;
}
template <class T>
bool ListIterator<T>::operator!=(const ListIterator<T> &lhs){
    return lhs.current != current;
}
template <class T>
T &ListIterator<T>::operator*(){
    return current->data;
}
template <class T>
ListIterator<T> ListIterator<T>::next(){
    return ListIterator<T>(current->next, current);
}
template <class T>
ListIterator<T>::ListIterator():current(nullptr),prev(nullptr){}
template <class T>
ListIterator<T>::ListIterator(Node<T> *current, Node<T> *prev):current(current), prev(prev) {};
template <class T>
ListIterator<T>::ListIterator(Node<T> *current):current(current), prev(nullptr) {};
template <class T>
ListIterator<T>::~ListIterator(){};
template <class T>
Node<T>::Node(){};
template <class T>
Node<T>::Node(T data) : data(data), next(nullptr) {};