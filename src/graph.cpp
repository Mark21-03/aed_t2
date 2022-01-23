#include "../include/graph.h"

#include <utility>
#include "set"
#include "../include/files_reader.h"
#include "../include/distanceCalc.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Line line, bool lineDirection, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;

    Edge edge = {dest, weight, std::move(line), lineDirection, src};
    nodes[src].adj.push_back(edge);

    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

Graph::Edge Graph::getEdge(int src, int dest) { // TODO: THIS METHOD IS WRONG... WE HAVE MULTIPLE edges for the same nodes

    for (Edge e: nodes[src].adj)
        if (e.dest == dest)
            return e;

    return {};
}


vector<int> Graph::nodesInReach(Location pos, int radius) {

    vector<int> v;
    for (int i = 1; i <= n; i++)
        if (distanceCalc(nodes[i].stop.location, pos) <= radius)
            v.push_back(i);
    return v;
}


void Graph::addGeoStartEndNode(Location start, Location end, int radius) {

    Stop stop = {};
    addNode(2488, stop);
    addNode(2489, stop);

    vector<int> nodesStart = nodesInReach(start, radius);
    vector<int> nodesEnd = nodesInReach(end, radius);

    //adicionar as edges para caminhar a pé da origem e até destino

    auto distCalc = [&](Location l, int i) {
        return (int) distanceCalc(l, getNode(i).stop.location);
    };

    for (auto i: nodesStart)
        addEdge(2488, i, {"__FOOT__", "__FOOT__"}, false, INF);

    for (auto i: nodesEnd)
        addEdge(i, 2489, {"__FOOT__", "__FOOT__"}, true, INF);

}


//distance criteria
void Graph::dijkstra_distance(int a) {

    auto lambda = [this](int x, Edge y) {
        Location l1 = nodes[x].stop.location;
        Location l2 = nodes[y.dest].stop.location;

        return distanceCalc(l1, l2);
    };

    dijkstra(a, lambda);

}

//min zones criteria
void Graph::dijkstra_zones(int a) {

    auto lambda = [this](int x, Edge y) {

        return nodes[x].stop.zone == nodes[y.dest].stop.zone ? 0 : 1;
    };

    dijkstra(a, lambda);

}

//min line changes criteria
void Graph::dijkstra_lineSwaps(int a) {


    auto lambda = [this, a](int x, Edge& y) {

        if (y.line.code == nodes[x].pred.line.code) {
            return 0;
        }
        set<int> seen;
        while (y.origin != a ) {
            if (seen.find(y.origin) != seen.end())
                break;
            y.weight += 3000;
            seen.insert(y.origin);
            y = nodes[x].pred;

        }

        return 4000;

    };


    dijkstra(a, lambda);

}


int Graph::dijkstra_distance(int a, int b) {
    dijkstra_distance(a);
    if (nodes[b].dist != INF)
        return nodes[b].dist;
    return -1;
}


list<Graph::Edge> Graph::dijkstra_path(int a, int b) {
    Line currentLine;
    list<Edge> path;
    Edge parent = nodes[b].pred;
    path.push_back(parent);

    if (nodes[b].pred.origin == -1)
        return {};

    while (parent.origin != a) {
        parent = nodes[parent.origin].pred;

        path.push_front(parent);
    }

    return path;
}

Graph::Node &Graph::getNode(int index) {
    return nodes[index];
}

void Graph::addNode(int index, Stop &stop) {
    nodes[index].stop = stop;
}


list<Graph::Edge> Graph::bfs_path(int a, int b) {
    Line currentLine;
    bfsDist(a);
    list<Edge> path;
    Edge parent = nodes[b].pred;
    path.push_back(parent);

    if (nodes[b].pred.origin == -1)
        return {};

    while (parent.origin != a) {
        parent = nodes[parent.origin].pred;

        path.push_front(parent);
    }

    return path;
}

//distancia entre dois nós (sem pesos)
int Graph::bfsDistance(int a, int b) {
    if (a == b) return 0;
    for (int i = 1; i <= n; i++)
        nodes[i].dist = -1;
    bfsDist(a);
    return nodes[b].dist;
}

// V será o no de origem e calcula a distancia deste a todos os nós
void Graph::bfsDist(int v) {
    nodes[v].dist = 0;
    for (int v = 1; v <= n; v++) {
        nodes[v].visited = false;
        nodes[v].pred.origin = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        //cout << u << " "; // show node order
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                nodes[w].pred = e;
            }
        }
    }

}


// Depth-First Search
void Graph::bfsPrint(int v) {
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        cout << nodes[u].stop << endl; // show nodes
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            //cout<<e.line<<endl; //show edges
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

//esta funcao procura uma edge entre dois nós tentando manter a mesma linha se possivel
void Graph::findLinePath(Line &currentLine, int son, int parent, vector<pair<Line, bool>> &lines) {
    Edge newLineCandidate;

    for (Edge e: nodes[parent].adj) {
        if (e.dest == son) {
            if (e.line.code == currentLine.code) {
                lines.insert(lines.begin(), pair<Line, bool>(currentLine, e.lineDirection));
                return;
            } else {
                newLineCandidate = e;
            }
        }
    }

    currentLine = newLineCandidate.line;
    lines.insert(lines.begin(), pair<Line, bool>(currentLine, newLineCandidate.lineDirection));
}

template<typename Functor>
void Graph::dijkstra(int s, Functor &functor) {
    MinHeap<int, int> q(n, -1);
    for (int v = 1; v <= n; v++) {
        nodes[v].dist = INF;
        nodes[v].pred = {-1,INF,"", ""};
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = {s, 0, "", "", false, s};
    while (q.getSize() > 0) {
        int u = q.removeMin();
        // cout << "Node " << nodes[u].stop.name << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto& e: nodes[u].adj) {
            int v = e.dest;
            int w = functor(u, e);
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                nodes[v].pred = e;
                q.decreaseKey(v, nodes[v].dist);
            }
        }
    }
}



