#ifndef AED_T2_STRUCTS_H
#define AED_T2_STRUCTS_H

#include <iostream>
#include <list>
#include <sstream>

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

    string lineDirectionName(bool dir) {

        //18 - PASSEIO ALEGRE - CARMO
        stringstream ss(name);

        string codeName, startName, endName;

        getline(ss, codeName, '-');
        getline(ss, startName, '-');
        getline(ss, endName, '-');

        if (!dir)
            return codeName + ". " + startName + " - " + endName;
        return codeName + ". " + endName + " - " + startName;

    }
};

struct LineStops {
    list<string> stops;
};

struct WeightCriteria {
    int distance, zones, changes;
};


#endif //AED_T2_STRUCTS_H
