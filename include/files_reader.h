#ifndef AED_T2_FILES_READER_H
#define AED_T2_FILES_READER_H


#include <iostream>
#include <fstream>
#include <vector>
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
};

struct LineStops {
    list<string> stops;
};


ostream &operator<<(ostream &os, const Location &l);


ostream &operator<<(ostream &os, const Stop &l);


ostream &operator<<(ostream &os, const Line &l);


istream &operator>>(istream &is, Location &l);


istream &operator>>(istream &is, Stop &l);


istream &operator>>(istream &is, Line &l);

istream &operator>>(istream &is, LineStops &l);


vector<Stop> StopsReader(const string &path);

vector<Line> LinesReader(const string &path);


#endif //AED_T2_FILES_READER_H
