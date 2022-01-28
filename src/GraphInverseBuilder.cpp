#include "../include/GraphInverseBuilder.h"

GraphInverseBuilder &GraphInverseBuilder::addNodes() {
    vector<Line> lines = LinesReader("../dataset/lines.csv");

    int i = 1;
    for (const auto &l: lines) {
        if (disabledLinesCodes.count(l.code) > 0)continue;
        auto aL = availableLines(l.code, includeM_lines);

        while (!aL.empty()) {

            auto first = aL.front();
            aL.pop_front();

            //bool direction = first.find("_0.csv") != string::npos;

            LineStops list;
            ifstream f(first);
            f >> list;

            if (list.stops.empty())
                continue;

            auto it = ++list.stops.begin();
            for (auto s = list.stops.begin(); s != list.stops.end() && it != list.stops.end(); s++) {
                if (disabledStopsCodes.count(*s) == 0) {
                    string lineName = l.code;
                    graph.addNode(i, *s, lineName);
                    nodeToIndex.insert(pair<pair<string, string>, int>(pair<string, string>(*s, lineName), i));
                    indexToNode.insert(pair<int, pair<string, string>>(i, pair<string, string>(*s, lineName)));
                }
                graph.addEdge(i, i + 1, false, 1);
                it++;
                i++;
            }
        }
    }

    for (auto d: StopsReader("../dataset/stops.csv")) {
        if (disabledStopsCodes.count(d.code) > 0) continue;
        string s;
        graph.addNode(i, d.code, s);
        nodeToIndex.insert(pair<pair<string, string>, int>(pair<string, string>(d.code, s), i));
        indexToNode.insert(pair<int, pair<string, string>>(i++, pair<string, string>(d.code, s)));
        zones.insert(pair<string,string>( d.code ,d.zone));
    }

    len = i;
    return *this;

}

GraphInverseBuilder &GraphInverseBuilder::addEdges() {
    vector<Line> lines = LinesReader("../dataset/lines.csv");


    for (int i = 1; i <= len; ++i) {
        for (int j = 1; j <= len; ++j) {
            if (graph.nodes[i].stop.second.empty() || graph.nodes[j].stop.second.empty()) {
                if (graph.nodes[i].stop.first == graph.nodes[j].stop.first
                    && graph.nodes[i].stop.second != graph.nodes[j].stop.second) {
                    graph.addEdge(i, j, false, 2);
                    graph.addEdge(j, i, false, 2);
                }
            }
        }
    }


    return *this;
}

GraphInverseBuilder &GraphInverseBuilder::addWalkingEdges(int radius) {
    //TODO
    return *this;
}


