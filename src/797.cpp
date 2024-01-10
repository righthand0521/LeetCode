#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(vector<vector<int>>& graph, vector<vector<int>>& answer, vector<int>& stk, int x, int n) {
        if (x == n) {
            answer.emplace_back(stk);
            return;
        }

        for (auto& y : graph[x]) {
            stk.emplace_back(y);
            dfs(graph, answer, stk, y, n);
            stk.pop_back();
        }
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> retVal;

        int graphSize = graph.size();
        vector<int> stk;
        stk.emplace_back(0);
        dfs(graph, retVal, stk, 0, graphSize - 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> graph;
    };
    vector<subject> testData{{{{1, 2}, {3}, {3}, {}}}, {{{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: graph = [[1,2],[3],[3],[]]
     *  Output: [[0,1,3],[0,2,3]]
     *
     *  Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
     *  Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.allPathsSourceTarget(testData[i].graph);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
