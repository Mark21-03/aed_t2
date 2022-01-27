#ifndef AED_T2_MENUASKS_H
#define AED_T2_MENUASKS_H


#include <iostream>
#include <vector>
#include "structs.h"

using namespace std;


#define geoCQueijo {41.16861948613213, -8.6899475068589}
#define geoFeup {41.17838121987286, -8.599018100763733}
#define geoPassal {41.15203283630788, -8.49986876108789}
#define geoFcup {41.15223552642268, -8.636936732334394}
#define geoFrancelos {41.10191154587645, -8.659713734654174}
#define geoIkea {41.20962241758282, -8.688599177567802}
#define geoAliados {41.14843076280013, -8.610857716992687}
#define geoBomSucesso {41.15576823832895, -8.629961857769722}
#define geoPalBolsa {41.14073588624748, -8.615741317702945}
#define geoGaiaShopping {41.117352653497626, -8.621390956976255}
#define geoNorteShopping {41.17921590595752, -8.652310502100645}
#define geoCordoaria {41.14546314938763, -8.616957405759472}
#define geoAlfena {41.24468890867462, -8.52083368770199}
#define geoCampanha {41.14885301366697, -8.585581573539976}
#define geoSouto {41.136360363397294, -8.530595914787796}
#define geoStartNode 2488
#define geoEndNode 2489


string trimStr(istream &ios, string str) {
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}


bool emptyStream(istream &ios) {
    string bufferContent;
    getline(ios, bufferContent);
    trimStr(ios, bufferContent);
    if (bufferContent.empty())
        return true;
    return false;
}

bool menuConfirmationPrompt() {
    char confirm;

    cout << "\nConfirm? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        return true;
    else {
        cout << "Canceled. Press any key to continue...";
        cin.clear();
        cin.ignore(10000, '\n');
        getchar();
    }


    return false;
}


string lineDirectionName(const string &name, bool dir) {

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


int askStopRadius() {
    int stopRadius = 50;

    cout << "\n\nPlease provide the distance (in meters) you are\n"
            "willing to travel on foot between intermediate stops\n";
    cout << "\n > ";

    int n;
    if (cin >> n) {
        stopRadius = n;
        cout << "\nStop Radius was set to " << stopRadius << " m\n";
    } else {
        cout << "Invalid input!\n";
    }

    cin.clear();
    cin.ignore(10000, '\n');
    getchar();
    return stopRadius;
}


int askFootDistance() {
    int footDistance = 200;

    cout << "\n\nPlease provide the distance (in meters) you are\n"
            "willing to travel on foot to reach the destination\n";
    cout << "\n > ";

    int n;
    if (cin >> n) {
        footDistance = n;
        cout << "\nFoot distance was set to " << footDistance << " m\n";
    } else {
        cout << "Invalid input!\n";
    }

    cin.clear();
    cin.ignore(10000, '\n');
    getchar();
    return footDistance;
}

bool askUseMLines() {

    bool useMLines = true;


    char confirm;

    cout << "\nDo you want to include M lines (Y / N) ? ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        useMLines = true;
    else {
        useMLines = false;
    }

    cin.clear();
    cin.ignore(10000, '\n');
    cout << "\nInclude M lines was set to " << (useMLines ? "TRUE" : "FALSE") << endl;
    getchar();
    return useMLines;
}


void askDisableStop() {
    cout << "\naskDisableStop\n";
    getchar();
}

void askDisableLine() {
    cout << "\naskDisableLine\n";
    getchar();
}

bool processStoredCords(const string &input, Location &location) {

    Location temp = location;

    if (input == "CQUEIJO")
        location = geoCQueijo;

    else if (input == "FEUP")
        location = geoFeup;

    else if (input == "FCUP")
        location = geoFcup;

    else if (input == "PASSAL")
        location = geoPassal;

    else if (input == "IKEA")
        location = geoIkea;

    else if (input == "FRANCELOS")
        location = geoFrancelos;

    else if (input == "ALIADOS")
        location = geoAliados;

    else if (input == "BOMSUCESSO")
        location = geoBomSucesso;

    else if (input == "PBOLSA")
        location = geoPalBolsa;

    else if (input == "GSHOP")
        location = geoGaiaShopping;

    else if (input == "NSHOP")
        location = geoNorteShopping;

    else if (input == "CORDOARIA")
        location = geoCordoaria;

    else if (input == "ALFENA")
        location = geoAlfena;

    else if (input == "CAMPANHA")
        location = geoCampanha;

    else if (input == "SOUTO")
        location = geoSouto;

    return (temp.latitude != location.latitude && temp.longitude != location.longitude);

}


template<class Sortable>
int binarySearch(vector<Sortable> v, Sortable val) {
    int l = 0, r = v.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (v[m] == val) return m;
        if (v[m] < val) l = m + 1;
        else r = m - 1;
    }
    return -1;
}


bool validStop(const vector<string> &stopsCode, const string &stop) {

    int index = binarySearch(stopsCode, stop);

    return index != -1;
}

#endif //AED_T2_MENUASKS_H
