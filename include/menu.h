#ifndef AED_T2_MENU_H
#define AED_T2_MENU_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "files_reader.h"
#include "graph.h"
#include "GraphBuilder.h"
#include "InverseGraph.h"
#include "GraphInverseBuilder.h"



#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


using namespace std;


class Menu {

private:
    vector<string> stopsCode = StopsCodesReader("../dataset/stops.csv");

public:

    Location localStart, localEnd;
    string codeStart, codeEnd;
    int footDistance = 200;
    int stopRadius = 40;
    bool useMLines = true;


    enum STATE {
        location, criteria, close, settings
    };

    STATE locationMenu();

    STATE settingsMenu();

    STATE criteriaMenu() const;

    void start();

    static list<Graph::Edge> minStops(Graph &graph, int originIndex, int destinyIndex);

    static list<Graph::Edge> minDistance(Graph &graph, int originIndex, int destinyIndex);

    static list<Graph::Edge> minZones(Graph &graph, int originIndex, int destinyIndex);

    static list<InverseGraph::Edge> minSwaps(InverseGraph &graph, int originIndex, int destinyIndex);

    void askLocationStops();

    void askLocationCords();

    void showGeneratedPath(int pathCriteria) const;

    static void beautifulPrintGeo(Graph graph, GraphBuilder model, list<Graph::Edge> path); // TODO: PASS BY REFERENCE

    static void fullLinePrint(Graph graph, GraphBuilder model, vector<pair<Line, bool>> lines, const list<int> &path);

    static void beautifulPrintStops(Graph &graph, GraphBuilder &model, list<Graph::Edge> &path);

    static void
    beautifulPrintStopsInverse(InverseGraph &graph, GraphInverseBuilder &model, list<InverseGraph::Edge> &path);

};



#endif