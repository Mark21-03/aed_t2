#include "../include/graph.h"
#include "../include/minHeap.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string lineName, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, weight, lineName});

    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


int Graph::dijkstra_distance(int a, int b) {

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

    if (nodes[b].dist != INF)
        return nodes[b].dist;
    return -1;
}


list<int> Graph::dijkstra_path(int a, int b) {

    dijkstra_distance(a, b);
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

void Graph::addNode(int index , string &node) {
    nodes[index].stopName = node;
}
