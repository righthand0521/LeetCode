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
        int retVal = x;

        if (parent[x] == x) {
            return retVal;
        }
        parent[x] = findset(parent[x]);
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
        retVal = (x == y);

        return retVal;
    }
};

class Solution {
   public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> retVal(2);

        int edgesSize = edges.size();
        for (int i = 0; i < edgesSize; ++i) {
            edges[i].push_back(i);
        }
        sort(edges.begin(), edges.end(), [](const auto& u, const auto& v) {
            //
            return u[2] < v[2];
        });

        UnionFind uf_std(n);
        int value = 0;
        for (int i = 0; i < edgesSize; ++i) {
            if (uf_std.unite(edges[i][0], edges[i][1]) == true) {
                value += edges[i][2];
            }
        }

        for (int i = 0; i < edgesSize; ++i) {
            UnionFind uf(n);
            int v = 0;

            for (int j = 0; j < edgesSize; ++j) {
                if ((i != j) && (uf.unite(edges[j][0], edges[j][1]) == true)) {
                    v += edges[j][2];
                }
            }

            if ((uf.setCount != 1) || ((uf.setCount == 1) && (v > value))) {
                retVal[0].push_back(edges[i][3]);
                continue;
            }

            uf = UnionFind(n);
            uf.unite(edges[i][0], edges[i][1]);
            v = edges[i][2];

            for (int j = 0; j < edgesSize; ++j) {
                if ((i != j) && (uf.unite(edges[j][0], edges[j][1]) == true)) {
                    v += edges[j][2];
                }
            }

            if (v == value) {
                retVal[1].push_back(edges[i][3]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{5, {{0, 1, 1}, {1, 2, 1}, {2, 3, 2}, {0, 3, 2}, {0, 4, 3}, {3, 4, 3}, {1, 4, 6}}},
                             {4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
     *  Output: [[0,1],[2,3,4,5]]
     *
     *  Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
     *  Output: [[],[0,1,2,3]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.findCriticalAndPseudoCriticalEdges(testData[i].n, testData[i].edges);
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
