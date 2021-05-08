#ifndef FLIGHTDETAILS_H_INCLUDED
#define FLIGHTDETAILS_H_INCLUDED

#include <string>

class FlightDetails
{
private:
    std::string origin;
    std::string destination;
    double fare;
    double duration;

public:
    FlightDetails();
    FlightDetails(std::string, std::string, double, double);
    FlightDetails(const FlightDetails&);
    FlightDetails& operator =(const FlightDetails &);

    std::string getOrigin();
    std::string getDestination();
    double getFare();
    double getDuration();

    void setOrigin(std::string);
    void setDestination(std::string);
    void setFare(double);
    void setDuration(double);

    ~FlightDetails();
};

#endif // FLIGHTDETAILS_H_INCLUDED
