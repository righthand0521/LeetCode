#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
#define DFS (1)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    int dfs(int headID, unordered_map<int, vector<int>>& adjacent, vector<int>& informTime) {
        int retVal = 0;

        for (auto neighbor : adjacent[headID]) {
            retVal = max(retVal, dfs(neighbor, adjacent, informTime));
        }
        retVal += informTime[headID];

        return retVal;
    }
    int bfs(int headID, unordered_map<int, vector<int>>& adjacent, vector<int>& informTime) {
        int retVal = 0;

        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(headID, 0);

        while (bfsQueue.empty() == false) {
            auto node = bfsQueue.front();
            int id = node.first;
            int minutes = node.second;
            bfsQueue.pop();

            if (adjacent[id].size() == 0) {
                retVal = max(retVal, minutes);
                continue;
            }

            for (auto neighbor : adjacent[id]) {
                bfsQueue.emplace(neighbor, minutes + informTime[id]);
            }
        }

        return retVal;
    }
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        int retVal = 0;

        //
        unordered_map<int, vector<int>> adjacent;
        for (int employee = 0; employee < n; ++employee) {
            adjacent[manager[employee]].emplace_back(employee);
        }
#if 0
        for (auto employee : adjacent) {
            cout << employee.first << ": ";
            for (auto neighbor : employee.second) {
                cout << neighbor << " ";
            }
            cout << "\n";
        }
#endif

        //
#if (DFS)
        retVal = dfs(headID, adjacent, informTime);
#elif (BFS)
        retVal = bfs(headID, adjacent, informTime);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int headID;
        vector<int> manager;
        vector<int> informTime;
    };
    vector<subject> testData{{1, 0, {-1}, {0}}, {6, 2, {2, 2, -1, 2, 2, 2}, {0, 0, 1, 0, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1, headID = 0, manager = [-1], informTime = [0]
     *  Output: 0
     *
     *  Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", headID = " << testData[i].headID << ", manager = [";
        for (long unsigned int j = 0; j < testData[i].manager.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].manager[j];
        }
        cout << "], informTime = [";
        for (long unsigned int j = 0; j < testData[i].informTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].informTime[j];
        }
        cout << "]\n";

        answer = cSolution.numOfMinutes(testData[i].n, testData[i].headID, testData[i].manager, testData[i].informTime);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
