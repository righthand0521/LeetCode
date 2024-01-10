#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
#define DFS (0)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    void dfs(int i, vector<vector<int>>& isConnected, vector<int>& visited) {
        int isConnectedSize = isConnected.size();

        for (int j = 0; j < isConnectedSize; ++j) {
            if (isConnected[i][j] == 0) {
                continue;
            } else if (find(visited.begin(), visited.end(), j) != visited.end()) {
                continue;
            } else {
                visited.emplace_back(j);
                dfs(j, isConnected, visited);
            }
        }
    }
    void bfs(int i, vector<vector<int>>& isConnected, vector<int>& visited) {
        int isConnectedSize = isConnected.size();

        visited.emplace_back(i);
        queue<int> bfsQueue;
        bfsQueue.emplace(i);
        while (bfsQueue.empty() == false) {
            auto idx = bfsQueue.front();
            bfsQueue.pop();
            for (int j = 0; j < isConnectedSize; ++j) {
                if (isConnected[idx][j] == 0) {
                    continue;
                } else if (find(visited.begin(), visited.end(), j) != visited.end()) {
                    continue;
                } else {
                    visited.emplace_back(j);
                    bfsQueue.emplace(j);
                }
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int retVal = 0;

        int isConnectedSize = isConnected.size();

        vector<int> visited;
        for (int i = 0; i < isConnectedSize; ++i) {
            if (find(visited.begin(), visited.end(), i) != visited.end()) {
                continue;
            }

#if (DFS)
            dfs(i, isConnected, visited);
#elif (BFS)
            bfs(i, isConnected, visited);
#endif

            ++retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> isConnected;
    };
    vector<subject> testData{{{{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}}, {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
     *  Output: 2
     *
     *  Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: isConnected = [";
        for (long unsigned int j = 0; j < testData[i].isConnected.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].isConnected[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].isConnected[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findCircleNum(testData[i].isConnected);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
