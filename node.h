#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template <class T>

class Node
{
private:
    T data;
    Node<T>* link;

public:
    Node();
    Node(T);
    void setData(T);
    T getData();

    template <class Type> friend class LinkedList;
    template <class Type> friend class Stack;
    template <class Type> friend class AdjacencyList;
    friend class Planner;
};

template <class T>
Node<T>::Node()
{
    link = nullptr;
}

template <class T>
Node<T>::Node(T elt)
{
    data = elt;
    link = nullptr;
}

template <class T>
void Node<T>::setData(T elt)
{
    data = elt;
}

template <class T>
T Node<T>::getData()
{
    return data;
}

#endif // NODE_H_INCLUDED
