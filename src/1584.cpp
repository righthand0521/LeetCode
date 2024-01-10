#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class DisjointSetUnion {
   private:
    vector<int> f;
    vector<int> rank;
    int n;

   public:
    DisjointSetUnion(int _n) {
        n = _n;
        rank.resize(n, 1);
        f.resize(n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
        }
    }
    int find(int x) {
        //
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    int unionSet(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            return false;
        }

        if (rank[fx] < rank[fy]) {
            swap(fx, fy);
        }
        rank[fx] += rank[fy];
        f[fy] = fx;
        return true;
    }
};

class Solution {
   private:
    struct Edge {
        int len;
        int x;
        int y;
        Edge(int len, int x, int y) : len(len), x(x), y(y) {}
    };

   public:
    int distance(vector<vector<int>>& points, int x, int y) {
        int retVal = 0;

        retVal = abs(points[x][0] - points[y][0]) + abs(points[x][1] - points[y][1]);

        return retVal;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int retVal = 0;

        int pointsSize = points.size();

        // Kruskal's algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
        DisjointSetUnion dsu(pointsSize);
        vector<Edge> edges;
        for (int i = 0; i < pointsSize; i++) {
            for (int j = i + 1; j < pointsSize; j++) {
                edges.emplace_back(distance(points, i, j), i, j);
            }
        }
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) -> int { return a.len < b.len; });

        int num = 1;
        for (auto& [len, x, y] : edges) {
            if (dsu.unionSet(x, y)) {
                retVal += len;
                num++;
                if (num == pointsSize) {
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}}}, {{{3, 12}, {-2, 5}, {-4, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
     *  Output: 20
     *
     *  Input: points = [[3,12],[-2,5],[-4,1]]
     *  Output: 18
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: points = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minCostConnectPoints(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
