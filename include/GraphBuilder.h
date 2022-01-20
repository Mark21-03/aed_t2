#ifndef AED_T2_GRAPHBUILDER_H
#define AED_T2_GRAPHBUILDER_H

#include "graph.h"
#include "files_reader.h"
#include "map"
#include "distanceCalc.h"
#include <climits>


class GraphBuilder {

private:

    void addNodes();

    void addEdges();

public:
    Graph graph;
    map<string, int> stopToIndex;
    map<int, string> indexToStop;

    Graph buildGraph() {
        graph = Graph(2487 + 2, true);
        addNodes();
        addEdges();
        return graph;
    }

    int nodeGeoDistance(int start, int end);

    static list<string> availableLines(const string &code);

    static bool file_exists(const string &name);
};


#endif //AED_T2_GRAPHBUILDER_H
