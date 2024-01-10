#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double champagneTower(int poured, int query_row, int query_glass) {
        double retVal = 0;

        vector<double> glass;
        glass.emplace_back(poured);
        for (int row = 0; row < query_row; ++row) {
            int glassSize = glass.size();
            vector<double> nextGlass(glassSize + 1, 0);
            for (int col = 0; col < glassSize; ++col) {
                double volume = glass[col];
                if (volume <= 1) {
                    continue;
                }
                nextGlass[col] += (volume - 1) / 2;
                nextGlass[col + 1] += (volume - 1) / 2;
            }
            glass = nextGlass;
        }
        retVal = min(1.0, glass[query_glass]);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int poured;
        int query_row;
        int query_glass;
    };
    vector<subject> testData{{1, 1, 1}, {2, 1, 1}, {100000009, 33, 17}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: poured = 1, query_row = 1, query_glass = 1
     *  Output: 0.00000
     *
     *  Input: poured = 2, query_row = 1, query_glass = 1
     *  Output: 0.50000
     *
     *  Input: poured = 100000009, query_row = 33, query_glass = 17
     *  Output: 1.00000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: poured = " << testData[i].poured << ", query_row = " << testData[i].query_row
             << ", query_glass = " << testData[i].query_glass << "\n";

        answer = cSolution.champagneTower(testData[i].poured, testData[i].query_row, testData[i].query_glass);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
