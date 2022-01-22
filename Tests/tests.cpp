#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/distanceCalc.h"
#include "../include/menu.h"
#include "../include/GraphBuilder.h"


#define geoCQueijo {41.16861948613213, -8.6899475068589}
#define geoFeup {41.17838121987286, -8.599018100763733}
#define geoPassal {41.15203283630788, -8.49986876108789}
#define geoFcup {41.15223552642268, -8.636936732334394}
#define geoFrancelos {41.10191154587645, -8.659713734654174}
#define geoIkea {41.20962241758282, -8.688599177567802}
#define geoAliados {41.14843076280013, -8.610857716992687}
#define geoBomSucesso {41.15576823832895, -8.629961857769722}
#define geoPalBolsa {41.14073588624748, -8.615741317702945}
#define geoGaiaShopping{41.117352653497626, -8.621390956976255}
#define geoNorteShopping{41.17921590595752, -8.652310502100645}
#define geoCordoaria{41.14546314938763, -8.616957405759472}
#define geoAlfena{41.24468890867462, -8.52083368770199}
#define geoCampanha{41.14885301366697, -8.585581573539976}
#define geoSouto{41.136360363397294, -8.530595914787796}

#define geoStartNode 2488
#define geoEndNode 2489


using testing::Eq;


TEST(Test_bfs, Test_bfs) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    //A melhor combinacao para testar é FRC ALXH1  ou CQ10 PSL1 porque atravessa o porto por comleto (muito longe)
    string origin = "PSL2";
    string destiny = "ASP2";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<pair<Line, bool>> lines;

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);

    cout << "Number of stops: " << path.size() << endl << endl;

    cout << "Path size : " << path.size() << " => ";
    for (auto i: path) cout << model.indexToStop[i] << " ; ";
    cout << endl;
    cout << "Line size : " << lines.size() << " => ";
    for (const auto &i: lines) cout << i.first.code << " ; ";
    cout << endl << endl;

    int i = 0;
    for (int &it: path) {

        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.name << endl;

        i++;
    }
}

TEST(Test_dijkstra, Test_dijkstra) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph(false);

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    graph.addGeoStartEndNode(geoSouto, geoGaiaShopping, 500);
    vector<pair<Line, bool>> lines;

    /*
    1: dijkstra_zones(a);
    2: dijkstra_distance(a);
    3: dijkstra_lineSwaps(a);
     */


    list<int> path = graph.dijkstra_path(geoStartNode, geoEndNode, lines, 2);

    cout << "Path size : " << path.size() << " => ";
    for (auto i: path) cout << model.indexToStop[i] << " ; ";
    cout << endl;
    cout << "Line size : " << lines.size() << " => ";
    for (auto i: lines) cout << i.first.code << " ; ";
    cout << endl << endl;

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << setw(20) << lines[i].first.lineDirectionName(lines[i].second) << "\t" << graph.getNode(*it).stop.zone
             << " "
             << endl;


        i++;
    }

}

