#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include "vector.h"
#include <string>
#include <fstream>

class Route
{
private:
    Vector<std::string> cities;
    double totalFare;
    double totalDuration;

public:
    Route();
    void addCity(std::string);
    void setTotalFare(double);
    void setTotalDuration(double);
    double getTotalFare();
    double getTotalDuration();
    void display();
};

#endif // ROUTE_H_INCLUDED
