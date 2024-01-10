#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        bool retVal = false;

        int prerequisitesSize = prerequisites.size();

        vector<int> indegree(numCourses);
        vector<vector<int>> adjacency(numCourses);
        for (int i = 0; i < prerequisitesSize; i++) {
            adjacency[prerequisites[i][0]].push_back(prerequisites[i][1]);
            indegree[prerequisites[i][1]]++;
        }

        queue<int> topologicalSortQueue;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                topologicalSortQueue.push(i);
            }
        }

        // Topological Sort Using Kahn's Algorithm
        int numOfPrerequisite = 0;
        while (topologicalSortQueue.empty() == false) {
            int prerequisite = topologicalSortQueue.front();
            topologicalSortQueue.pop();
            ++numOfPrerequisite;

            for (auto& neighbor : adjacency[prerequisite]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    topologicalSortQueue.push(neighbor);
                }
            }
        }
        retVal = (numOfPrerequisite == numCourses);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numCourses;
        vector<vector<int>> prerequisites;
    };
    vector<subject> testData{{2, {{1, 0}}}, {2, {{1, 0}, {0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numCourses = 2, prerequisites = [[1,0]]
     *  Output: true
     *
     *  Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
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

        answer = cSolution.canFinish(testData[i].numCourses, testData[i].prerequisites);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
