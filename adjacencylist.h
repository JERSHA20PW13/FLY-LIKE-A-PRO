#ifndef ADJACENCYLIST_H_INCLUDED
#define ADJACENCYLIST_H_INCLUDED

#include "linkedlist.h"
#include "node.h"
#include "flightdetails.h"

template <class T>
class AdjacencyList
{
private:
    LinkedList<LinkedList<T>> Alist;

public:
    AdjacencyList();
    void ins(FlightDetails);
    LinkedList<T> getOriginList(std::string);
    void display();

    //to remove
    friend class Planner;
};

template <class T>
AdjacencyList<T>::AdjacencyList()
{

}

template <class T>
void AdjacencyList<T>::ins(FlightDetails flight)
{
    Node<LinkedList<T>>* ptr = Alist.start;

    if(Alist.start==nullptr)
    {
        LinkedList<FlightDetails> temp;
        temp.ins_end(flight);
        Alist.ins_end(temp);
    }

    else
    {
        while(ptr != nullptr)
        {
            if(ptr->data.start->data.getOrigin() == flight.getOrigin())
            {
                ptr->data.ins_end(flight);
                break;
            }
            ptr = ptr->link;
        }

        if(ptr == nullptr)
        {
            LinkedList<FlightDetails> temp;
            temp.ins_end(flight);
            Alist.ins_end(temp);
        }
    }
}

template <class T>
LinkedList<T> AdjacencyList<T>:: getOriginList(std::string city)
{
    Node<LinkedList<T>> *ptr = Alist.start;
    while(ptr != nullptr)
    {
        if(ptr->data.start->data.getOrigin() == city)
        {
            return ptr->data;
        }
        ptr = ptr->link;
    }

    if(ptr == nullptr)
    {
        LinkedList<FlightDetails> dummy;
        return dummy;
    }
}

template <class T>
void AdjacencyList<T>::display()
{
    Node<LinkedList<FlightDetails>> *ptr = Alist.start;
    while(ptr != nullptr)
    {
        std::cout << ptr->data.start->data.getOrigin() << " - ";
        ptr->data.display();
        std::cout << "\n";
        ptr = ptr->link;
    }
}

#endif // ADJACENCYLIST_H_INCLUDED
