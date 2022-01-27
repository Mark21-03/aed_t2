//
// Created by ricar on 27/01/2022.
//

#ifndef AED_T2_INVERSEGRAPH_H
#define AED_T2_INVERSEGRAPH_H


#include "GraphBuilder.h"

class InverseGraph {
public:
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        bool lineDirection;
        int origin;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        Edge pred;
        bool visited;
        pair<string ,  string> stop;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: Indirect; true: directed
    vector<Node> nodes; // The list of nodes being represented


    InverseGraph() = default;

    explicit InverseGraph(int nodes, bool dir = false);

    void addEdge(int src, int dest, bool lineDirection , int weight);

    Node &getNode(int index);

    void addNode(int index, string &stop, string & line);

    void dijkstra(int s);

    list<InverseGraph::Edge> dijkstra_path(int a, int b);
};


#endif //AED_T2_INVERSEGRAPH_H
