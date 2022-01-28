#include "../include/InverseGraph.h"

InverseGraph::InverseGraph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}


void InverseGraph::addEdge(int src, int dest, bool lineDirection, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;

    Edge edge = {dest, weight, lineDirection, src};
    nodes[src].adj.push_back(edge);

    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

InverseGraph::Node &InverseGraph::getNode(int index) {
    return nodes[index];
}

void InverseGraph::addNode(int index, string &stop, string &line) {
    nodes[index].stop = pair<string, string>(stop, line);
}

void InverseGraph::dijkstra(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v = 1; v <= n; v++) {
        nodes[v].dist = INF;
        nodes[v].pred = {-1, INF, false, -1};
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = {s, 0, false, s};
    while (q.getSize() > 0) {
        int u = q.removeMin();
        // cout << "Node " << nodes[u].line.name << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto &e: nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                nodes[v].pred = e;
                q.decreaseKey(v, nodes[v].dist);
            }
        }
    }
}

list<InverseGraph::Edge> InverseGraph::dijkstra_path(int a, int b) {
    list<Edge> path;
    Edge parent = nodes[b].pred;
    path.push_back(parent);

    if (nodes[b].pred.origin == -1)
        return {};

    while (parent.origin != a) {
        parent = nodes[parent.origin].pred;

        //findLinePath( path.back().line ,parent);

        path.push_front(parent);
    }

    return path;
}



