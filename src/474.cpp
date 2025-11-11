#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int retVal = 0;

        int strsSize = strs.size();

        vector<vector<int>> bitsCount(strsSize, vector<int>(2, 0));
        for (int i = 0; i < strsSize; ++i) {
            for (char c : strs[i]) {
                ++bitsCount[i][c - '0'];
            }
        }

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < strsSize; ++i) {
            for (int j = m; j >= bitsCount[i][0]; --j) {
                for (int k = n; k >= bitsCount[i][1]; --k) {
                    dp[j][k] = max(dp[j][k], dp[j - bitsCount[i][0]][k - bitsCount[i][1]] + 1);
                }
            }
        }
        retVal = dp[m][n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> strs;
        int m;
        int n;
    };
    vector<subject> testData{{{"10", "0001", "111001", "1", "0"}, 5, 3}, {{"10", "0", "1"}, 1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
     *  Output: 4
     *
     *  Input: strs = ["10","0","1"], m = 1, n = 1
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: strs = [";
        for (long unsigned int j = 0; j < testData[i].strs.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].strs[j] << "\"";
        }
        cout << "], m = " << testData[i].m << ", n = " << testData[i].n << "\n";

        answer = cSolution.findMaxForm(testData[i].strs, testData[i].m, testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
