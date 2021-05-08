#ifndef PLANNER_H_INCLUDED
#define PLANNER_H_INCLUDED

#include "linkedlist.h"
#include "adjacencylist.h"
#include "route.h"
#include "flightdetails.h"
#include "flightsortplan.h"
#include "vector.h"
#include "stack.h"
#include <fstream>

class Planner
{
private:
    std::ifstream inFlightDetails;

    int flightNo;
    Vector<Stack<Node<FlightDetails>*>> findRoutes(FlightSortPlan);
    bool isCityOnStack(Stack<Node<FlightDetails>*>, std::string);
    Vector<Route> transferRoutes(Vector<Stack<Node<FlightDetails>*>>);
    Vector<Route> sortRoutes(Vector<Route>, std::string);
    void outputRoute(Vector<Route>, FlightSortPlan);

public:
    //to change as private
    AdjacencyList<FlightDetails> flights;
    Planner();
    void readFlightDetails(std::string);
    void readFlightSortPlans();

};

#endif // PLANNER_H_INCLUDED
