#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include "structs.h"
#include "minHeap.h"

#define INF 999999


using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        WeightCriteria weight; // An integer weight
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

    void addEdge(int src, int dest, Line line, WeightCriteria weight = {0, 0, 0});

    Node &getNode(int index);

    void addNode(int index, Stop &stop);

    int dijkstra_distance(int a, int b);

    list<int> dijkstra_path(int a, int b, vector<Line> &lines, int swicther);

    void bfsDist(int v);

    int bfsDistance(int a, int b);

    void bfsPrint(int v);

    void dijkstra_distance(int a);

    void dijkstra_zones(int a);

    void dijkstra_lineSwaps(int a);

    template<typename Functor>
    void dijkstra(int a, Functor& functor) {
        for (int i = 1; i <= n; i++) {
            nodes[i].dist = INF;
            nodes[i].visited = false;
            nodes[i].pred = -1;
        }

        nodes[a].dist = 0;
        nodes[a].pred = -1;

        MinHeap<int, int> heap(n, -1);

        for (int i = 1; i <= n; i++)
            heap.insert(i, nodes[i].dist);

        while (heap.getSize() > 0) {

            int u = heap.removeMin();

            nodes[u].visited = true;

            for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {

                int v = nodes[it->dest].dist;

                int cost = functor(u , it->dest) + nodes[u].dist;

                if (v > cost && !nodes[it->dest].visited) {

                    nodes[it->dest].dist = cost;

                    v = cost;

                    nodes[it->dest].pred = u;

                    heap.decreaseKey(it->dest, v);
                }
            }
        }
    }

    list<int> bfs_path(int a, int b, vector<Line> &lines);

    Edge getEdge(int src, int dest);

    void findLinePath(Line &currentLine, int son, int parent, vector<Line> &lines);
};


#endif
