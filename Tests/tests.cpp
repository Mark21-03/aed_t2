#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Eq;


/*
template<class Sortable>
int binarySearch(vector<Sortable> v, Sortable val) {

    int l = 0, r = v.size() - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;

        if (v[m] == val)
            return m;

        if (v[m] < val)
            l = m + 1;

        else
            r = m - 1;
    }

    // if we reach here, then element was
    // not present
    return -1;
}
*/
/*
TEST(Test_bfs, Test_bfs) {


    vector<string> stopsCode = StopsCodesReader("../dataset/lines.csv");

    string val = "AGR1";

    bool found = binary_search(stopsCode.begin(), stopsCode.end(), val);

    if (found)
        cout << "\nFound!\n";
    else
        cout << "\nNot Found!\n";

}
*/