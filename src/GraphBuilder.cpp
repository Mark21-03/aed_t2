#include "../include/GraphBuilder.h"


GraphBuilder &GraphBuilder::addNodes() {
    int i = 1;
    for (auto d: StopsReader("../dataset/stops.csv")) {
        if (disabledStopsCodes.count(d.code) > 0) continue;

        graph.addNode(i, d);
        stopToIndex.insert(pair<string, int>(d.code, i));
        indexToStop.insert(pair<int, string>(i++, d.code));
    }
    return *this;
}


GraphBuilder &GraphBuilder::addEdges() {
    vector<Line> lines = LinesReader("../dataset/lines.csv");

    for (const auto &l: lines) {
        if (disabledLinesCodes.count(l.code) > 0)continue;
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
                    if (disabledStopsCodes.count(*s) <= 0) {

                        auto b = stopToIndex[*s];
                        auto end = stopToIndex[*it];

                        graph.addEdge(b, end, l, direction, INF);
                    }
                } else
                    break;
                it++;
            }
        }
    }
    return *this;
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

