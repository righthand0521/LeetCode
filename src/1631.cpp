#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
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
        //
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }
    bool unite(int x, int y) {
        x = findset(x);
        y = findset(y);
        if (x == y) {
            return false;
        }

        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;

        return true;
    }
    bool connected(int x, int y) {
        x = findset(x);
        y = findset(y);

        return x == y;
    }
};

class Solution {
   public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int retVal = 0;

        int rows = heights.size();
        int columns = heights[0].size();  // 1 <= rows, columns <= 100

        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                int id = i * columns + j;
                if (i > 0) {
                    edges.emplace_back(id - columns, id, abs(heights[i][j] - heights[i - 1][j]));
                }
                if (j > 0) {
                    edges.emplace_back(id - 1, id, abs(heights[i][j] - heights[i][j - 1]));
                }
            }
        }
        sort(edges.begin(), edges.end(), [](const auto& e1, const auto& e2) {
            auto&& [x1, y1, v1] = e1;
            auto&& [x2, y2, v2] = e2;
            return v1 < v2;
        });

        UnionFind uf(rows * columns);
        for (auto& [x, y, v] : edges) {
            uf.unite(x, y);
            if (uf.connected(0, rows * columns - 1)) {
                retVal = v;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> heights;
    };
    vector<subject> testData{{{{1, 2, 2}, {3, 8, 2}, {5, 3, 5}}},
                             {{{1, 2, 3}, {3, 8, 4}, {5, 3, 5}}},
                             {{{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
     *  Output: 2
     *
     *  Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
     *  Output: 1
     *
     *  Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].heights[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].heights[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumEffortPath(testData[i].heights);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
