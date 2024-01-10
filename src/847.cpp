#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
   public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int retVal = 0;

        int graphSize = graph.size();

        queue<tuple<int, int, int>> bfsQueue;
        vector<vector<int>> visited(graphSize, vector<int>(1 << graphSize));
        for (int i = 0; i < graphSize; ++i) {
            bfsQueue.emplace(i, 1 << i, 0);
            visited[i][1 << i] = true;
        }

        while (bfsQueue.empty() == false) {
            auto [vertex, maskVertex, distance] = bfsQueue.front();
            bfsQueue.pop();
            if (maskVertex == (1 << graphSize) - 1) {
                retVal = distance;
                break;
            }

            for (int neighbor : graph[vertex]) {
                int maskNeighbor = maskVertex | (1 << neighbor);
                if (visited[neighbor][maskNeighbor] == false) {
                    bfsQueue.emplace(neighbor, maskNeighbor, distance + 1);
                    visited[neighbor][maskNeighbor] = true;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> graph;
    };
    vector<subject> testData{{{{1, 2, 3}, {0}, {0}, {0}}}, {{{1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: graph = [[1,2,3],[0],[0],[0]]
     *  Output: 4
     *
     *  Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
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

        answer = cSolution.shortestPathLength(testData[i].graph);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
