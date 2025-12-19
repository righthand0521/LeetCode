#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> retVal;

        int meetingsSize = meetings.size();
        sort(meetings.begin(), meetings.end(), [&](const auto& x, const auto& y) {
            //
            return x[2] < y[2];
        });

        vector<int> secret(n);
        secret[0] = secret[firstPerson] = true;

        unordered_set<int> vertices;
        unordered_map<int, vector<int>> edges;

        for (int i = 0; i < meetingsSize;) {
            int j = i;
            while ((j + 1 < meetingsSize) && (meetings[j + 1][2] == meetings[i][2])) {
                ++j;
            }

            vertices.clear();
            edges.clear();
            for (int k = i; k <= j; ++k) {
                int x = meetings[k][0];
                int y = meetings[k][1];
                vertices.insert(x);
                vertices.insert(y);
                edges[x].push_back(y);
                edges[y].push_back(x);
            }

            queue<int> bfsQueue;
            for (int u : vertices) {
                if (secret[u]) {
                    bfsQueue.push(u);
                }
            }
            while (bfsQueue.empty() == false) {
                int u = bfsQueue.front();
                bfsQueue.pop();
                for (int v : edges[u]) {
                    if (secret[v] == false) {
                        secret[v] = true;
                        bfsQueue.push(v);
                    }
                }
            }

            i = j + 1;
        }

        for (int i = 0; i < n; ++i) {
            if (secret[i] == true) {
                retVal.emplace_back(i);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> meetings;
        int firstPerson;
    };
    vector<subject> testData{{6, {{1, 2, 5}, {2, 3, 8}, {1, 5, 10}}, 1},
                             {4, {{3, 1, 3}, {1, 2, 2}, {0, 3, 3}}, 3},
                             {5, {{3, 4, 2}, {1, 2, 1}, {2, 3, 1}}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
     *  Output: [0,1,2,3,5]
     *
     *  Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
     *  Output: [0,1,3]
     *
     *  Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
     *  Output: [0,1,2,3,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", meetings = [";
        for (long unsigned int j = 0; j < testData[i].meetings.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].meetings[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].meetings[j][k];
            }
            cout << "]";
        }
        cout << "], firstPerson = " << testData[i].firstPerson << "\n";

        answer = cSolution.findAllPeople(testData[i].n, testData[i].meetings, testData[i].firstPerson);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
