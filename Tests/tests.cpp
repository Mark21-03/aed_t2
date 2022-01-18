#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/lines_reader.h"

using testing::Eq;


TEST(Test_lines_reader, Test_lines_reader) {

    vector<Line> lines = reader("../dataset/lines.csv");

    for (const Line &l: lines)
        cout << l << endl;

}
