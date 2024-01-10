#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/number-of-operations-to-make-network-connected/solutions/572152/wang-luo-lian-jie-bing-cha-ji-by-yexiso-1nd4/
class DisjointSet {
   private:
    vector<int> parent;
    vector<int> rank;
    int count;
    int rest;

   public:
    DisjointSet(int n) : parent(vector<int>(n)), rank(vector<int>(n)), count(n), rest(0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }
    void merge(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);

        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) {
                rank[rootx] += 1;
            }
            count--;
        } else {
            rest++;
        }
    }
    int getCount() {
        //
        return count;
    }
    int getRest() {
        //
        return rest;
    }
};

class Solution {
   public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int retVal = -1;

        int connectionsSize = connections.size();
        if (connectionsSize < n - 1) {
            return retVal;
        }

        DisjointSet ds(n);
        for (auto& connection : connections) {
            ds.merge(connection[0], connection[1]);
        }
        retVal = ds.getCount() - 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> connections;
    };
    vector<subject> testData{{4, {{0, 1}, {0, 2}, {1, 2}}},
                             {6, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}}},
                             {6, {{0, 1}, {0, 2}, {0, 3}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, connections = [[0,1],[0,2],[1,2]]
     *  Output: 1
     *
     *  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
     *  Output: 2
     *
     *  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
     *  Output: -1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", connections = [";
        for (long unsigned int j = 0; j < testData[i].connections.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].connections[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].connections[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.makeConnected(testData[i].n, testData[i].connections);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
