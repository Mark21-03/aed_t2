//
// Created by ricar on 27/01/2022.
//

#include "../include/GraphInverseBuilder.h"
#include "../include/files_reader.h"

GraphInverseBuilder &GraphInverseBuilder::addNodes() {
    vector<Line> lines = LinesReader("../dataset/lines.csv");

    int i = 1;
    for (const auto &l: lines) {
        auto aL = availableLines(l.code);

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
                string lineName = l.code;
                graph.addNode(i, *s, lineName);
                nodeToIndex.insert(pair<pair<string,string>, int>(pair<string,string>(*s,lineName), i));
                indexToNode.insert(pair<int, pair<string,string>>(i, pair<string ,string >(*s, lineName)));

                if (it != list.stops.end()) {
                    graph.addEdge(i, i + 1, false, 1);
                }
                i++;

            }
        }
    }

    for (auto d: StopsReader("../dataset/stops.csv")) {
        string s = "";
        graph.addNode(i, d.code, s);
        nodeToIndex.insert(pair<pair<string,string>, int>(pair<string,string>(d.code, s), i));
        indexToNode.insert(pair<int, pair<string,string>>(i++, pair<string ,string >(d.code, s)));
    }

    len = i;
    return *this;

}

GraphInverseBuilder &GraphInverseBuilder::addEdges() {
    vector<Line> lines = LinesReader("../dataset/lines.csv");



    for (int i = 1; i <= len; ++i) {
        for (int j = 1; j <= len; ++j) {
            if (graph.nodes[i].stop.second.empty() || graph.nodes[j].stop.second.empty()) {
                if (graph.nodes[i].stop.first == graph.nodes[j].stop.first && graph.nodes[i].stop.second != graph.nodes[j].stop.second) {
                    graph.addEdge(i, j, false, 2);
                    graph.addEdge(j, i, false, 2);
                }
            }
        }
    }


    return *this;
}

GraphInverseBuilder &GraphInverseBuilder::addWalkingEdges(int radius) {
    return *this;
}

bool GraphInverseBuilder::file_exists(const string &name) {
    ifstream f(name.c_str());
    return f.good();
}

list<string> GraphInverseBuilder::availableLines(const string &code) const {
    list<string> l;

    bool codeIsM_Line = code.back() == 'M';

    if (!includeM_lines && codeIsM_Line) return {};

    string basicPath = "../dataset/line/line_";
    string format = ".csv";
    if (file_exists(basicPath + code + "_" + "0" + format))
        l.push_back(basicPath + code + "_" + "0" + format);
    if (file_exists(basicPath + code + "_" + "1" + format))
        l.push_back(basicPath + code + "_" + "1" + format);

    return l;
}

InverseGraph &GraphInverseBuilder::getGraph(){
    return graph;
}
