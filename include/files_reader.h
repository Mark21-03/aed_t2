#ifndef AED_T2_FILES_READER_H
#define AED_T2_FILES_READER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


struct Location {
public:
    double latitude, longitude;
};

struct Stop {
public:
    string code, name, zone;
    Location location;
};

struct Line {
public:
    string code, name;
};


ostream &operator<<(ostream &os, const Location &l);


ostream &operator<<(ostream &os, const Stop &l);


ostream &operator<<(ostream &os, const Line &l);


istream &operator>>(istream &is, Location &l);


istream &operator>>(istream &is, Stop &l);


istream &operator>>(istream &is, Line &l);


vector<Stop> StopsReader(const string &path);

vector<Line> LinesReader(const string &path);


#endif //AED_T2_FILES_READER_H
