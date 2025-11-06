#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

class DSU {
   public:
    vector<int> parent;

    DSU(int size) {
        parent.resize(size);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        int retVal = x;

        if (parent[x] != x) {
            parent[x] = find(parent[x]);
            retVal = parent[x];
        }

        return retVal;
    }
    void join(int u, int v) {
        //
        parent[find(v)] = find(u);
    }
};
class Solution {
   public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        vector<int> retVal;

        DSU dsu(c + 1);
        for (auto& p : connections) {
            dsu.join(p[0], p[1]);
        }

        vector<bool> online(c + 1, true);
        vector<int> offlineCounts(c + 1, 0);
        for (auto& q : queries) {
            int op = q[0], x = q[1];
            if (op == 2) {
                online[x] = false;
                offlineCounts[x]++;
            }
        }

        unordered_map<int, int> minimumOnlineStations;
        for (int i = 1; i <= c; i++) {
            int root = dsu.find(i);
            if (!minimumOnlineStations.count(root)) {
                minimumOnlineStations[root] = -1;
            }

            int station = minimumOnlineStations[root];
            if (online[i]) {
                if (station == -1 || station > i) {
                    minimumOnlineStations[root] = i;
                }
            }
        }

        for (int i = (int)queries.size() - 1; i >= 0; i--) {
            int op = queries[i][0], x = queries[i][1];
            int root = dsu.find(x);
            int station = minimumOnlineStations[root];

            if (op == 1) {
                if (online[x]) {
                    retVal.push_back(x);
                } else {
                    retVal.push_back(station);
                }
            }

            if (op == 2) {
                if (offlineCounts[x] > 1) {
                    offlineCounts[x]--;
                } else {
                    online[x] = true;
                    if (station == -1 || station > x) {
                        minimumOnlineStations[root] = x;
                    }
                }
            }
        }

        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int c;
        vector<vector<int>> connections;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{5, {{1, 2}, {2, 3}, {3, 4}, {4, 5}}, {{1, 3}, {2, 1}, {1, 1}, {2, 2}, {1, 2}}},
                             {3, {}, {{1, 1}, {2, 1}, {1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]
     *  Output: [3,2,3]
     *
     *  Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]
     *  Output: [1,-1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: c = " << testData[i].c << ", connections = [";
        for (long unsigned int j = 0; j < testData[i].connections.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].connections[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].connections[j][k];
            }
            cout << "]";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.processQueries(testData[i].c, testData[i].connections, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
