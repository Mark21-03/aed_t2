#include "../include/GraphBuilder.h"


GraphBuilder &GraphBuilder::addNodes(const set<string> &disabledStops) {
    int i = 1;
    for (auto d: StopsReader("../dataset/stops.csv")) {
        if (disabledStops.count(d.code) == 1) continue;
        graph.addNode(i, d);
        stopToIndex.insert(pair<string, int>(d.code, i));
        indexToStop.insert(pair<int, string>(i++, d.code));
    }
    return *this;
}

GraphBuilder &GraphBuilder::addEdges(const set<string> &disabledLines) {
    vector<Line> lines = LinesReader("../dataset/lines.csv");

    for (const auto &l: lines) {
        if (disabledLines.count(l.code) == 1) continue;
        auto aL = availableLines(l.code, includeM_lines);

        while (!aL.empty()) {

            auto first = aL.front();
            aL.pop_front();

            bool direction = first.find("_0.csv") != string::npos;

            LineStops list;
            ifstream f(first);
            f >> list;

            if (list.stops.empty())
                continue;

            auto it = ++list.stops.begin();
            for (auto s = list.stops.begin(); s != list.stops.end(); s++) {
                if (it != list.stops.end()) {
                    auto b = stopToIndex[*s];
                    auto end = stopToIndex[*it];

                    graph.addEdge(b, end, l, direction, INF);
                } else
                    break;
                it++;
            }
        }
    }
    return *this;
}

int GraphBuilder::nodeGeoDistance(int start, int end) {

    Location l1 = graph.getNode(start).stop.location;
    Location l2 = graph.getNode(end).stop.location;

    return (int) distanceCalc(l1, l2);
}

GraphBuilder &GraphBuilder::addWalkingEdges(int radius) {
    for (auto &s: graph.nodes) {
        vector<int> v = graph.nodesInReach(s.stop.location, radius);
        for (auto i: v) {
            if (stopToIndex[s.stop.code] == i)
                continue;

            graph.addEdge(stopToIndex[s.stop.code], i, Line{"__FOOT__", "__FOOT__"}, true,
                          INF); // TODO: CHECK LINE DIRECTION and name
        }
    }
    return *this;
}

const Graph &GraphBuilder::getGraph() const {
    return graph;
}

