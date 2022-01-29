#ifndef AED_T2_GRAPHINVERSEBUILDER_H
#define AED_T2_GRAPHINVERSEBUILDER_H


#include "graph.h"
#include "InverseGraph.h"
#include <map>

class GraphInverseBuilder {
private:

    bool includeM_lines;
    set<string> disabledLinesCodes;
    set<string> disabledStopsCodes;

    GraphInverseBuilder &addNodes();

    GraphInverseBuilder &addEdges();

public:
    GraphInverseBuilder &addWalkingEdges(int radius);


    vector<int> nodesInReach(int i, int radius) {

        vector<int> v;
        for (int d = onlyStopsFirstIndex; d <= len; d++) {
            if ((int) distanceCalc(graph.nodeLocation[graph.getNode(d).stop.first],
                                   graph.nodeLocation[graph.getNode(i).stop.first]) <= radius) {
                v.push_back(d);
            }

        }
        return v;
    }


    InverseGraph graph;
    map<pair<string, string>, int> nodeToIndex;
    map<int, pair<string, string>> indexToNode;
    int len;
    int onlyStopsFirstIndex;

    InverseGraph &buildGraph(bool includeMLines = true, int footDistance = -1, const set<string> &disabledLines = {},
                             const set<string> &disabledStops = {}) {
        graph = InverseGraph(9000, true); //TODO RICARDO VER O NUMERO DE NOS DE MODO A NAO TER MUITOS EXTRA DESNECESSARIOS
        this->includeM_lines = includeMLines;
        this->disabledLinesCodes = disabledLines;
        this->disabledStopsCodes = disabledStops;
        addNodes();
        addEdges();
        if (footDistance != -1)
            addWalkingEdges(footDistance);
        return graph;
    }

    void addGeoStartEndNode(Location start, Location end, int radius) {

        Stop stop = {};
        string s = "";
        string startStop = "CURRENT POINT";
        string endStop = "END POINT";
        graph.addNode(len + 1, startStop, s);
        graph.nodeLocation.insert(pair<string, Location>(startStop, start));
        graph.addNode(len + 2, endStop, s);
        graph.nodeLocation.insert(pair<string, Location>(endStop, end));


        vector<int> nodesStart = nodesInReach(len + 1, radius);
        vector<int> nodesEnd = nodesInReach(len + 2, radius);

        for (int i: nodesStart) {
            graph.addEdge(len + 1, i, false, 1);
        }

        for (int i: nodesEnd) {
            graph.addEdge(i, len + 2, true, 1);
        }

    }

};


#endif //AED_T2_GRAPHINVERSEBUILDER_H
