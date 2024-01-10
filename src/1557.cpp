#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> retVal;

        vector<int> incoming(n, 0);
        for (auto edge : edges) {
            ++incoming[edge[1]];
        }

        for (int i = 0; i < n; ++i) {
            if (incoming[i] == 0) {
                retVal.emplace_back(i);
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
    vector<subject> testData{{6, {{0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}}},
                             {5, {{0, 1}, {2, 1}, {3, 1}, {1, 4}, {2, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
     *  Output: [0,3]
     *
     *  Input: n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
     *  Output: [0,2,3]
     */

    Solution cSolution;
    vector<int> answer;
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

        answer = cSolution.findSmallestSetOfVertices(testData[i].n, testData[i].edges);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
