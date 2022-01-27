#ifndef AED_T2_GRAPHBUILDER_H
#define AED_T2_GRAPHBUILDER_H

#include "graph.h"
#include "files_reader.h"
#include "map"
#include "Utils.h"
#include <climits>


class GraphBuilder {

private:

    bool includeM_lines;

    GraphBuilder &addNodes();

    GraphBuilder &addEdges();


public:
    GraphBuilder &addWalkingEdges(int radius);

    Graph graph;
    map<string, int> stopToIndex;
    map<int, string> indexToStop;

    Graph buildGraph(bool includeMLines = true, int footDistance = -1) {
        graph = Graph(2487 + 2, true);
        this->includeM_lines = includeMLines;
        addNodes();
        addEdges();
        if (footDistance != -1)
            addWalkingEdges(footDistance);
        return graph;
    }

    int nodeGeoDistance(int start, int end);

    const Graph &getGraph() const;
};


#endif //AED_T2_GRAPHBUILDER_H
