#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> retVal;

        //
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& meeting : meetings) {
            int x = meeting[0];
            int y = meeting[1];
            int t = meeting[2];
            graph[x].emplace_back(t, y);
            graph[y].emplace_back(t, x);
        }

        //
        int secretDefaultValue = std::numeric_limits<int>::max();
        vector<int> secret(n, secretDefaultValue);
        secret[0] = 0;
        secret[firstPerson] = 0;

        //
        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(0, 0);
        bfsQueue.emplace(firstPerson, 0);
        while (bfsQueue.empty() == false) {
            auto [person, time] = bfsQueue.front();
            bfsQueue.pop();
            for (auto [t, nextPerson] : graph[person]) {
                if ((t >= time) && (secret[nextPerson] > t)) {
                    secret[nextPerson] = t;
                    bfsQueue.emplace(nextPerson, t);
                }
            }
        }

        //
        for (int i = 0; i < n; ++i) {
            if (secret[i] != secretDefaultValue) {
                retVal.push_back(i);
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
