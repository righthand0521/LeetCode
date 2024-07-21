#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    // Code to find the topologically sorted sequence using Kahn's algorithm.
    vector<int> topoSort(vector<vector<int>>& edges, int n) {
        vector<int> retVal;

        // Create an adjacency list to store the edges.
        vector<vector<int>> adjacency(n + 1);
        vector<int> degree(n + 1);
        for (auto edge : edges) {
            adjacency[edge[0]].emplace_back(edge[1]);
            degree[edge[1]]++;
        }

        // Push all integers with in-degree 0 in the queue.
        queue<int> degreeQueue;
        for (int i = 1; i <= n; i++) {
            if (degree[i] == 0) {
                degreeQueue.push(i);
            }
        }
        while (degreeQueue.empty() == false) {
            int order = degreeQueue.front();
            degreeQueue.pop();
            retVal.emplace_back(order);
            for (auto neighbor : adjacency[order]) {
                degree[neighbor]--;
                if (degree[neighbor] == 0) {
                    degreeQueue.push(neighbor);
                }
            }
            n--;
        }

        // If we have not visited all integers, return empty array.
        if (n != 0) {
            retVal.clear();
        }

        return retVal;
    }

   public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> retVal(k, vector<int>(k, 0));

        // Store the topologically sorted sequences.
        vector<int> orderRows = topoSort(rowConditions, k);
        vector<int> orderColumns = topoSort(colConditions, k);

        // If no topological sort exists, return empty array.
        if ((orderRows.empty() == true) or (orderColumns.empty() == true)) {
            retVal.clear();
            return retVal;
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (orderRows[i] == orderColumns[j]) {
                    retVal[i][j] = orderRows[i];
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int k;
        vector<vector<int>> rowConditions;
        vector<vector<int>> colConditions;
    };
    vector<subject> testData{{3, {{1, 2}, {3, 2}}, {{2, 1}, {3, 2}}}, {3, {{1, 2}, {2, 3}, {3, 1}, {2, 3}}, {{2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
     *  Output: [[3,0,0],[0,0,1],[0,2,0]]
     *
     *  Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]], colConditions = [[2,1]]
     *  Output: []
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << ", rowConditions = [";
        for (long unsigned int j = 0; j < testData[i].rowConditions.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].rowConditions[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].rowConditions[j][k];
            }
            cout << "]";
        }
        cout << "], colConditions = [";
        for (long unsigned int j = 0; j < testData[i].colConditions.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].colConditions[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].colConditions[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.buildMatrix(testData[i].k, testData[i].rowConditions, testData[i].colConditions);
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
