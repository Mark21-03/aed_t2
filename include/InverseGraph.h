#ifndef AED_T2_INVERSEGRAPH_H
#define AED_T2_INVERSEGRAPH_H


#include "GraphBuilder.h"

class InverseGraph {
public:

    /**
     * An edge links two nodes and can have a direction and weight
     */
    struct Edge {
        int dest;
        int weight;
        bool lineDirection;
        int origin;
    };

    /**
     * A node is a bus stop, holding additional tributes
     */
    struct Node {
        list<Edge> adj;
        int dist;
        Edge pred;
        bool visited;
        pair<string, string> stop;
    };

    int n;
    bool hasDir;
    vector<Node> nodes;
    map<string, Location> nodeLocation;
    map<string, string> zones;


    /**
     * Default empty constructor
     */
    InverseGraph() = default;

    /**
     * Creates a graph with N given nodes and if their edges have a direction
     * @param nodes number of nodes to consider
     * @param dir boolean if nodes' edges should have a direction
     */
    explicit InverseGraph(int nodes, bool dir = false);

    /**
     * Adds an edge between two nodes
     * @param src starting node to be linked
     * @param dest ending node to be linked
     * @param lineDirection boolean if edge has a direction
     * @param weight edge weight
     */
    void addEdge(int src, int dest, bool lineDirection, int weight);

    /**
     * gets the node in the index
     * @param index
     * @return
     */
    Node &getNode(int index);

    /**
     * Creates and adds a node to the position
     * @param index
     * @param stop
     * @param line
     */
    void addNode(int index, string &stop, string &line);

    /**
     * Time complexity of {\displaystyle O(E+V\log(V))}.
     * @param s
     */
    void dijkstra(int s);

    /**
     * Time complexity of O(n). n being the size of the path
     * @param a
     * @param b
     * @return
     */
    list<InverseGraph::Edge> dijkstra_path(int a, int b);

};


#endif //AED_T2_INVERSEGRAPH_H
