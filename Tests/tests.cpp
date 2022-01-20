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

    string origin = "TLHR2";
    string destiny = "FEUP2";

    cout << graph.bfsDistance(model.stopToIndex[origin], model.stopToIndex[destiny]) << endl;

}


