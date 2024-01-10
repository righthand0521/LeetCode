#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        int retVal = 0;

        unordered_map<int, vector<int>> graph;
        vector<int> indegree(n, 0);
        for (vector<int>& edge : relations) {
            int x = edge[0] - 1;
            int y = edge[1] - 1;
            graph[x].push_back(y);
            indegree[y]++;
        }

        queue<int> topologicalSortQueue;
        vector<int> maxTime(n, 0);
        for (int node = 0; node < n; node++) {
            if (indegree[node] == 0) {
                topologicalSortQueue.push(node);
                maxTime[node] = time[node];
            }
        }

        // Topological Sort Using Kahn's Algorithm
        while (topologicalSortQueue.empty() == false) {
            int node = topologicalSortQueue.front();
            topologicalSortQueue.pop();
            for (int neighbor : graph[node]) {
                maxTime[neighbor] = max(maxTime[neighbor], maxTime[node] + time[neighbor]);
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    topologicalSortQueue.push(neighbor);
                }
            }
        }

        for (int node = 0; node < n; node++) {
            retVal = max(retVal, maxTime[node]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> relations;
        vector<int> time;
    };
    vector<subject> testData{
        {3, {{1, 3}, {2, 3}}, {3, 2, 5}}, {5, {{1, 5}, {2, 5}, {3, 5}, {3, 4}, {4, 5}}, {1, 2, 3, 4, 5}}, {1, {}, {1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
     *  Output: 8
     *
     *  Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
     *  Output: 12
     *
     *  Input: n = 1, relations = [], time = [1]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", relations = [";
        for (long unsigned int j = 0; j < testData[i].relations.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].relations[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].relations[j][k];
            }
            cout << "]";
        }
        cout << "], time = [";
        for (long unsigned int j = 0; j < testData[i].time.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].time[j];
        }
        cout << "]\n";

        answer = cSolution.minimumTime(testData[i].n, testData[i].relations, testData[i].time);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
