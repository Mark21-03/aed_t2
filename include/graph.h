#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <climits>
#include "structs.h"
#include "minHeap.h"

#define INF (INT_MAX/2)

using namespace std;

class Graph {

public:
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        Line line;
        bool lineDirection;
        int origin;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        Edge pred;
        bool visited;
        Stop stop;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    Graph() = default;

    explicit Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, Line line, bool lineDirection, int weight);

    Node &getNode(int index);

    void addNode(int index, Stop &stop);

    int dijkstra_distance(int a, int b);

    list<Edge> dijkstra_path(int a, int b);

    void bfsDist(int v);

    int bfsDistance(int a, int b);

    void bfsPrint(int v);

    void dijkstra_distance(int a);

    void dijkstra_zones(int a);

    void dijkstra_lineSwaps(int a);

    template<typename Functor>
    void dijkstra(int s, Functor &functor);

    list<Edge> bfs_path(int a, int b);

    Edge getEdge(int src, int dest);

    void findLinePath(Line &currentLine, Edge &edge);

    void addGeoStartEndNode(Location start, Location end, int radius);

    vector<int> nodesInReach(Location pos, int radius);

};


#endif
