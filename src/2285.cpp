#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        long long retVal = 0;

        vector<int> degree(n, 0);
        for (auto road : roads) {
            degree[road[0]] += 1;
            degree[road[1]] += 1;
        }
        sort(degree.begin(), degree.end());

        long long value = 1;
        for (int d : degree) {
            retVal += (value * d);
            value += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> roads;
    };
    vector<subject> testData{{5, {{0, 1}, {1, 2}, {2, 3}, {0, 2}, {1, 3}, {2, 4}}}, {5, {{0, 3}, {2, 4}, {1, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
     *  Output: 43
     *
     *  Input: n = 5, roads = [[0,3],[2,4],[1,3]]
     *  Output: 20
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", roads = [";
        for (long unsigned int j = 0; j < testData[i].roads.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].roads[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].roads[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximumImportance(testData[i].n, testData[i].roads);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
