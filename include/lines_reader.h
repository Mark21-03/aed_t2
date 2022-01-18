#ifndef AED_T2_LINES_READER_H
#define AED_T2_LINES_READER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


struct Line {
public:
    string code, name;
};


vector<Line> reader(const string &path);

ostream &operator<<(ostream &os, const Line &l);

istream &operator>>(istream &is, Line &l);

#endif //AED_T2_LINES_READER_H
