#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "node.h"
#include "flightdetails.h"
#include <iostream>

template <class T>
class LinkedList
{
private:
    Node<T>* start;

public:
    LinkedList();
    void ins_beg(T);
    void ins_end(T);
    T del_beg();
    void display();

    template<class Type> friend class AdjacencyList;
    template<class Type> friend class Stack;
    friend class Planner;
};

template <class T>
LinkedList<T> :: LinkedList()
{
    start = nullptr;
}

template <class T>
void LinkedList<T> :: ins_beg(T elt)
{
    Node<T> *N = new Node<T>;
    N->data = elt;
    N->link = start;
    start = N;
}

template <class T>
void LinkedList<T> :: ins_end(T elt)
{
    Node<T> *ptr = start;
    if(start == nullptr)
        start = new Node<T> (elt);
    else
    {
        while(ptr->link != nullptr)
            ptr = ptr->link;
        ptr->link = new Node<T> (elt);
    }
}

template <class T>
T LinkedList<T> :: del_beg()
{
    T temp = start->data;
    start = start->link;
    return temp;
}

template <class T>
void LinkedList<T>::display()
{
    Node<T> *ptr = start;
    while(ptr != nullptr)
    {
        std::cout << ptr->data.getDestination() << " ";
        ptr = ptr->link;
    }
}

#endif // LINKEDLIST_H_INCLUDED
