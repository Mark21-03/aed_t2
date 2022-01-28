#ifndef AED_T2_GRAPHBUILDER_H
#define AED_T2_GRAPHBUILDER_H

#include "graph.h"
#include "files_reader.h"
#include "map"
#include "Utils.h"
#include <climits>
#include<set>

/**
 * Creates a graph meeting certain criteria
 */
class GraphBuilder {

private:

    bool includeM_lines;
    set<string> disabledLinesCodes;
    set<string> disabledStopsCodes;

    /**
     * Adds the nodes to the graph being built
     * @return returns reference to the self object
     */
    GraphBuilder &addNodes();

    /**
     * Adds the edges to the graph being built
     * @return returns reference to the self object
     */
    GraphBuilder &addEdges();


public:
    /**
     * Adds the walking edges between near bus stops
     * making them connected if they are inside a given radius
     * @param radius radius to consider the connection of bus stops
     * @return returns reference to the self object
     */
    GraphBuilder &addWalkingEdges(int radius);

    Graph graph;
    map<string, int> stopToIndex;
    map<int, string> indexToStop;

    /**
     * Creates a graph with given criteria
     * @param includeMLines boolean saying if M bus lines should be added
     * @param footDistance tells the distance the user is willing to travel to reach its destination
     * @param disabledLines set of all disabled bus lines that shouldn't be in the graph
     * @param disabledStops set of all disabled bus stops that shouldn't be in the graph
     * @return
     */
    Graph& buildGraph(bool includeMLines = true, int footDistance = -1, const set<string> &disabledLines = {},
                     const set<string> &disabledStops = {}) {
        graph = Graph(2487 + 2, true);
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


#endif //AED_T2_GRAPHBUILDER_H