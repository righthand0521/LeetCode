#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int dfs(int node, int parent, int depth, const vector<vector<int>>& children, vector<int>& color) {
        int retVal = 1 - depth % 2;

        color[node] = depth % 2;
        for (int child : children[node]) {
            if (child == parent) {
                continue;
            }
            retVal += dfs(child, node, depth + 1, children, color);
        }

        return retVal;
    }
    vector<int> build(const vector<vector<int>>& edges, vector<int>& color) {
        vector<int> retVal;

        int edgesSize = edges.size() + 1;
        vector<vector<int>> children(edgesSize);
        for (const auto& edge : edges) {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }
        int res = dfs(0, -1, 0, children, color);
        retVal = {res, edgesSize - res};

        return retVal;
    }

   public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        vector<int> retVal;

        int edges1Size = edges1.size() + 1;
        vector<int> color1(edges1Size);
        vector<int> count1 = build(edges1, color1);

        int edges2Size = edges2.size() + 1;
        vector<int> color2(edges2Size);
        vector<int> count2 = build(edges2, color2);

        retVal.resize(edges1.size() + 1);
        for (int i = 0; i < edges1Size; i++) {
            retVal[i] = count1[color1[i]] + max(count2[0], count2[1]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> edges1;
        vector<vector<int>> edges2;
    };
    vector<subject> testData{
        {{{0, 1}, {0, 2}, {2, 3}, {2, 4}}, {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}}},
        {{{0, 1}, {0, 2}, {0, 3}, {0, 4}}, {{0, 1}, {1, 2}, {2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
     *  Output: [8,7,7,8,8]
     *
     *  Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]
     *  Output: [3,6,6,6,6]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: edges1 = [";
        for (long unsigned int j = 0; j < testData[i].edges1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges1[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges1[j][k];
            }
            cout << "]";
        }
        cout << "], edges2 = [";
        for (long unsigned int j = 0; j < testData[i].edges2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges2[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges2[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxTargetNodes(testData[i].edges1, testData[i].edges2);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
