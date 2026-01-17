#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        long long retVal = 0;

        int bottomLeftSize = bottomLeft.size();
        int maxSide = 0;
        for (int i = 0; i < bottomLeftSize; i++) {
            for (int j = i + 1; j < bottomLeftSize; j++) {
                int weight = min(topRight[i][0], topRight[j][0]) - max(bottomLeft[i][0], bottomLeft[j][0]);
                int high = min(topRight[i][1], topRight[j][1]) - max(bottomLeft[i][1], bottomLeft[j][1]);

                maxSide = max(maxSide, min(weight, high));
            }
        }
        retVal = 1LL * maxSide * maxSide;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> bottomleft;
        vector<vector<int>> topRight;
    };
    vector<subject> testData{{{{1, 1}, {2, 2}, {3, 1}}, {{3, 3}, {4, 4}, {6, 6}}},
                             {{{1, 1}, {1, 3}, {1, 5}}, {{5, 5}, {5, 7}, {5, 9}}},
                             {{{1, 1}, {2, 2}, {1, 2}}, {{3, 3}, {4, 4}, {3, 4}}},
                             {{{1, 1}, {3, 3}, {3, 1}}, {{2, 2}, {4, 4}, {4, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
     *  Output: 1
     *
     *  Input: bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
     *  Output: 4
     *
     *  Input: bottomLeft = [[1,1],[2,2],[1,2]], topRight = [[3,3],[4,4],[3,4]]
     *  Output: 1
     *
     *  Input: bottomLeft = [[1,1],[3,3],[3,1]], topRight = [[2,2],[4,4],[4,2]]
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: bottomleft = [";
        for (long unsigned int j = 0; j < testData[i].bottomleft.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].bottomleft[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].bottomleft[j][k];
            }
            cout << "]";
        }
        cout << "], topRight = [";
        for (long unsigned int j = 0; j < testData[i].topRight.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].topRight[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].topRight[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.largestSquareArea(testData[i].bottomleft, testData[i].topRight);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
