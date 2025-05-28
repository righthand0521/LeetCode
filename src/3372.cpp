#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int dfs(int node, int parent, const vector<vector<int>>& children, int k) {
        int retVal = 0;

        if (k < 0) {
            return retVal;
        }

        retVal = 1;
        for (int child : children[node]) {
            if (child == parent) {
                continue;
            }
            retVal += dfs(child, node, children, k - 1);
        }

        return retVal;
    }
    vector<int> build(const vector<vector<int>>& edges, int k) {
        vector<int> retVal;

        int edgesSize = edges.size() + 1;
        vector<vector<int>> children(edgesSize);
        for (const auto& edge : edges) {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }

        retVal.resize(edgesSize);
        for (int i = 0; i < edgesSize; i++) {
            retVal[i] = dfs(i, -1, children, k);
        }

        return retVal;
    }

   public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        vector<int> retVal;

        vector<int> count1 = build(edges1, k);
        vector<int> count2 = build(edges2, k - 1);
        int maxCount2 = *max_element(count2.begin(), count2.end());

        int edges1Size = edges1.size() + 1;
        retVal.resize(edges1Size);
        for (int i = 0; i < edges1Size; i++) {
            retVal[i] = count1[i] + maxCount2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> edges1;
        vector<vector<int>> edges2;
        int k;
    };
    vector<subject> testData{
        {{{0, 1}, {0, 2}, {2, 3}, {2, 4}}, {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}}, 2},
        {{{0, 1}, {0, 2}, {0, 3}, {0, 4}}, {{0, 1}, {1, 2}, {2, 3}}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
     *  Output: [9,7,9,8,8]
     *
     *  Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1
     *  Output: [6,3,3,3,3]
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
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxTargetNodes(testData[i].edges1, testData[i].edges2, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
