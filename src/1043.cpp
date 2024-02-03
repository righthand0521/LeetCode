#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int retVal = 0;

        int arrSize = arr.size();

        vector<int> dp(arrSize + 1, 0);
        for (int i = 1; i <= arrSize; ++i) {
            int maxValue = arr[i - 1];
            for (int j = i - 1; ((j >= 0) && (j >= i - k)); --j) {
                dp[i] = max(dp[i], dp[j] + maxValue * (i - j));
                if (j > 0) {
                    maxValue = max(maxValue, arr[j - 1]);
                }
            }
        }

        retVal = dp[arrSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int k;
    };
    vector<subject> testData{{{1, 15, 7, 9, 2, 5, 10}, 3}, {{1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3}, 4}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,15,7,9,2,5,10], k = 3
     *  Output: 84
     *
     *  Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
     *  Output: 83
     *
     *  Input: arr = [1], k = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxSumAfterPartitioning(testData[i].arr, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
