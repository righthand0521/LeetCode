#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
#define DFS (1)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "DFS\n";
#elif (BFS)
        cout << "BFS\n";
#endif
    }

    bool dfs(int node, vector<vector<int>>& graph, unordered_map<int, int>& color) {
        bool retVal = true;

        for (auto neighbor : graph[node]) {
            if (color.find(neighbor) != color.end()) {
                if (color[neighbor] == color[node]) {
                    retVal = false;
                    break;
                }
            } else {
                color[neighbor] = 1 - color[node];
                retVal = dfs(neighbor, graph, color);
                if (retVal == false) {
                    break;
                }
            }
        }

        return retVal;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        bool retVal = true;

#if (DFS)
#elif (BFS)
        queue<int> bfsQueue;
#endif

        unordered_map<int, int> color;
        int graphSize = graph.size();
        for (int node = 0; node < graphSize; ++node) {
            if (color.find(node) != color.end()) {
                continue;
            }
            color[node] = 0;

#if (DFS)
            retVal = dfs(node, graph, color);
            if (retVal == false) {
                break;
            }
#elif (BFS)
            bfsQueue.push(node);
            while (bfsQueue.empty() == false) {
                auto current = bfsQueue.front();
                bfsQueue.pop();

                for (auto& neighbor : graph[current]) {
                    if (color.find(neighbor) != color.end()) {
                        if (color[neighbor] == color[current]) {
                            retVal = false;
                            return retVal;
                        }
                    } else {
                        color[neighbor] = 1 - color[current];
                        bfsQueue.push(neighbor);
                    }
                }
            }
#endif
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> graph;
    };
    vector<subject> testData{{{{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}}}, {{{1, 3}, {0, 2}, {1, 3}, {0, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
     *  Output: false
     *
     *  Input: graph = [[1,3],[0,2],[1,3],[0,2]]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: graph = [";
        for (long unsigned int j = 0; j < testData[i].graph.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].graph[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].graph[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.isBipartite(testData[i].graph);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
