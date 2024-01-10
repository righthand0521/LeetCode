#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/solutions/2864715/minimum-time-to-collect-all-apples-in-a-tree/
class Solution {
   public:
    int dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& hasApple) {
        int totalTime = 0;

        int childTime = 0;
        for (auto child : adj[node]) {
            if (child == parent) {
                continue;
            }
            childTime = dfs(child, node, adj, hasApple);

            /* childTime > 0 indicates subtree of child has apples.
             * Since the root node of the subtree does not contribute to the time, even if it has an apple,
             * we have to check it independently.
             */
            if (childTime || hasApple[child]) {
                totalTime += childTime + 2;
            }
        }

        return totalTime;
    }
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        int retVal = 0;

        vector<vector<int>> adjacent(n);
        for (auto& edge : edges) {
            adjacent[edge[0]].push_back(edge[1]);
            adjacent[edge[1]].push_back(edge[0]);
        }
        retVal = dfs(0, -1, adjacent, hasApple);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        vector<bool> hasApple;
    };
    vector<subject> testData{
        {7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, {false, false, true, false, true, true, false}},
        {7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, {false, false, true, false, false, true, false}},
        {7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, {false, false, false, false, false, false, false}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", ";
        cout << "edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], ";
        cout << "hasApple = [";
        for (long unsigned int j = 0; j < testData[i].hasApple.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << (testData[i].hasApple[j] == true ? "true" : "false");
        }
        cout << "]\n";

        answer = cSolution.minTime(testData[i].n, testData[i].edges, testData[i].hasApple);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
