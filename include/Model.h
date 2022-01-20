#ifndef AED_T2_MODEL_H
#define AED_T2_MODEL_H

#include "graph.h"
#include "files_reader.h"
#include "map"
#include "distanceCalc.h"

inline bool file_exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

class Model {
    Graph stops;
    map<string, int> stopToIndex;

    Model() {
        stops = Graph(2487 + 2, true);

        int i = 1;
        for (auto d : StopsReader("../dataset/stops.csv")) {
            stopToIndex.insert(pair<string, int>(d.code, i++));
        }

        for (auto l : LinesReader("../dataset/lines.csv")) {
            auto aL = availableLines(l.code);
            while (!aL.empty()) {
                auto first = aL.front();
                aL.pop_front();
                LineStops list;
                ifstream f(first);
                f >> list;
                auto it = list.stops.begin()++;
                for (auto s = list.stops.begin(); s != list.stops.end(); s++) {
                    if (it != list.stops.end()) {
                        auto b = stopToIndex[*s];
                        auto end = stopToIndex[*it];
                        stops.addEdge(b, end, INT_MAX);
                    } else
                        break;
                    it++;
                }
            }
        }
    }

    static list<string> availableLines(string code) {
        list<string> l;

        string basicPath = "../line/line_";
        string format = ".csv";
        if (file_exists(basicPath+code+"_"+"0" + format))
            l.push_back(basicPath+code+"_"+"0"+ format);
        if (file_exists(basicPath+code+"_"+"1"+ format))
            l.push_back(basicPath+code+"_"+"1"+ format);

        return l;
    }

};


#endif //AED_T2_MODEL_H
