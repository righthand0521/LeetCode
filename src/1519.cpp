#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // labels is consisting of only of lowercase English letters.
    int maxNode = 26;

    vector<int> dfs(int node, int parent, vector<vector<int>>& adjacent, string& labels, vector<int>& ans) {
        // Store count of all alphabets in the subtree of the node.
        vector<int> nodeCounts(maxNode);
        nodeCounts[labels[node] - 'a'] = 1;

        for (auto& child : adjacent[node]) {
            if (child == parent) {
                continue;
            }

            vector<int> childCounts = dfs(child, node, adjacent, labels, ans);

            // Add frequencies of the child node in the parent node's frequency array.
            for (int i = 0; i < maxNode; i++) {
                nodeCounts[i] += childCounts[i];
            }
        }
        ans[node] = nodeCounts[labels[node] - 'a'];

        return nodeCounts;
    }

    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<int> retVal(n, 0);

        vector<vector<int>> adjacent(n);
        for (auto& edge : edges) {
            adjacent[edge[0]].push_back(edge[1]);
            adjacent[edge[1]].push_back(edge[0]);
        }

        dfs(0, -1, adjacent, labels, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        string labels;
    };
    vector<subject> testData{{7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, "abaedcd"},
                             {4, {{0, 1}, {1, 2}, {0, 3}}, "bbbb"},
                             {5, {{0, 1}, {0, 2}, {1, 3}, {0, 4}}, "aabab"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", ";
        cout << "edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], ";
        cout << "labels = \"" << testData[i].labels << "\"\n";

        answer = cSolution.countSubTrees(testData[i].n, testData[i].edges, testData[i].labels);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
