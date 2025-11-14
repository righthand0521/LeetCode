#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> retVal;

        vector diff(n + 1, vector<int>(n + 1));
        for (const auto& query : queries) {
            int row1 = query[0];
            int col1 = query[1];
            int row2 = query[2];
            int col2 = query[3];
            diff[row1][col1] += 1;
            diff[row2 + 1][col1] -= 1;
            diff[row1][col2 + 1] -= 1;
            diff[row2 + 1][col2 + 1] += 1;
        }

        retVal = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x1 = (i == 0) ? (0) : (retVal[i - 1][j]);
                int x2 = (j == 0) ? (0) : (retVal[i][j - 1]);
                int x3 = ((i == 0) || (j == 0)) ? (0) : (retVal[i - 1][j - 1]);
                retVal[i][j] = diff[i][j] + x1 + x2 - x3;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{3, {{1, 1, 2, 2}, {0, 0, 1, 1}}}, {2, {{0, 0, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
     *  Output: [[1,1,0],[1,2,1],[0,1,1]]
     *
     *  Input: n = 2, queries = [[0,0,1,1]]
     *  Output: [[1,1],[1,1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.rangeAddQueries(testData[i].n, testData[i].queries);
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
