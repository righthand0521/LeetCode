#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findChampion(int n, vector<vector<int>>& edges) {
        int retVal = -1;

        vector<int> indegree(n, 0);
        for (auto edge : edges) {
            indegree[edge[1]] += 1;
        }

        for (int i = 0; i < n; ++i) {
            if (indegree[i] != 0) {
                continue;
            }

            if (retVal == -1) {
                retVal = i;
            } else {
                retVal = -1;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{3, {{0, 1}, {1, 2}}}, {4, {{0, 2}, {1, 3}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, edges = [[0,1],[1,2]]
     *  Output: 0
     *
     *  Input: n = 4, edges = [[0,2],[1,3],[1,2]]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findChampion(testData[i].n, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
