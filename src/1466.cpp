#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minReorder(int n, vector<vector<int>>& connections) {
        int retVal = 0;

        vector<vector<int>> adjacent(n);
        vector<vector<int>> backAdjacent(n);
        for (auto connection : connections) {
            adjacent[connection[0]].push_back(connection[1]);
            backAdjacent[connection[1]].push_back(connection[0]);
        }

        // Breadth-First Search
        queue<int> bfsQueue;
        bfsQueue.push(0);

        vector<bool> visit(n);

        while (bfsQueue.empty() == false) {
            int current = bfsQueue.front();
            bfsQueue.pop();

            visit[current] = true;

            for (auto iterator : adjacent[current]) {
                if (visit[iterator] == false) {
                    ++retVal;
                    bfsQueue.push(iterator);
                }
            }

            for (auto iterator : backAdjacent[current]) {
                if (visit[iterator] == false) {
                    bfsQueue.push(iterator);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> connections;
    };
    vector<subject> testData{
        {6, {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}}}, {5, {{1, 0}, {1, 2}, {3, 2}, {3, 4}}}, {3, {{1, 0}, {2, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
     *  Output: 3
     *
     *  Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
     *  Output: 2
     *
     *  Input: n = 3, connections = [[1,0],[2,0]]
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", connections = [";
        for (long unsigned int j = 0; j < testData[i].connections.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].connections[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].connections[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minReorder(testData[i].n, testData[i].connections);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
