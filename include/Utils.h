#ifndef AED_T2_UTILS_H
#define AED_T2_UTILS_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <vector>

#include "structs.h"

using namespace std;

/**
 * Computes the geographic distance between two locations (in meters)
 * @param l1 first location
 * @param l2 second location
 * @return distance between first and second location
 */
static double distanceCalc(Location l1, Location l2) {

    static const double radians =  M_PI / 180.0;
    double lat1 = l1.latitude, lon1 = l1.longitude;
    double lat2 = l2.latitude, lon2 = l2.longitude;

    double dLat = (lat2 - lat1) * radians ;
    double dLon = (lon2 - lon1) * radians ;

    lat1 = (lat1) * radians;
    lat2 = (lat2) * radians;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}


#endif //AED_T2_UTILS_H
