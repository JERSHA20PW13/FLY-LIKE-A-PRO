#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "linkedlist.h"
#include "node.h"
#include "flightdetails.h"

template <class T>

class Stack
{
private:
    LinkedList<T> Llist;
    T top;

public:
    Stack();
    bool isEmpty();
    T getTop();
    void push(T);
    T pop();
};

template <class T>
Stack<T>::Stack()
{

}

template <class T>
bool Stack<T> ::isEmpty()
{
    if (Llist.start== nullptr)
        return true;
    else
        return false;
}

template <class T>
T Stack<T>::getTop()
{
    return top;
}

template <class T>
void Stack<T>::push(T elt)
{
    Llist.ins_beg(elt);
    top = elt;
}

template <class T>
T Stack<T>::pop()
{
    T elt;
    if(!isEmpty())
    {
        elt = Llist.del_beg();

        if(Llist.start != nullptr)
        {
            top = Llist.start->data;
        }
        return elt;
    }
    else
    {
        std::cout<< "Error: Stack underflow\n";
        return elt;
    }
}

#endif // STACK_H_INCLUDED
