#include "../include/graph.h"
#include "../include/minHeap.h"
#include "../include/files_reader.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Line line, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, weight, line});

    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

Graph::Edge Graph::getEdge(int src, int dest) {

    for (Edge e: nodes[src].adj)
        if (e.dest == dest)
            return e;

    return {};
}


int Graph::dijkstra(int a) {

    //inicializar os nodes
    for (int i = 1; i <= n; i++) {
        nodes[i].dist = INF;
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }

    //nó inicial não tem pai e tem distancia 0 a ele proprio
    nodes[a].dist = 0;
    nodes[a].pred = -1;

    //criamos a heap e acrescentamos o nó de partida
    MinHeap<int, int> heap(n, -1);


    for (int i = 1; i <= n; i++)
        heap.insert(i, nodes[i].dist);

    //executar algoritmo enquanto existirem nodes por ver
    while (heap.getSize() > 0) {

        int u = heap.removeMin(); //nó com mais prioridade a ser removido (aquele com min dist)

        //se o node não foi visitado, vista-lo e verificar as suas edges
        nodes[u].visited = true;

        //verificar ha arestas para relaxar
        for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {

            int v = nodes[it->dest].dist; // distancia do no de destino

            int cost = it->weight + nodes[u].dist; // custo se considerarmos o no de partida da edge mais o peso da edge

            //relaxa a aresta se encontrou um caminho melhor
            if (v > cost && !nodes[it->dest].visited) {

                nodes[it->dest].dist = cost;

                v = cost; // atualiza para o novo custo minimo

                nodes[it->dest].pred = u; // define o novo pai para esse no de destino

                heap.decreaseKey(it->dest, v); //atualiza a prioridade (distancia) na heap
            }
        }
    }
}


int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].dist != INF)
        return nodes[b].dist;
    return -1;
}


list<int> Graph::dijkstra_path(int a, int b) {

    dijkstra(a);
    list<int> path = {b};
    int parent = b;

    if (nodes[b].pred == -1)
        return {};

    while (parent != a) {
        parent = nodes[parent].pred;
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


list<int> Graph::bfs_path(int a, int b, vector<Line> &lines) {
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

void Graph::findLinePath(Line &currentLine, int son, int parent, vector<Line> &lines) {
    Line newLineCandidate = {"NULL", "NULL"};

    for (Edge e: nodes[parent].adj) {
        if (e.dest == son) {
            if (e.line.code == currentLine.code) {
                lines.insert(lines.begin(), currentLine);
                return;
            } else {
                newLineCandidate = e.line;
            }
        }
    }
    currentLine = newLineCandidate;
    lines.insert(lines.begin(), currentLine);
}
