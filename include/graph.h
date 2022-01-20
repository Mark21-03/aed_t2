#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include "structs.h"

#define INF 999999


using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        Line line;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        Stop stop;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:

    Graph() = default;

    explicit Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, Line line, int weight = 1);

    Node &getNode(int index);

    void addNode(int index, Stop &stop);

    int dijkstra_distance(int a, int b);

    list<int> dijkstra_path(int a, int b);

    void bfsDist(int v);

    int bfsDistance(int a, int b);

    void bfsPrint(int v);

    int dijkstra(int a);

    list<int> bfs_path(int a, int b, vector<Line> &lines);

    Edge getEdge(int src, int dest);

    void findLinePath(Line &currentLine, int son, int parent, vector<Line> &lines);
};


#endif
