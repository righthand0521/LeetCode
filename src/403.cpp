#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canCross(vector<int>& stones) {
        bool retVal = false;

        int stonesSize = stones.size();

        vector<vector<bool>> dp(stonesSize, vector<bool>(stonesSize));
        dp[0][0] = true;

        for (int i = 1; i < stonesSize; ++i) {
            if (stones[i] - stones[i - 1] > i) {
                return retVal;
            }
        }

        for (int i = 1; i < stonesSize; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                int k = stones[i] - stones[j];
                if (k > j + 1) {
                    break;
                }

                dp[i][k] = dp[j][k - 1] || dp[j][k] || dp[j][k + 1];
                if ((i == stonesSize - 1) && (dp[i][k] != false)) {
                    retVal = true;
                    return retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> stones;
    };
    vector<subject> testData{{{0, 1, 3, 5, 6, 8, 12, 17}}, {{0, 1, 2, 3, 4, 8, 9, 11}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: stones = [0,1,3,5,6,8,12,17]
     *  Output: true
     *
     *  Input: stones = [0,1,2,3,4,8,9,11]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: stones = [";
        for (long unsigned int j = 0; j < testData[i].stones.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].stones[j];
        }
        cout << "]\n";

        answer = cSolution.canCross(testData[i].stones);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
