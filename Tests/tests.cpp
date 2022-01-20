#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/distanceCalc.h"
#include "../include/menu.h"
#include "../include/GraphBuilder.h"

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

    string origin = "ESED1"; // TODO ele nao encontra o caminho CQ10   PSL2 nem  COLS PAL3
    string destiny = "IPO5"; //TODO o circular  PAL3  PRG1 nao funciona mas ao contrario sim (esta a considerar a rotacao ao contrario)

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<Line> lines;


    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);

    cout << "Number of stops: " << path.size() << endl;

    cout << endl;

    int i = 0;


    if (path.size() != lines.size()) {
        cout  << "SOMETHING WENT WRONG:\n";

        cout << "Path size : " << path.size()<< " => ";
        for(auto i:path) cout<<model.indexToStop[i]<<" ; ";
        cout<<endl;
        cout << "Line size : " << lines.size() << " => ";
        for(auto i:lines) cout<<i<<" ; ";
        cout<<endl<<endl;
    }


    for (auto it = path.begin(); it != path.end(); it++) {

        cout << model.indexToStop[*it] << " ;  " << lines[i] << endl;

        i++;
    }

}

TEST(Test_bfsPrint, Test_bfsPrint) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();


    //graph.bfsPrint(1);

}



