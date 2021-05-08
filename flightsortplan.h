#ifndef FLIGHTSORTPLAN_H_INCLUDED
#define FLIGHTSORTPLAN_H_INCLUDED

#include <string>

class FlightSortPlan
{
private:
    std::string origin;
    std::string destination;
    std::string sortType;

public:
    FlightSortPlan();
    FlightSortPlan(std::string, std::string, std::string);

    std::string getOrigin();
    std::string getDestination();
    std::string getSortType();

    void setOrigin(std::string);
    void setDestination(std::string);
    void setSortType(std::string);
};

#endif // FLIGHTSORTPLAN_H_INCLUDED
