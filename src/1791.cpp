#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findCenter(vector<vector<int>>& edges) {
        int retVal = 0;

        int edgesSize = edges.size();

        vector<int> degreeCount(edgesSize + 2, 0);
        for (auto edge : edges) {
            degreeCount[edge[0]] += 1;
            degreeCount[edge[1]] += 1;
        }

        for (int i = 1; i <= edgesSize + 1; ++i) {
            if (degreeCount[i] == edgesSize) {
                retVal = i;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> edges;
    };
    vector<subject> testData{{{{1, 2}, {2, 3}, {4, 2}}}, {{{1, 2}, {5, 1}, {1, 3}, {1, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges = [[1,2],[2,3],[4,2]]
     *  Output: 2
     *
     *  Input: edges = [[1,2],[5,1],[1,3],[1,4]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findCenter(testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
