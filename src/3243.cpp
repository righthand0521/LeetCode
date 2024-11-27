#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMinDistance(vector<vector<int>>& adjList, int n) {
        int retVal = 0;

        vector<int> dp(n);
        dp[n - 1] = 0;
        for (int currentNode = n - 2; currentNode >= 0; currentNode--) {
            int minDistance = n;
            for (auto neighbor : adjList[currentNode]) {
                minDistance = min(minDistance, dp[neighbor] + 1);
            }
            dp[currentNode] = minDistance;
        }
        retVal = dp[0];

        return retVal;
    }
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> retVal;

        vector<vector<int>> adjacency(n, vector<int>(0));
        for (int i = 0; i < n - 1; i++) {
            adjacency[i].push_back(i + 1);
        }

        for (auto& road : queries) {
            int src = road[0];
            int dst = road[1];
            adjacency[src].push_back(dst);

            retVal.push_back(findMinDistance(adjacency, n));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{5, {{2, 4}, {0, 2}, {0, 4}}}, {4, {{0, 3}, {0, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, queries = [[2,4],[0,2],[0,4]]
     *  Output: [3,2,1]
     *
     *  Input: n = 4, queries = [[0,3],[0,2]]
     *  Output: [1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.shortestDistanceAfterQueries(testData[i].n, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
