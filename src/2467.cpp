#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
    int dfs(int sourceNode, int parentNode, int time, int bob, vector<int>& amount, vector<vector<int>>& tree,
            vector<int>& distanceFromBob) {
        int retVal = 0;

        // Find the node distances from Bob
        int amountSize = amount.size();
        if (sourceNode == bob) {
            distanceFromBob[sourceNode] = 0;
        } else {
            distanceFromBob[sourceNode] = amountSize;
        }

        int maxChild = numeric_limits<int>::min();
        for (int adjacentNode : tree[sourceNode]) {
            if (adjacentNode != parentNode) {
                maxChild = max(maxChild, dfs(adjacentNode, sourceNode, time + 1, bob, amount, tree, distanceFromBob));
                distanceFromBob[sourceNode] = min(distanceFromBob[sourceNode], distanceFromBob[adjacentNode] + 1);
            }
        }

        int maxIncome = 0;
        if (distanceFromBob[sourceNode] > time) {  // Alice reaches the node first
            maxIncome += amount[sourceNode];
        } else if (distanceFromBob[sourceNode] == time) {  // Alice and Bob reach the node at the same time
            maxIncome += amount[sourceNode] / 2;
        }

        // Return max income of leaf node
        if (maxChild == numeric_limits<int>::min()) {
            retVal = maxIncome;
        } else {
            retVal = maxIncome + maxChild;
        }

        return retVal;
    }

   public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int retVal = 0;

        int amountSize = amount.size();

        vector<vector<int>> tree(amountSize, vector<int>());
        for (vector<int> edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        vector<int> distanceFromBob(amountSize);

        retVal = dfs(0, 0, 0, bob, amount, tree, distanceFromBob);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> edges;
        int bob;
        vector<int> amount;
    };
    vector<subject> testData{{{{0, 1}, {1, 2}, {1, 3}, {3, 4}}, 3, {-2, 4, 2, -4, 6}}, {{{0, 1}}, 1, {-7280, 2350}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
     *  Output: 6
     *
     *  Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
     *  Output: -7280
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << ", bob = " << testData[i].bob << "], amount = [";
        for (long unsigned int j = 0; j < testData[i].amount.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].amount[j];
        }
        cout << "]\n";

        answer = cSolution.mostProfitablePath(testData[i].edges, testData[i].bob, testData[i].amount);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
