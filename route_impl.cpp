#include "route.h"
#include <iomanip>
#include <fstream>

using namespace std;

Route::Route()
{
    totalFare = 0;
    totalDuration = 0;
}

void Route::addCity(string city)
{
    cities.pushBack(city);
}

void Route::setTotalFare(double tf)
{
    if(tf>0)
        totalFare = tf;
    else
        cerr << "Invalid total fare " << endl;
}

void Route::setTotalDuration(double td)
{
    if(td>0)
        totalDuration = td;
    else
        cerr << "Invalid total duration " << endl;
}

double Route::getTotalFare()
{
    return totalFare;
}

double Route::getTotalDuration()
{
    return totalDuration;
}

void Route::display()
{
    for(int i=0; i<cities.getSize()-1; i++)
        cout << cities[i] << "->";
    cout << cities[cities.getSize()-1] << ". Fare: Rs. " << fixed << setprecision(2) << totalFare << " Duration: " << fixed << setprecision(0) << totalDuration << " minutes";
}

