#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int retVal = 0;

        /* Input : arr = [1, 5, 7, 8, 5, 3, 4, 2, 1], difference = -2
         *  1 dp{1 : 1 }
         *  5 dp{1 : 1, 5 : 1 }
         *  7 dp{1 : 1, 5 : 1, 7 : 1 }
         *  8 dp{1 : 1, 5 : 1, 7 : 1, 8 : 1 }
         *  5 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1 }
         *  3 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3 }
         *  4 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1 }
         *  2 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2 }
         *  1 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2, 1 : 4 }
         */
        unordered_map<int, int> dp;
        for (int value : arr) {
            dp[value] = dp[value - difference] + 1;
            retVal = max(retVal, dp[value]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int difference;
    };
    vector<subject> testData{{{1, 2, 3, 4}, 1}, {{1, 3, 5, 7}, 1}, {{1, 5, 7, 8, 5, 3, 4, 2, 1}, -2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,3,4], difference = 1
     *  Output: 4
     *
     *  Input: arr = [1,3,5,7], difference = 1
     *  Output: 1
     *
     *  Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "], difference = " << testData[i].difference << "\n";

        answer = cSolution.longestSubsequence(testData[i].arr, testData[i].difference);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
