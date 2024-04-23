#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> retVal;

        if (n == 1) {
            retVal.emplace_back(0);
            return retVal;
        }

        vector<vector<int>> adjacency(n);
        vector<int> degree(n, 0);
        for (auto& edge : edges) {
            int src = edge[0];
            int dst = edge[1];
            adjacency[src].emplace_back(dst);
            adjacency[dst].emplace_back(src);
            degree[src]++;
            degree[dst]++;
        }

        queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (degree[i] == 1) {
                queue.emplace(i);
            }
        }

        int remainNodes = n;
        while (remainNodes > 2) {
            int queueSize = queue.size();
            remainNodes -= queueSize;
            for (int i = 0; i < queueSize; i++) {
                int node = queue.front();
                queue.pop();
                for (auto& vertex : adjacency[node]) {
                    --degree[vertex];
                    if (degree[vertex] == 1) {
                        queue.emplace(vertex);
                    }
                }
            }
        }
        while (queue.empty() == false) {
            retVal.emplace_back(queue.front());
            queue.pop();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{4, {{1, 0}, {1, 2}, {1, 3}}}, {6, {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, edges = [[1,0],[1,2],[1,3]]
     *  Output: [1]
     *
     *  Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
     *  Output: [3,4]
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

        answer = cSolution.findMinHeightTrees(testData[i].n, testData[i].edges);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
