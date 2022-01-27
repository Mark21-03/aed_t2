//
// Created by ricar on 27/01/2022.
//

#ifndef AED_T2_GRAPHINVERSEBUILDER_H
#define AED_T2_GRAPHINVERSEBUILDER_H


#include "graph.h"
#include "InverseGraph.h"
#include <map>

class GraphInverseBuilder {
private:

    bool includeM_lines;

    GraphInverseBuilder& addNodes();

    GraphInverseBuilder& addEdges();


public:
    GraphInverseBuilder& addWalkingEdges(int radius);

    InverseGraph graph;
    map<pair<string,string>, int> nodeToIndex;
    map<int, pair<string,string>> indexToNode;
    int len;

    InverseGraph buildGraph(bool includeMLines = true, int footDistance = -1) {
        graph = InverseGraph(9000, true);
        this->includeM_lines = includeMLines;
        addNodes();
        addEdges();
        if (footDistance!=-1)
            addWalkingEdges(footDistance);
        return graph;
    }

    static bool file_exists(const string &name);

    list<string> availableLines(const string &code) const;

    string findANodeLine();

    InverseGraph &getGraph();
};


#endif //AED_T2_GRAPHINVERSEBUILDER_H
