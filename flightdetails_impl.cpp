#include <iostream>
#include "flightdetails.h"
#include <string>

using namespace std;

FlightDetails::FlightDetails()
{
    origin=destination="";
    fare=duration=1;
}

FlightDetails::FlightDetails(std::string ori, std::string des, double f, double d)
{
    origin= ori;
    destination= des;
    fare = f;
    duration = d;
}

FlightDetails::FlightDetails(const FlightDetails &toCopy)
{
    *this = toCopy;
}

std::string FlightDetails::getOrigin()
{
    return origin;
}

std::string FlightDetails::getDestination()
{
    return destination;
}

double FlightDetails::getFare()
{
    return fare;
}

double FlightDetails::getDuration()
{
    return duration;
}

void FlightDetails:: setOrigin(std::string ori)
{
    origin = ori;
}

void FlightDetails:: setDestination(std::string des)
{
    destination = des;
}

void FlightDetails:: setFare(double f)
{
    fare = f;
}

void FlightDetails:: setDuration(double d)
{
    duration = d;
}

FlightDetails& FlightDetails::operator = (const FlightDetails& toCopy)
{
    origin = toCopy.origin;
    destination = toCopy.destination;
    fare = toCopy.fare;
    duration = toCopy.duration;
    return *this;
}

FlightDetails::~FlightDetails()
{

}
