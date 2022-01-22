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
        WeightCriteria weight; // An integer weight
        Line line;
        bool lineDirection;
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

    void addEdge(int src, int dest, Line line, bool lineDirection, WeightCriteria weight = {0, 0, 0});

    Node &getNode(int index);

    void addNode(int index, Stop &stop);

    int dijkstra_distance(int a, int b);

    list<int> dijkstra_path(int a, int b, vector<pair<Line, bool>> &lines, int swicther);

    void bfsDist(int v);

    int bfsDistance(int a, int b);

    void bfsPrint(int v);

    void dijkstra_distance(int a);

    int dijkstra_zones(int a);

    void dijkstra_lineSwaps(int a);

    list<int> bfs_path(int a, int b, vector<pair<Line, bool>> &lines);

    Edge getEdge(int src, int dest);

    void findLinePath(Line &currentLine, int son, int parent, vector<pair<Line, bool>> &lines);

    void addGeoStartEndNode(Location start, Location end, int radius);

    vector<int> nodesInReach(Location pos, int radius);
};


#endif
