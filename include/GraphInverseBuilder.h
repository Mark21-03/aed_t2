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

    /**
     * Adds the nodes to the graph being built
     * @return reference to the self object
     */
    GraphInverseBuilder &addNodes();

    /**
     * Adds the edges to the graph being built
     * @return reference to the self object
     */
    GraphInverseBuilder &addEdges();

public:

    /**
     * Adds the edges of type walking for the nodes closer than a given radius
     * @param radius distance between nodes to consider
     * @return reference to the self object
     */
    GraphInverseBuilder &addWalkingEdges(int radius);


    /**
     * Returns a list of the nodes' indexes in reach of a given node's radius
     * @param i node index to search neighbors in radius reach
     * @param radius distance to search for neighbors
     * @return
     */
    inline vector<int> nodesInReach(int i, int radius) {


        vector<int> v;
        auto l = graph.nodeLocation[graph.getNode(i).stop.first];
        for (int d = onlyStopsFirstIndex; d <= len; d++) {
            if ((int) distanceCalc(graph.nodeLocation[graph.getNode(d).stop.first],
                                   l) <= radius) {
                v.push_back(d);
            }

        }
        return v;
    }


    InverseGraph graph;
    map<pair<string, string>, int> nodeToIndex;
    map<int, pair<string, string>> indexToNode;
    map<string, string> stopNames;
    int len;
    int onlyStopsFirstIndex;

    /**
     * Builds the graph with given criteria
     * @param includeMLines boolean if M bus lines should be in the graph
     * @param footDistance distance the user wants to walk to the first stop and to reach the destiny
     * @param disabledLines set of bus lines that shouldn't be in the graph
     * @param disabledStops set of bus stops that shouldn't be in the graph
     * @return
     */
    InverseGraph &buildGraph(bool includeMLines = true, int footDistance = -1, const set<string> &disabledLines = {},
                             const set<string> &disabledStops = {}) {
        graph = InverseGraph(8000, true);
        this->includeM_lines = includeMLines;
        this->disabledLinesCodes = disabledLines;
        this->disabledStopsCodes = disabledStops;
        addNodes();
        addEdges();
        if (footDistance != -1)
            addWalkingEdges(footDistance);
        return graph;
    }

    /**
     * Adds the first and end nodes that represent th geo location of the start end end positions
     * @param start starting geo position
     * @param end ending geo position
     * @param radius max walking distance from the nodes being added to the bus network
     */
    void addGeoStartEndNode(Location start, Location end, int radius) {

        Stop stop = {};
        string s = "";
        string startStop = "CURRENT POINT";
        string endStop = "END POINT";
        graph.addNode(len + 1, startStop, s);
        auto it = graph.nodeLocation.insert(pair<string, Location>(startStop, start));
        if (!it.second) {
            it.first->second = start;
            graph.nodes[len + 1].adj = list<InverseGraph::Edge>();
        }
        graph.addNode(len + 2, endStop, s);
        it = graph.nodeLocation.insert(pair<string, Location>(endStop, end));
        if (!it.second) {
            it.first->second = end;
            for (int d = onlyStopsFirstIndex; d <= len; d++) {
                if (!graph.nodes[d].adj.empty() && graph.nodes[d].adj.back().dest == len + 2)
                    graph.nodes[d].adj.pop_back();
            }
        }


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
