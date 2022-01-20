#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <queue>

#define INF 999999


using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        string line;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string stopName;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:

    Graph() = default;

    explicit Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, string lineName, int weight = 1);

    Node &getNode(int index);

    void addNode(int index, string &node);

    int dijkstra_distance(int a, int b);

    list<int> dijkstra_path(int a, int b);

    void bfsDist(int v);

    int bfsDistance(int a, int b);

    int dfs(int v);

    void bfs(int v);
};


#endif
