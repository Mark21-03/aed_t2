#ifndef AED_T2_FILES_READER_H
#define AED_T2_FILES_READER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include "structs.h"

bool file_exists(const string &name);

ostream &operator<<(ostream &os, const Location &l);

ostream &operator<<(ostream &os, const Stop &l);

ostream &operator<<(ostream &os, const Line &l);

istream &operator>>(istream &is, Location &l);

istream &operator>>(istream &is, Stop &l);

istream &operator>>(istream &is, Line &l);

istream &operator>>(istream &is, LineStops &l);

vector<Stop> StopsReader(const string &path);

vector<Line> LinesReader(const string &path);

vector<string> StopsCodesReader(const string &path);

list<string> availableLines(const string &code, bool includeM_lines);

#endif //AED_T2_FILES_READER_H
