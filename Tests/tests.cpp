#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/lines_reader.h"
#include "../include/distanceCalc.h"
#include "../include/menu.h"

using testing::Eq;


TEST(Test_lines_reader, Test_lines_reader) {

    vector<Line> lines = reader("../dataset/lines.csv");

    for (const Line &l: lines)
        cout << l << endl;


}

TEST(Test_distance_calc, Test_distance_calc) {

    cout << distanceCalc(41.17567866, -8.614147205, 41.19931569, -8.657616107) << endl;

}



