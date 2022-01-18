#include "../include/lines_reader.h"

ostream &operator<<(ostream &os, const Line &l) {
    os << l.code1 << " " << l.code2 << " " << l.name << " ";
    return os;
}


istream &operator>>(istream &is, Line &l) {

    // 106,ZF - VALADARES (ESTAÇÃO)-FRANCELOS
    string code1, code2, name, line;
    getline(is, code1, ',');
    getline(is, code2, '-');
    getline(is, name);

    l.code1 = code1;
    l.code2 = code2;
    l.name = name;

    return is;
}


vector<Line> reader(const string &path) {

    // where file contents are stored
    vector<Line> rows;

    //variables to retrieve from files
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





