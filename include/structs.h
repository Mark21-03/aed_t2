#ifndef AED_T2_STRUCTS_H
#define AED_T2_STRUCTS_H

#include <iostream>
#include <list>

using namespace std;


struct Location {
    double latitude, longitude;
};

struct Stop {
    string code, name, zone;
    Location location;
};

struct Line {
    string code, name;
};

struct LineStops {
    list<string> stops;
};


#endif //AED_T2_STRUCTS_H
