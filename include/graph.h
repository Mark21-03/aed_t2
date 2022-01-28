#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <climits>
#include "structs.h"
#include "minHeap.h"
#include<set>

#define INF (INT_MAX/2)

using namespace std;

/**
 * Graph structure: composed of nodes linked by edges
 */
class Graph {
public:
    /**
     * An edge links two nodes and can have a direction and weight
     * In this case, an edge is a connection between two stops and holds
     * the bus line that connects them
     */
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        Line line;
        bool lineDirection;
        int origin;
    };

    /**
     * A node is a bus stop, holding additional tributes
     */
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

    /**
     * Default constructor
     */
    Graph() = default;

    /**
     * Creates a graph with N nodes and if there is a direction to their edges
     * @param nodes number of nodes to be built
     * @param dir boolean if edge direction exists
     */
    explicit Graph(int nodes, bool dir = false);

    /**
     * Adds an edge between two nodes
     * @param src start node to be linked
     * @param dest end node to be linked
     * @param line bus line that makes the edge
     * @param lineDirection edge direction
     * @param weight weight of the edge (it can represent multiple things)
     */
    void addEdge(int src, int dest, Line line, bool lineDirection, int weight);

    /**
     * Returns a reference to a graph node
     * @param index index of the node to be returned
     * @return reference to the node stored with the given index
     */
    Node &getNode(int index);

    /**
     * Adds a node to an index
     * @param index index where to add the node in the graph
     * @param stop main value of a node is the bus stop it represents
     */
    void addNode(int index, Stop &stop);

    /**
     * Calculates the distance between two nodes A and B
     * based on the edge's weight
     * @param a starting node
     * @param b end node
     * @return distance between nodes
     */
    int dijkstra_distance(int a, int b);

    /**
     * Creates a edge path between the nodes A and B
     * @param a start node
     * @param b end node
     * @return edge path to be taken to reach B starting at A
     */
    list<Edge> dijkstra_path(int a, int b);

    /**
     * Sets the nodes dist attribute to their relative nodal distance to
     * the start node (dist = 0)
     * @param v start node to consider as dist = 0
     */
    void bfsDist(int v);

    /**
     * Returns the distance between two nodes using nodal distance of BFS
     * @param a node to use as dist = 0
     * @param b node we want to know the distance from A
     * @return how many nodes are between A and B
     */
    int bfsDistance(int a, int b);

    /**
     * Prints the entire graph using BFS
     * @param v node where to start printing
     */
    void bfsPrint(int v);

    /**
     * Sets the nodes weight and dist values to the geographic distance
     * they are from the node A, based on the edges weights
     * @param a dijkstra algorithm
     */
    void dijkstra_distance(int a);

    /**
     * Sets the nodes weight and dist values based on the weights of the edges
     * which, in this case, have weight >0 if they connect 2 different bus zones
     * @param a node where to start the dijkstra algorithm
     */
    void dijkstra_zones(int a);

    /**
     * Sets the nodes weight and dist values based on the weights of the edges
     * which, in this case, have weight >0 if edges connect different bus lines
     * @param a node where to start dijkstra algorithm
     */
    void dijkstra_lineSwaps(int a);

    /**
     * Dijkstra algorithm finds shortest paths and sets the nodes dist based on the
     * distance they are from the starting node taking into account edge weight
     * @tparam Functor weight function calculator
     * @param s node where to start dijkstra algorithm
     * @param functor function that calculates dijkstra's edge and node cost distance
     */
    template<typename Functor>
    void dijkstra(int s, Functor &functor);

    /**
     * Returns the path that BFS algorithm follows to traverse
     * from node A to B with minimum nodal distance
     * @param a
     * @param b
     * @return
     */
    list<Edge> bfs_path(int a, int b);

    /**
     * Given a current bus line and an edge, it attempts to find
     * an edge connecting the same nodes but maintaining the same bus line
     * @param currentLine current bus line being used
     * @param edge edge connecting two bus stops
     */
    void findLinePath(Line &currentLine, Edge &edge);

    /**
     * Adds a start and end nodes position and links them to the
     * bus stops inside a certain geographic radius from them
     * @param start location of the start node/position
     * @param end location of the end node/position
     * @param radius radius where to search from the start/end node for bus stops to add new walking edges
     */
    void addGeoStartEndNode(Location start, Location end, int radius);

    /**
     * Returns all nodes inside a certain radius from a position
     * @param pos position center where to search
     * @param radius radius of the circle to create and boundary search
     * @return vector with all nodes' indexes that are inside the radius
     */
    vector<int> nodesInReach(Location pos, int radius);

};


#endif
