#include "../include/graph.h"

#include <utility>
#include "../include/minHeap.h"
#include "../include/files_reader.h"
#include "../include/distanceCalc.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Line line, bool lineDirection, WeightCriteria weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;

    Edge edge = {dest, weight, std::move(line), lineDirection};
    nodes[src].adj.push_back(edge);

    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

Graph::Edge Graph::getEdge(int src, int dest) {

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
        addEdge(2488, i, {"__FOOT__", "__FOOT__"}, false, {distCalc(start, i), 0, 1});

    for (auto i: nodesEnd)
        addEdge(i, 2489, {"__FOOT__", "__FOOT__"}, true, {distCalc(end, i), 0, 1});

}


//distance criteria
void Graph::dijkstra_distance(int a) {

    auto lambda = [this] (int x, int y) {
        Location l1 = nodes[x].stop.location;
        Location l2 = nodes[y].stop.location;

        return distanceCalc(l1, l2); };

    dijkstra(a, lambda);

}

//min zones criteria
void Graph::dijkstra_zones(int a) {

    auto lambda = [this] (int x, int y) {

        return nodes[x].stop.zone == nodes[y].stop.zone ? 0 : 1;};

    dijkstra(a, lambda);

}

//min line changes criteria
void Graph::dijkstra_lineSwaps(int a) {

    auto lambda = [this] (int x, int y) {

        return nodes[x].stop.code == nodes[y].stop.code ? 0 : 1;};

    dijkstra(a, lambda);

}


int Graph::dijkstra_distance(int a, int b) {
    dijkstra_distance(a);
    if (nodes[b].dist != INF)
        return nodes[b].dist;
    return -1;
}


list<int> Graph::dijkstra_path(int a, int b, vector<pair<Line, bool>> &lines, int switcher) {
    Line currentLine;

    switch (switcher) {
        case 1:
            dijkstra_zones(a);
            break;
        case 2:
            dijkstra_distance(a);
            break;
        case 3:
            dijkstra_lineSwaps(a);
            break;
    }


    list<int> path = {b};
    int parent = b;
    int son = parent;

    if (nodes[b].pred == -1)
        return {};

    while (parent != a) {
        son = parent;
        parent = nodes[parent].pred;

        if (path.size() == 1)
            currentLine = getEdge(parent, son).line;

        path.push_front(parent);

        findLinePath(currentLine, son, parent, lines);
    }

    return path;
}

Graph::Node &Graph::getNode(int index) {
    return nodes[index];
}

void Graph::addNode(int index, Stop &stop) {
    nodes[index].stop = stop;
}


list<int> Graph::bfs_path(int a, int b, vector<pair<Line, bool>> &lines) {
    Line currentLine;
    bfsDist(a);
    list<int> path = {b};
    int parent = b;
    int son = parent;

    if (nodes[b].pred == -1)
        return {};

    while (parent != a) {
        son = parent;
        parent = nodes[parent].pred;

        if (path.size() == 1)
            currentLine = getEdge(parent, son).line;

        path.push_front(parent);

        findLinePath(currentLine, son, parent, lines);
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
        nodes[v].pred = -1;
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
                nodes[w].pred = u;
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



