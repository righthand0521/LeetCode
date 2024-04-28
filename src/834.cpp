#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(int children, int parent, int depth, vector<vector<int>>& adjacency, vector<int>& distances,
             vector<int>& retVal) {
        retVal[0] += depth;
        for (auto& neighnor : adjacency[children]) {
            if (neighnor != parent) {
                dfs(neighnor, children, depth + 1, adjacency, distances, retVal);
                distances[children] += distances[neighnor];
            }
        }
    }
    void reroot(int children, int parent, vector<vector<int>>& adjacency, vector<int>& distances, int vertex,
                vector<int>& retVal) {
        for (auto& neighnor : adjacency[children]) {
            if (neighnor != parent) {
                retVal[neighnor] = retVal[children] + vertex - 2 * distances[neighnor];
                reroot(neighnor, children, adjacency, distances, vertex, retVal);
            }
        }
    }
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<int> retVal(n, 0);

        vector<vector<int>> adjacency(n);
        for (auto& edge : edges) {
            int src = edge[0];
            int dst = edge[1];
            adjacency[src].emplace_back(dst);
            adjacency[dst].emplace_back(src);
        }
        vector<int> distances(n, 1);

        dfs(0, -1, 0, adjacency, distances, retVal);
        reroot(0, -1, adjacency, distances, n, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{6, {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}}}, {1, {}}, {2, {{1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
     *  Output: [8,12,6,10,10,10]
     *
     *  Input: n = 1, edges = []
     *  Output: [0]
     *
     *  Input: n = 2, edges = [[1,0]]
     *  Output: [1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.sumOfDistancesInTree(testData[i].n, testData[i].edges);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
