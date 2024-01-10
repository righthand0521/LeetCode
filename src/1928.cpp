#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
/* Constraints
 *  n == passingFees.length
 *  2 <= n <= 1000
 *  1 <= passingFees[j] <= 1000
 */
#define MAX_PASSINGFEES (1000 * 1000 + 1)

    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int retVal = -1;

        int n = passingFees.size();
        vector<vector<int>> fee(maxTime + 1, vector<int>(n, MAX_PASSINGFEES));
        fee[0][0] = passingFees[0];

        for (int i = 1; i <= maxTime; ++i) {
            for (auto& edge : edges) {
                int x = edge[0];
                int y = edge[1];
                int time = edge[2];
                if (time <= i) {
                    fee[i][x] = min(fee[i][x], fee[i - time][y] + passingFees[x]);
                    fee[i][y] = min(fee[i][y], fee[i - time][x] + passingFees[y]);
                }
            }
        }

        int minFee = MAX_PASSINGFEES;
        for (int i = 1; i <= maxTime; ++i) {
            minFee = min(minFee, fee[i][n - 1]);
        }

        if (minFee != MAX_PASSINGFEES) {
            retVal = minFee;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int maxTime;
        vector<vector<int>> edges;
        vector<int> passingFees;
    };
    vector<subject> testData{
        {30, {{0, 1, 10}, {1, 2, 10}, {2, 5, 10}, {0, 3, 1}, {3, 4, 10}, {4, 5, 15}}, {5, 1, 2, 20, 20, 3}},
        {29, {{0, 1, 10}, {1, 2, 10}, {2, 5, 10}, {0, 3, 1}, {3, 4, 10}, {4, 5, 15}}, {5, 1, 2, 20, 20, 3}},
        {25, {{0, 1, 10}, {1, 2, 10}, {2, 5, 10}, {0, 3, 1}, {3, 4, 10}, {4, 5, 15}}, {5, 1, 2, 20, 20, 3}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: maxTime = " << testData[i].maxTime << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], passingFees = [";
        for (long unsigned int j = 0; j < testData[i].passingFees.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].passingFees[j];
        }
        cout << "]\n";

        answer = cSolution.minCost(testData[i].maxTime, testData[i].edges, testData[i].passingFees);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
