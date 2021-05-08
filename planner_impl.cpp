#include "planner.h"
#include "adjacencylist.h"
#include "route.h"
#include "flightdetails.h"
#include "flightsortplan.h"
#include "linkedlist.h"
#include "vector.h"
#include "stack.h"
#include "node.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

Planner::Planner()
{
    flightNo = 1;
}

void Planner::readFlightDetails(string file)
{
    inFlightDetails.open(file);
    if(!inFlightDetails)
    {
        cerr << "Flight Details file not opened correctly";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(inFlightDetails,line);
    int flightsAvailable = stoi(line);

    string origin, destination;
    double fare, duration;

    for(int i=0; i<flightsAvailable; i++)
    {
        getline(inFlightDetails,origin,'|');
        getline(inFlightDetails,destination,'|');
        getline(inFlightDetails,line,'|');
        fare = stod(line);
        getline(inFlightDetails,line,'\n');
        duration = stod(line);

        FlightDetails FwdData(origin,destination,fare,duration);
        flights.ins(FwdData);
        FlightDetails BwdData(destination,origin,fare,duration);
        flights.ins(BwdData);
    }
    inFlightDetails.close();
}

void Planner::readFlightSortPlans()
{
    int choice = 1;
    string origin,destination,sortType;
    while(choice)
    {
        cout << "................................................................................................................\n................................................................................................................\n.%%%%%%..%%......%%..%%..........%%......%%%%%%..%%..%%..%%%%%%...........%%%%...........%%%%%...%%%%%....%%%%..\n.%%......%%.......%%%%...........%%........%%....%%.%%...%%..............%%..%%..........%%..%%..%%..%%..%%..%%.\n.%%%%....%%........%%............%%........%%....%%%%....%%%%............%%%%%%..........%%%%%...%%%%%...%%..%%.\n.%%......%%........%%............%%........%%....%%.%%...%%..............%%..%%..........%%......%%..%%..%%..%%.\n.%%......%%%%%%....%%............%%%%%%..%%%%%%..%%..%%..%%%%%%..........%%..%%..........%%......%%..%%...%%%%..\n................................................................................................................\n\n\n\n";
        cout << "ENTER ORIGIN : " ;
        cin >> origin;
        cout << "ENTER DESTINATION : ";
        cin >> destination;
        cout << "F - FARE, D - DURATION" << endl;
        do
        {
            cout << "ENTER SORT TYPE [F/D] : ";
            cin >> sortType;
        }while(sortType != "F" && sortType != "D");

        FlightSortPlan fsp(origin,destination,sortType);

        Vector<Stack<Node<FlightDetails>*>> routes = findRoutes(fsp);

        Vector<Route> routeVector = transferRoutes(routes);

        routeVector = sortRoutes(routeVector,sortType);

        outputRoute(routeVector,fsp);

        cout << endl << "Got any more trips (0-no, 1-yes) ? ";
        cin >> choice;
        system("CLS");
    }
}

Vector<Stack<Node<FlightDetails>*>> Planner::findRoutes(FlightSortPlan plan)
{
    Vector<Stack<Node<FlightDetails>*>> routes;

    Stack<LinkedList<FlightDetails>> rStack;

    rStack.push(flights.getOriginList(plan.getOrigin()));

    Stack<Node<FlightDetails>*> ptrStack;

    Node<FlightDetails>* ptr = rStack.getTop().start;

    do
    {
        if(ptr==nullptr)
        {
            bool finish = false;

            while(ptr==nullptr)
            {
                rStack.pop();

                if(rStack.isEmpty())
                {
                    finish = true;
                    break;
                }

                ptr = ptrStack.pop();
                ptr = ptr->link;

                while(ptr != nullptr && isCityOnStack(ptrStack, ptr->data.getDestination()))
                {
                    ptr = ptr->link;
                }
            }
            if(finish)
                break;
        }


        if(ptr->data.getDestination()==plan.getDestination())
        {
            ptrStack.push(ptr);

            routes.pushBack(ptrStack);

            ptrStack.pop();

            ptr = ptr->link;

            while(ptr != nullptr && isCityOnStack(ptrStack,ptr->data.getDestination()))
            {
                ptr = ptr->link;
            }
        }

        if(ptr!=nullptr)
        {
            ptrStack.push(ptr);

            rStack.push(flights.getOriginList(ptr->data.getDestination()));

            ptr = rStack.getTop().start;

            while(ptr != nullptr && isCityOnStack(ptrStack,ptr->data.getDestination()))
            {
                ptr = ptr->link;
            }
        }

    }while(1);
    return routes;
}

Vector<Route> Planner::transferRoutes(Vector<Stack<Node<FlightDetails>*>> routes)
{
    Stack<FlightDetails> fStack;

    Vector<Route> routeVector;

    for(int i=0; i<routes.getSize(); i++)
    {
        while(!routes[i].isEmpty())
        {
            Node<FlightDetails>* ptr = routes[i].pop();
            fStack.push(ptr->data);
        }

        Route flightRoute;
        int fareTotal = 0;
        int durationTotal = 0;

        FlightDetails f = fStack.pop();
        flightRoute.addCity(f.getOrigin());
        flightRoute.addCity(f.getDestination());
        fareTotal += f.getFare();
        durationTotal += f.getDuration();

        while(!fStack.isEmpty())
        {
            f = fStack.pop();
            flightRoute.addCity(f.getDestination());
            fareTotal += f.getFare();
            durationTotal += f.getDuration();
        }
        flightRoute.setTotalFare(fareTotal);
        flightRoute.setTotalDuration(durationTotal);

        routeVector.pushBack(flightRoute);
    }
    return routeVector;
}

Vector<Route> Planner::sortRoutes(Vector<Route> routeVector, string type)
{
    if(type == "D")
    {
        for(int i=0; i<routeVector.getSize(); i++)
        {
            for(int j=i+1; j<routeVector.getSize(); j++)
            {
                if(routeVector[i].getTotalDuration()>routeVector[j].getTotalDuration())
                {
                     Route temp = routeVector[i];
                     routeVector[i] = routeVector[j];
                     routeVector[j] = temp;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<routeVector.getSize(); i++)
        {
            for(int j=i+1; j<routeVector.getSize(); j++)
            {
                if(routeVector[i].getTotalFare()>routeVector[j].getTotalFare())
                {
                     Route temp = routeVector[i];
                     routeVector[i] = routeVector[j];
                     routeVector[j] = temp;
                }
            }
        }
    }

    return routeVector;
}

bool Planner::isCityOnStack(Stack<Node<FlightDetails>*> s, string city)
{
    Node<FlightDetails>* top = nullptr;

    while(!s.isEmpty())
    {
        top = s.pop();
        if(top->data.getOrigin()==city || top->data.getDestination()==city)
            return true;
    }
    return false;
}

void Planner::outputRoute(Vector<Route> routeVector,FlightSortPlan fsp)
{
    cout << endl;
    cout << "Flight " << flightNo << ": " << fsp.getOrigin() << ", " << fsp.getDestination() << endl;

    int np;
    cout << "How many paths needed ? : ";
    cin >> np;
    cout << endl;
    for(int i=0; i<np && i<routeVector.getSize(); i++)
    {
        if(i<9)
        {
            cout << "Path number : " << i+1 << "\t\t";
            routeVector[i].display();
            cout << endl;
        }
        else
        {
            cout << "Path number : " << i+1 << "\t";
            routeVector[i].display();
            cout << endl;
        }
    }

    if(routeVector.getSize()==0)
        cout << "No routes found -_- " << endl;
    else
    {
        if(fsp.getSortType() == "D")
        {
            cout << "(Sorted by duration)" << endl;
        }
        else
        {
            cout << "(Sorted by fare)" << endl;
        }
    }

    flightNo++;
}
