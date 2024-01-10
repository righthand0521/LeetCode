#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
#define BREADTH_FIRST_SEARCH (1)
   public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<int> pRetVal(n, -1);

        // redEdges: 0, blueEdges: 1.
        vector<vector<pair<int, int>>> adjacent(n);
        for (auto& redEdge : redEdges) {
            adjacent[redEdge[0]].push_back({redEdge[1], 0});
        }
        for (auto& blueEdge : blueEdges) {
            adjacent[blueEdge[0]].push_back(make_pair(blueEdge[1], 1));
        }

        vector<vector<bool>> visit(n, vector<bool>(2));

        queue<vector<int>> bfs;
        bfs.push({0, 0, -1});  // Start with node 0, with number of steps as 0 and undefined color -1.

        visit[0][0] = true;
        visit[0][1] = true;
        pRetVal[0] = 0;
        while (bfs.empty() == false) {
            auto element = bfs.front();
            int node = element[0];
            int steps = element[1];
            int prevColor = element[2];
            bfs.pop();

            for (auto& [neighbor, color] : adjacent[node]) {
                if (visit[neighbor][color] == true) {
                    continue;
                }

                if (color == prevColor) {
                    continue;
                }

                visit[neighbor][color] = true;
                bfs.push({neighbor, 1 + steps, color});
                if (pRetVal[neighbor] == -1) {
                    pRetVal[neighbor] = 1 + steps;
                }
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> redEdges;
        vector<vector<int>> blueEdges;
    };
    vector<subject> testData{{3, {{0, 1}, {1, 2}}, {}},
                             {3, {{0, 1}}, {{2, 1}}},
                             {3, {{1, 0}}, {{2, 1}}},
                             {3, {{0, 1}}, {{1, 2}}},
                             {3, {{0, 1}, {0, 2}}, {{1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
     *  Output: [0,1,-1]
     *
     *  Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
     *  Output: [0,1,-1]
     *
     *  n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
     *  [0,-1,-1]
     *
     *  n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
     *  [0,1,2]
     *
     *  n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
     *  [0,1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", redEdges = [";
        for (long unsigned int j = 0; j < testData[i].redEdges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].redEdges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].redEdges[j][k];
            }
            cout << "]";
        }
        cout << "], blueEdges = [";
        for (long unsigned int j = 0; j < testData[i].blueEdges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].blueEdges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].blueEdges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.shortestAlternatingPaths(testData[i].n, testData[i].redEdges, testData[i].blueEdges);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
