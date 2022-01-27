#ifndef AED_T2_INVERSEGRAPH_H
#define AED_T2_INVERSEGRAPH_H


#include "GraphBuilder.h"

class InverseGraph {
public:
    struct Edge {
        int dest;
        int weight;
        bool lineDirection;
        int origin;
    };

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


    InverseGraph() = default;

    explicit InverseGraph(int nodes, bool dir = false);

    void addEdge(int src, int dest, bool lineDirection, int weight);

    Node &getNode(int index);

    void addNode(int index, string &stop, string &line);

    void dijkstra(int s);

    list<InverseGraph::Edge> dijkstra_path(int a, int b);
};


#endif //AED_T2_INVERSEGRAPH_H
