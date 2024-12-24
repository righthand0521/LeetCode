#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> buildAdjList(int size, vector<vector<int>>& edges) {
        vector<vector<int>> retVal(size);

        for (auto& edge : edges) {
            retVal[edge[0]].push_back(edge[1]);
            retVal[edge[1]].push_back(edge[0]);
        }

        return retVal;
    };

    pair<int, int> findDiameter(vector<vector<int>>& adjList, int node, int parent) {
        pair<int, int> retVal = {0, 0};

        int maxDepth1 = 0;
        int maxDepth2 = 0;
        int diameter = 0;
        for (int neighbor : adjList[node]) {
            // Skip the parent to avoid cycles
            if (neighbor == parent) {
                continue;
            }

            // Recursively calculate the diameter and depth of the neighbor's subtree
            auto [childDiameter, depth] = findDiameter(adjList, neighbor, node);

            // Update the maximum diameter of the subtree
            diameter = max(diameter, childDiameter);

            // Increment the depth to include the edge to this neighbor
            depth++;

            // Update the two largest depths from the current node
            if (depth > maxDepth1) {
                maxDepth2 = maxDepth1;
                maxDepth1 = depth;
            } else if (depth > maxDepth2) {
                maxDepth2 = depth;
            }
        }

        // Update the diameter to include the path through the current node
        diameter = max(diameter, maxDepth1 + maxDepth2);

        retVal = {diameter, maxDepth1};

        return retVal;
    }

   public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int retVal = 0;

        int edges1Size = edges1.size() + 1;
        vector<vector<int>> adjList1 = buildAdjList(edges1Size, edges1);
        int diameter1 = findDiameter(adjList1, 0, -1).first;

        int edges2Size = edges2.size() + 1;
        vector<vector<int>> adjList2 = buildAdjList(edges2Size, edges2);
        int diameter2 = findDiameter(adjList2, 0, -1).first;

        int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

        retVal = max({diameter1, diameter2, combinedDiameter});

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> edges1;
        vector<vector<int>> edges2;
    };
    vector<subject> testData{{{{0, 1}, {0, 2}, {0, 3}}, {{0, 1}}},
                             {{{0, 1}, {0, 2}, {0, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}},
                              {{0, 1}, {0, 2}, {0, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
     *  Output: 3
     *
     *  Input: edges1=[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2=[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
     *  Output: 5
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: edges1 = [";
        for (long unsigned int j = 0; j < testData[i].edges1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges1[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges1[j][k];
            }
            cout << "]";
        }
        cout << "], edges2 = [";
        for (long unsigned int j = 0; j < testData[i].edges2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges2[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges2[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumDiameterAfterMerge(testData[i].edges1, testData[i].edges2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
