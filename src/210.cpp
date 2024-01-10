#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> retVal;

        int prerequisitesSize = prerequisites.size();

        vector<int> indegree(numCourses);
        vector<vector<int>> adjacency(numCourses);
        for (int i = 0; i < prerequisitesSize; i++) {
            adjacency[prerequisites[i][1]].push_back(prerequisites[i][0]);
            indegree[prerequisites[i][0]]++;
        }

        queue<int> topologicalSortQueue;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                topologicalSortQueue.push(i);
            }
        }

        // Topological Sort Using Kahn's Algorithm
        while (topologicalSortQueue.empty() == false) {
            int prerequisite = topologicalSortQueue.front();
            topologicalSortQueue.pop();
            retVal.emplace_back(prerequisite);

            for (auto& neighbor : adjacency[prerequisite]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    topologicalSortQueue.push(neighbor);
                }
            }
        }

        int returnSize = retVal.size();
        if (returnSize != numCourses) {
            retVal.clear();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numCourses;
        vector<vector<int>> prerequisites;
    };
    vector<subject> testData{
        {2, {{1, 0}}}, {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}}, {1, {}}, {3, {{1, 0}, {1, 2}, {0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numCourses = 2, prerequisites = [[1,0]]
     *  Output: [0,1]
     *
     *  Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
     *  Output: [0,2,1,3]
     *
     *  Input: numCourses = 1, prerequisites = []
     *  Output: [0]
     *
     *  Input: numCourses = 3, prerequisites = [[1,0],[1,2],[0,1]]
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numCourses = " << testData[i].numCourses << ", prerequisites = [";
        for (long unsigned int j = 0; j < testData[i].prerequisites.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].prerequisites[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].prerequisites[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findOrder(testData[i].numCourses, testData[i].prerequisites);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
