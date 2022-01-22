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

#define geoStartNode 2488
#define geoEndNode 2489


using testing::Eq;


TEST(Test_lines_reader, Test_lines_reader) {

    vector<Line> lines = LinesReader("../dataset/lines.csv");

/*    for (const Line &l: lines)
        cout << l << endl;*/

}

TEST(Test_distance_calc, Test_distance_calc) {

    //cout << distanceCalc(41.17567866, -8.614147205, 41.19931569, -8.657616107) << endl;

}


TEST(Test_stops_reader, Test_stops_reader) {

    vector<Stop> stops = StopsReader("../dataset/stops.csv");

/*    for (const Stop &l: stops)
        cout << l << endl;*/

    //cout.precision(10);
    //cout << endl << stops[0].location << endl;

}

TEST(Test_model, Test_model_constructor) {
    GraphBuilder model = GraphBuilder();

    model.buildGraph();

    ASSERT_EQ(model.stopToIndex["1AL2"], 1);
    ASSERT_EQ(model.stopToIndex["ZOID2"], 2487);

}

TEST(Test_bfs, Test_bfs) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    //A melhor combinacao para testar é FRC ALXH1  ou CQ10 PSL1 porque atravessa o porto por comleto (muito longe)
    string origin = "PSL2";
    string destiny = "ASP2";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<Line> lines;

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);

    cout << "Number of stops: " << path.size() << endl;

    cout << endl;

    int i = 0;


    if (path.size() != lines.size()) {
        cout << "Path size : " << path.size() << " => ";
        for (auto i: path) cout << model.indexToStop[i] << " ; ";
        cout << endl;
        cout << "Line size : " << lines.size() << " => ";
        for (auto i: lines) cout << i.code << " ; ";
        cout << endl << endl;
    }


    for (auto it = path.begin(); it != path.end(); it++) {

        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].name << endl;

        i++;
    }
}

TEST(Test_bfsPrint, Test_bfsPrint) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();


    //graph.bfsPrint(1);

}

TEST(Test_dijkstra, Test_dijkstra_zones) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    graph.addGeoStartEndNode(geoFcup, geoFeup, 10000);
    vector<Line> lines;

    list<int> path = graph.dijkstra_path(geoStartNode, geoEndNode, lines, 1);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << setw(20) << lines[i].name << "\t" << graph.getNode(*it).stop.zone << endl;


        i++;
    }

}

TEST(Test_dijkstra, Test_dijkstra_distance) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    graph.addGeoStartEndNode(geoFeup, geoFcup, 500);
    vector<Line> lines;

    list<int> path = graph.dijkstra_path(originIndex, geoEndNode, lines, 2);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << setw(20) << lines[i].name << endl;
        i++;
    }

}


TEST(Test_dijkstra, Test_dijkstra_swap) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "STBX2";
    string destiny = "VLC2";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    graph.addGeoStartEndNode(geoFeup, geoFcup, 500);

    vector<Line> lines;

    list<int> path = graph.dijkstra_path(2488, 2489, lines, 3);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << setw(20) << lines[i].name << endl;
        i++;
    }

}


TEST(Test_bfs, Test_bfs_walk) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "FNTL1";
    string destiny = "SAR2";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    graph.addGeoStartEndNode(geoFeup, geoFcup, 500);


    vector<Line> lines;

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);

    cout << "Number of stops: " << path.size() << endl;

    cout << endl;

    int i = 0;


    if (path.size() != lines.size()) {
        cout << "Path size : " << path.size() << " => ";
        for (auto i: path) cout << model.indexToStop[i] << " ; ";
        cout << endl;
        cout << "Line size : " << lines.size() << " => ";
        for (auto i: lines) cout << i.code << " ; ";
        cout << endl << endl;
    }


    for (auto it = path.begin(); it != path.end(); it++) {

        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].name << endl;

        i++;
    }
}




