#include "../include/GraphBuilder.h"

inline bool GraphBuilder::file_exists(const string &name) {
    ifstream f(name.c_str());
    return f.good();
}

list<string> GraphBuilder::availableLines(const string &code) {
    list<string> l;

    string basicPath = "../dataset/line/line_";
    string format = ".csv";
    if (file_exists(basicPath + code + "_" + "0" + format))
        l.push_back(basicPath + code + "_" + "0" + format);
    if (file_exists(basicPath + code + "_" + "1" + format))
        l.push_back(basicPath + code + "_" + "1" + format);

    return l;
}


void GraphBuilder::addNodes() {
    int i = 1;
    for (auto d: StopsReader("../dataset/stops.csv")) {
        graph.addNode(i, d.code);
        stopToIndex.insert(pair<string, int>(d.code, i++));
    }

}

void GraphBuilder::addEdges() {
    for (const auto &l: LinesReader("../dataset/lines.csv")) {
        auto aL = availableLines(l.code);
        while (!aL.empty()) {
            auto first = aL.front();
            aL.pop_front();
            LineStops list;
            ifstream f(first);
            f >> list;
            if (list.stops.empty())
                continue;
            auto it = ++list.stops.begin();
            for (auto s = list.stops.begin();
                 s != list.stops.end(); s++) { // the circular stuff should be treated differently TODO
                if (it != list.stops.end()) {
                    auto b = stopToIndex[*s];
                    auto end = stopToIndex[*it];
                    graph.addEdge(b, end, first, nodeGeoDistance(b, end));
                } else
                    break;
                it++;
            }
        }
    }

}

int GraphBuilder::nodeGeoDistance(int start, int end) {

    Location l1 = graph.getNode(start).stop.location;
    Location l2 = graph.getNode(end).stop.location;

    return distanceCalc(l1, l2);
}