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

    InverseGraph graph;
    map<pair<string, string>, int> nodeToIndex;
    map<int, pair<string, string>> indexToNode;
    int len;

    InverseGraph buildGraph(bool includeMLines = true, int footDistance = -1, const set<string> &disabledLines = {},
                            const set<string> &disabledStops = {}) {
        graph = InverseGraph(9000, true);
        this->includeM_lines = includeMLines;
        this->disabledLinesCodes = disabledLines;
        this->disabledStopsCodes = disabledStops;
        addNodes();
        addEdges();
        if (footDistance != -1)
            addWalkingEdges(footDistance);
        return graph;
    }

};


#endif //AED_T2_GRAPHINVERSEBUILDER_H
