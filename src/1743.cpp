#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        vector<int> retVal;

        map<int, vector<int>> graph;
        for (auto& edge : adjacentPairs) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        int root = 0;
        for (auto& pair : graph) {
            if (pair.second.size() == 1) {
                root = pair.first;
                break;
            }
        }
        retVal.emplace_back(root);

        int curr = root;
        int prev = numeric_limits<int>::max();  // -10^5 <= nums[i], ui, vi <= 10^5
        while (retVal.size() < graph.size()) {
            for (int neighbor : graph[curr]) {
                if (neighbor != prev) {
                    retVal.emplace_back(neighbor);
                    prev = curr;
                    curr = neighbor;
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> adjacentPairs;
    };
    vector<subject> testData{{{{2, 1}, {3, 4}, {3, 2}}}, {{{4, -2}, {1, 4}, {-3, 1}}}, {{{100000, -100000}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: adjacentPairs = [[2,1],[3,4],[3,2]]
     *  Output: [1,2,3,4]
     *
     *  Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
     *  Output: [-2,4,1,-3]
     *
     *  Input: adjacentPairs = [[100000,-100000]]
     *  Output: [100000,-100000]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: adjacentPairs = [";
        for (long unsigned int j = 0; j < testData[i].adjacentPairs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].adjacentPairs[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].adjacentPairs[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.restoreArray(testData[i].adjacentPairs);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
