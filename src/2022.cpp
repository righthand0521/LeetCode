#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        vector<vector<int>> retVal;

        int originalSize = original.size();
        if (originalSize != m * n) {
            return retVal;
        }
        retVal.resize(m, vector<int>(n, false));

        int originalIndex = 0;
        for (int x = 0; x < m; ++x) {
            for (int y = 0; y < n; ++y) {
                retVal[x][y] = original[originalIndex++];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> original;
        int m;
        int n;
    };
    vector<subject> testData{{{1, 2, 3, 4}, 2, 2}, {{1, 2, 3}, 1, 3}, {{1, 2}, 1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: original = [1,2,3,4], m = 2, n = 2
     *  Output: [[1,2],[3,4]]
     *
     *  Input: original = [1,2,3], m = 1, n = 3
     *  Output: [[1,2,3]]
     *
     *  Input: original = [1,2], m = 1, n = 1
     *  Output: []
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: original = [";
        for (long unsigned int j = 0; j < testData[i].original.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].original[j];
        }
        cout << "], m = " << testData[i].m << ", n = " << testData[i].n << "\n";

        answer = cSolution.construct2DArray(testData[i].original, testData[i].m, testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
