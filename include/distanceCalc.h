#ifndef AED_T2_DISTANCECALC_H
#define AED_T2_DISTANCECALC_H

#include <cmath>

#include "structs.h"

using namespace std;

static double distanceCalc(Location l1, Location l2) {

    double lat1 = l1.latitude, lon1 = l1.longitude;
    double lat2 = l2.latitude, lon2 = l2.longitude;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}


#endif //AED_T2_DISTANCECALC_H
