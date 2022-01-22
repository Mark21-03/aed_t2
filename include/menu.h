#ifndef AED_T2_MENU_H
#define AED_T2_MENU_H


#include <iostream>
#include <vector>
#include <string>
#include "files_reader.h"
#include "graph.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


#define geoStartNode 2488
#define geoEndNode 2489

using namespace std;


class Menu {

private:

    Location localStart, localEnd;
    string codeStart, codeEnd;
    int footDistance = 500;
    bool useMLines = true;


    enum STATE {
        location, criteria, close
    };

    static bool menuConfirmationPrompt();


public:

    STATE locationMenu();

    STATE criteriaMenu();

    void start();

    static list<int> minStops(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    static list<int> minDistance(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    static list<int> minZones(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    static list<int> minSwaps(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    void locationStops();

    void locationCords();

    void settingsMenu();

    void resetMenuVars();

    void showGeneratedPath(int pathCriteria);

    void askFootDistance();

    void askUseMLines();
};

string trimStr(istream &ios, string str);

bool emptyStream(istream &ios);

#endif