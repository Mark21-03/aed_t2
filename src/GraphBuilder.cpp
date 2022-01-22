#include "../include/GraphBuilder.h"

inline bool GraphBuilder::file_exists(const string &name) {
    ifstream f(name.c_str());
    return f.good();
}


list<string> GraphBuilder::available_0_Lines(const string &code) const {
    list<string> l;

    bool codeIsM_Line = code.back() == 'M';

    if (!includeM_lines && codeIsM_Line) return {};

    string basicPath = "../dataset/line/line_";
    string format = ".csv";
    if (file_exists(basicPath + code + "_" + "0" + format))
        l.push_back(basicPath + code + "_" + "0" + format);

    return l;
}

list<string> GraphBuilder::available_1_Lines(const string &code) const {
    list<string> l;

    bool codeIsM_Line = code.back() == 'M';

    if (!includeM_lines && codeIsM_Line) return {};

    string basicPath = "../dataset/line/line_";
    string format = ".csv";

    if (file_exists(basicPath + code + "_" + "1" + format))
        l.push_back(basicPath + code + "_" + "1" + format);

    return l;
}


void GraphBuilder::addNodes() {
    int i = 1;
    for (auto d: StopsReader("../dataset/stops.csv")) {
        graph.addNode(i, d);
        stopToIndex.insert(pair<string, int>(d.code, i));
        indexToStop.insert(pair<int, string>(i++, d.code));
    }

}

void GraphBuilder::addEdges() {
    vector<Line> lines = LinesReader("../dataset/lines.csv");

    for (const auto &l: lines) {
        auto aL = available_0_Lines(l.code);

        while (!aL.empty()) {

            auto first = aL.front();
            aL.pop_front();
            LineStops list;
            ifstream f(first);
            f >> list;

            if (list.stops.empty())
                continue;

            auto it = ++list.stops.begin();
            for (auto s = list.stops.begin(); s != list.stops.end(); s++) {
                // the circular stuff should be treated differently TODO
                if (it != list.stops.end()) {
                    auto b = stopToIndex[*s];
                    auto end = stopToIndex[*it];

                    int zoneDif = graph.getNode(b).stop.zone == graph.getNode(end).stop.zone ? 0 : 1;

                    graph.addEdge(b, end, l, false, {nodeGeoDistance(b, end), zoneDif, 0});
                } else
                    break;
                it++;
            }
        }
    }

    for (const auto &l: lines) {
        auto aL = available_1_Lines(l.code);

        while (!aL.empty()) {

            auto first = aL.front();
            aL.pop_front();
            LineStops list;
            ifstream f(first);
            f >> list;

            if (list.stops.empty())
                continue;

            auto it = ++list.stops.begin();
            for (auto s = list.stops.begin(); s != list.stops.end(); s++) {
                // the circular stuff should be treated differently TODO
                if (it != list.stops.end()) {
                    auto b = stopToIndex[*s];
                    auto end = stopToIndex[*it];

                    int zoneDif = graph.getNode(b).stop.zone == graph.getNode(end).stop.zone ? 0 : 1;

                    graph.addEdge(b, end, l, true, {nodeGeoDistance(b, end), zoneDif, 0});
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

