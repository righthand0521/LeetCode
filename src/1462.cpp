#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<bool> retVal;

        vector<vector<bool>> isPrerequisite(numCourses, vector<bool>(numCourses, false));
        for (auto edge : prerequisites) {
            isPrerequisite[edge[0]][edge[1]] = true;
        }

        for (int intermediate = 0; intermediate < numCourses; intermediate++) {
            for (int src = 0; src < numCourses; src++) {
                for (int target = 0; target < numCourses; target++) {
                    // If src -> intermediate & intermediate -> target exists then src -> target will also exist.
                    isPrerequisite[src][target] = isPrerequisite[src][target] || (isPrerequisite[src][intermediate] &&
                                                                                  isPrerequisite[intermediate][target]);
                }
            }
        }

        for (auto query : queries) {
            retVal.push_back(isPrerequisite[query[0]][query[1]]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numCourses;
        vector<vector<int>> prerequisites;
        vector<vector<int>> queries;
    };
    vector<subject> testData{
        {2, {{1, 0}}, {{0, 1}, {1, 0}}}, {2, {}, {{1, 0}, {0, 1}}}, {3, {{1, 2}, {1, 0}, {2, 0}}, {{1, 0}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
     *  Output: [false,true]
     *
     *  Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
     *  Output: [false,false]
     *
     *  Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
     *  Output: [true,true]
     */

    Solution cSolution;
    vector<bool> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numCourses = " << testData[i].numCourses << ", prerequisites = [";
        for (long unsigned int j = 0; j < testData[i].prerequisites.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].prerequisites[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].prerequisites[j][k];
            }
            cout << "]";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.checkIfPrerequisite(testData[i].numCourses, testData[i].prerequisites, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << (answer[j] == true ? "true" : "false");
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
