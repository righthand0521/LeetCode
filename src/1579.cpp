#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class UnionFind {
   public:
    int n;
    int setCount;
    vector<int> parent;
    vector<int> size;

    UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
        //
        iota(parent.begin(), parent.end(), 0);
    }
    int findset(int x) {
        int retVal = 0;

        if (parent[x] != x) {
            parent[x] = findset(parent[x]);
        }
        retVal = parent[x];

        return retVal;
    }
    bool unite(int x, int y) {
        bool retVal = false;

        x = findset(x);
        y = findset(y);
        if (x == y) {
            return retVal;
        }

        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        retVal = true;

        return retVal;
    }
    bool connected(int x, int y) {
        bool retVal = false;

        x = findset(x);
        y = findset(y);
        if (x == y) {
            retVal = true;
        }

        return retVal;
    }
};

class Solution {
   public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int retVal = 0;

        UnionFind ufa(n);
        UnionFind ufb(n);

        for (auto& edge : edges) {
            --edge[1];
            --edge[2];
        }

        for (const auto& edge : edges) {
            if (edge[0] == 3) {
                if (!ufa.unite(edge[1], edge[2])) {
                    ++retVal;
                } else {
                    ufb.unite(edge[1], edge[2]);
                }
            }
        }

        for (const auto& edge : edges) {
            if (edge[0] == 1) {
                if (!ufa.unite(edge[1], edge[2])) {
                    ++retVal;
                }
            } else if (edge[0] == 2) {
                if (!ufb.unite(edge[1], edge[2])) {
                    ++retVal;
                }
            }
        }

        if (ufa.setCount != 1 || ufb.setCount != 1) {
            retVal = -1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{4, {{3, 1, 2}, {3, 2, 3}, {1, 1, 3}, {1, 2, 4}, {1, 1, 2}, {2, 3, 4}}},
                             {4, {{3, 1, 2}, {3, 2, 3}, {1, 1, 4}, {2, 1, 4}}},
                             {4, {{3, 2, 3}, {1, 1, 2}, {2, 3, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
     *  Output: 2
     *
     *  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
     *  Output: 0
     *
     *  Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
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

        answer = cSolution.maxNumEdgesToRemove(testData[i].n, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
