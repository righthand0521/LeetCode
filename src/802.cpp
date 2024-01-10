#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> retVal;

        int graphSize = graph.size();

        vector<int> indegree(graphSize);
        vector<vector<int>> adjacency(graphSize);
        for (int i = 0; i < graphSize; i++) {
            for (auto node : graph[i]) {
                adjacency[node].push_back(i);
                indegree[i]++;
            }
        }

        queue<int> topologicalSortQueue;
        for (int i = 0; i < graphSize; i++) {
            if (indegree[i] == 0) {
                topologicalSortQueue.push(i);
            }
        }

        // Topological Sort Using Kahn's Algorithm
        vector<bool> safe(graphSize);
        while (topologicalSortQueue.empty() == false) {
            int node = topologicalSortQueue.front();
            topologicalSortQueue.pop();
            safe[node] = true;

            for (auto& neighbor : adjacency[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    topologicalSortQueue.push(neighbor);
                }
            }
        }

        for (int i = 0; i < graphSize; i++) {
            if (safe[i] == true) {
                retVal.push_back(i);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> graph;
    };
    vector<subject> testData{{{{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}}}, {{{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
     *  Output: [2,4,5,6]
     *
     *  Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
     *  Output: [4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: graph = [";
        for (long unsigned int j = 0; j < testData[i].graph.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].graph[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].graph[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.eventualSafeNodes(testData[i].graph);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
