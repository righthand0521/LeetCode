#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int knightDialer(int n) {
        int retVal = 0;

        int numericCell = 10;

        vector<vector<int>> jumps = {{4, 6}, {6, 8}, {7, 9}, {4, 8}, {3, 9, 0}, {}, {1, 7, 0}, {2, 6}, {1, 3}, {2, 4}};

        vector<int> previousDp(numericCell, 1);
        for (int i = 1; i < n; ++i) {
            vector<int> dp(numericCell, 0);

            for (int square = 0; square < numericCell; ++square) {
                int sum = 0;
                for (int nextSquare : jumps[square]) {
                    sum = (sum + previousDp[nextSquare]) % MODULO;
                }

                dp[square] = sum;
            }

            previousDp = dp;
        }

        for (int square = 0; square < numericCell; ++square) {
            retVal = (retVal + previousDp[square]) % MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {2}, {3131}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 10
     *
     *  Input: n = 2
     *  Output: 20
     *
     *  Input: n = 3131
     *  Output: 136006598
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.knightDialer(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
