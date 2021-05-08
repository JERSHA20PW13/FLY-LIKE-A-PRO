#include "flightsortplan.h"
#include <iostream>

using namespace std;

FlightSortPlan::FlightSortPlan()
{
    origin=destination=sortType="";
}

FlightSortPlan::FlightSortPlan(string o, string d, string st)
{
    origin =o;
    destination= d;
    sortType = st;
}

string FlightSortPlan::getOrigin()
{
    return origin;
}

string FlightSortPlan::getDestination()
{
    return destination;
}

string FlightSortPlan::getSortType()
{
    return sortType;
}

void FlightSortPlan::setOrigin(string o)
{
    origin = o;
}

void FlightSortPlan::setDestination(string d)
{
    destination = d;
}

void FlightSortPlan::setSortType(string st)
{
    if(st=="F" || st=="D")
        sortType= st;
    else
        cerr << "Error: Invalid sort type\n";
}
