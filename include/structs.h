#ifndef AED_T2_STRUCTS_H
#define AED_T2_STRUCTS_H

#include <iostream>
#include <list>
#include <sstream>

using namespace std;


/**
 * A location is defined by its position : latitude & longitude
 */
struct Location {
    double latitude, longitude;
};

/**
 * A bus stop has a location and some information that defines it
 */
struct Stop {
    string code, name, zone;
    Location location;
};

/**
 * A bus line has a name and a code. It can be traversed in both ways
 */
struct Line {
    string code, name;

    string lineDirectionName(bool dir) const {

        //18 - PASSEIO ALEGRE - CARMO
        stringstream ss(name);

        string codeName, startName, endName;

        getline(ss, codeName, '-');
        getline(ss, startName, '-');
        getline(ss, endName, '-');

        if (dir)
            return codeName + "." + startName + "-" + endName;
        return codeName + "." + endName + "-" + startName;

    }
};

/**
 * A collection of stops of a specific bus line
 */
struct LineStops {
    list<string> stops;
};


#endif //AED_T2_STRUCTS_H
