#include "../include/files_reader.h"


ostream &operator<<(ostream &os, const Location &l) {
    os << l.latitude << " " << l.longitude;
    return os;
}


ostream &operator<<(ostream &os, const Stop &l) {
    os << l.code << " " << l.name << " " << l.zone << " -> " << l.location;
    return os;
}

ostream &operator<<(ostream &os, const Line &l) {
    os << l.code << " " << l.name << " ";
    return os;
}


istream &operator>>(istream &is, Location &l) {

    double latitude, longitude;
    char sep;

    is >> latitude >> sep;

    if (sep == ',') {
        is >> longitude;
        l = {latitude, longitude};
    }

    return is;
}


istream &operator>>(istream &is, Stop &l) {


    //Code,Name,Zone,Latitude,Longitude
    //1AL2,AV.ALIADOS,PRT1,41.14954216,-8.610023615
    string code, name, line, zone;
    Location location{};

    getline(is, code, ',');
    getline(is, name, ',');
    getline(is, zone, ',');
    is >> location;


    l = {code, name, zone, location};

    return is;
}


istream &operator>>(istream &is, Line &l) {

    // 106,ZF - VALADARES (ESTAÇÃO)-FRANCELOS
    string code, name, line;
    getline(is, code, ',');
    getline(is, name);

    l = {code, name};

    return is;
}

istream &operator>>(istream &is, LineStops &l) {

    int n;

    is >> n;

    string s;

    for (int i = 0; i < n; ++i) {
        is >> s;
        l.stops.push_back(s);
    }

    return is;
}


vector<Stop> StopsReader(const string &path) {

    // where file contents are stored
    vector<Stop> rows;

    //variables to retrieve from files
    fstream file(path, ios::in);

    Stop line;
    string aux;

    getline(file, aux);
    while (getline(file, aux)) {
        stringstream ss(aux);
        ss >> line;
        rows.push_back(line);
    }

    return rows;
}


vector<Line> LinesReader(const string &path) {

    vector<Line> rows;
    fstream file(path, ios::in);

    Line line;
    string aux;

    getline(file, aux);
    while (getline(file, aux)) {
        stringstream ss(aux);
        ss >> line;
        rows.push_back(line);
    }

    return rows;
}

vector<string> StopsCodesReader(const string &path) {

    vector<string> rows;
    fstream file(path, ios::in);

    Line line;
    string aux;

    getline(file, aux);
    while (getline(file, aux)) {
        stringstream ss(aux);
        ss >> line;
        rows.push_back(line.code);
    }

    return rows;
}





