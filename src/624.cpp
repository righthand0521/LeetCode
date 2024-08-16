#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxDistance(vector<vector<int>>& arrays) {
        int retVal = 0;

        int arraysSize = arrays.size();

        int arraysColSize = arrays[0].size();
        int minValue = arrays[0][0];
        int maxValue = arrays[0][arraysColSize - 1];
        for (int i = 1; i < arraysSize; ++i) {
            arraysColSize = arrays[i].size();
            int diff1 = abs(arrays[i][arraysColSize - 1] - minValue);
            int diff2 = abs(maxValue - arrays[i][0]);
            retVal = max(retVal, max(diff1, diff2));

            minValue = min(minValue, arrays[i][0]);
            maxValue = max(maxValue, arrays[i][arraysColSize - 1]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> arrays;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5}, {1, 2, 3}}}, {{{1}, {1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arrays = [[1,2,3],[4,5],[1,2,3]]
     *  Output: 4
     *
     *  Input: arrays = [[1],[1]]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arrays = [";
        for (long unsigned int j = 0; j < testData[i].arrays.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].arrays[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].arrays[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxDistance(testData[i].arrays);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
